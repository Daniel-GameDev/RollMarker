// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MarkerCubeBase.h"
#include "Components/BoxComponent.h"
#include "Framework/RollMarkerGameMode.h"
#include "Kismet/GameplayStatics.h"

AMarkerCubeBase::AMarkerCubeBase()	
{
	PrimaryActorTick.bCanEverTick = true;
	bGenerateOverlapEvents = false;
	bCanBeMarked = true;
	MarkerCubeType = EMarkerCubeType::EMCT_Default;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetSimulatePhysics(true);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMarkerCubeBase::OnBoxBeginOverlap);
}

void AMarkerCubeBase::BeginPlay()
{
	Super::BeginPlay();

	TransferStateToGameMode(true);

	DefaultMaterial = (UMaterialInstance*)StaticMeshComponent->GetMaterial(0);

	SetLastEnumIndex();
	SetupRandomMovementTimer();
	SetBoxComponentGenerateOverlapEvents();
}

void AMarkerCubeBase::SetupRandomMovementTimer()
{
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMarkerCubeBase::RandomMovement, RandomImpulseIntervalTime, true);
	}
}

void AMarkerCubeBase::SetLastEnumIndex()
{
	MarkerCubeAction = EMarkerCubeActions::EMCA_Last;
	LastEnumIndex = MarkerCubeAction.GetIntValue();
	for (int8 i = 0; i < LastEnumIndex; i++)
	{
		CubeActionsArray.Add(EMarkerCubeActions(i));
	}
}

void AMarkerCubeBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMarkerCubeBase* MarkerCubePtr = Cast<AMarkerCubeBase>(OtherActor))
	{
		if (CheckMarkConditions(MarkerCubePtr))
		{
			FHitResult HitResult;
			GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), OtherActor->GetActorLocation(), ECollisionChannel::ECC_Visibility);
			SpawnHitEmitter(HitResult.Location);
			PlayHitSound(HitResult.Location);
			MarkerCubePtr->Mark(GetStaticMeshMaterial());
		}
	}
}

void AMarkerCubeBase::SpawnHitEmitter(FVector Location)
{
	if (GetWorld() && HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, FTransform(GetActorRotation(), Location, FVector(HitParticleScale)));
	}
}

void AMarkerCubeBase::PlayHitSound(FVector Location)
{
	if (GetWorld() && HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, Location);
	}
}

void AMarkerCubeBase::SetBoxComponentGenerateOverlapEvents()
{
	BoxComponent->SetGenerateOverlapEvents(bGenerateOverlapEvents);
}

bool AMarkerCubeBase::CheckMarkConditions(AMarkerCubeBase* MarkerCubePtr)
{
	if (MarkerCubePtr->GetMarkerCubeState() == EMarkerCubeState::EMCS_Marked || MarkerCubePtr->bCanBeMarked == false) return false;

	return true;
}

void AMarkerCubeBase::TransferStateToGameMode(bool bDefaultState)
{
	if (GetWorld())
	{
		if (ARollMarkerGameMode* RollMarkerGameMode = Cast<ARollMarkerGameMode>(GetWorld()->GetAuthGameMode()))
		{
			RollMarkerGameMode->CubeTypeInGame(MarkerCubeType, bDefaultState);
		}
	}
}

int8 AMarkerCubeBase::GetRandomEnum(TArray<TEnumAsByte<EMarkerCubeActions>>ExcludedEnums)
{
	TArray<EMarkerCubeActions> MarkerCubeActionsTemp = CubeActionsArray;
	for (int8 i = 0; i < ExcludedEnums.Num(); i++)
	{
		if (MarkerCubeActionsTemp.Find(ExcludedEnums[i].GetValue()))
		{
			MarkerCubeActionsTemp.Remove(ExcludedEnums[i].GetValue());
		}
	}

	const int8 RandIndex = FMath::RandRange(0, MarkerCubeActionsTemp.Num() - 1);
	return RandIndex;
}

void AMarkerCubeBase::RandomMovement()
{
	if (bJumpAllowed)
	{
		TArray<TEnumAsByte<EMarkerCubeActions>>ExcludedEnum = {EMarkerCubeActions::EMCA_Last};
		MarkerCubeAction = EMarkerCubeActions(GetRandomEnum(ExcludedEnum));
	}
	else
	{
		TArray<TEnumAsByte<EMarkerCubeActions>>ExcludedEnum = {EMarkerCubeActions::EMCA_Last, EMarkerCubeActions::EMCA_Jump};
		MarkerCubeAction = EMarkerCubeActions(GetRandomEnum(ExcludedEnum));
		JumpDelayTimeTemp = FMath::Clamp(RandomImpulseIntervalTime + JumpDelayTimeTemp, 0, JumpDelayTime);
		if (JumpDelayTimeTemp == JumpDelayTime)
		{
			bJumpAllowed = true;
			JumpDelayTimeTemp = 0.f;
		}
	}

	switch (MarkerCubeAction)
	{
	case EMarkerCubeActions::EMCA_MoveX:
		AddRandImpulseX();
		break;
	case EMarkerCubeActions::EMCA_MoveY:
		AddRandImpulseY();
		break;
	case EMarkerCubeActions::EMCA_Jump:
		bJumpAllowed = false;
		Jump();
		break;
	default:
		break;
	}
}

void AMarkerCubeBase::AddRandImpulseX()
{
	StaticMeshComponent->AddImpulse(FVector(FMath::FRandRange(MinImpulseValue, MaxImpulseValue), 0.f, 0.f), NAME_None, true);
}

void AMarkerCubeBase::AddRandImpulseY()
{
	StaticMeshComponent->AddImpulse(FVector(0.f, FMath::FRandRange(MinImpulseValue, MaxImpulseValue), 0.f), NAME_None, true);
}

void AMarkerCubeBase::Jump()
{
	StaticMeshComponent->AddImpulse(FVector(0.f, 0.f, FMath::FRandRange(MinJumpImpulseValue, MaxJumpImpulseValue)), NAME_None, true);
}

void AMarkerCubeBase::Mark(UMaterialInstance* Material)
{
	MarkerCubeState = EMarkerCubeState::EMCS_Marked;
	BoxComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetMaterial(0, Material);
	TransferStateToGameMode(false);
}

void AMarkerCubeBase::UnMark()
{
	MarkerCubeState = EMarkerCubeState::EMCS_Default;
	BoxComponent->SetGenerateOverlapEvents(bGenerateOverlapEvents);
	StaticMeshComponent->SetMaterial(0, DefaultMaterial);
	TransferStateToGameMode(true);
}

void AMarkerCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}