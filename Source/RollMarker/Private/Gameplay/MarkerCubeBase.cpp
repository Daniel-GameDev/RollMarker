// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MarkerCubeBase.h"
#include "Components/BoxComponent.h"

AMarkerCubeBase::AMarkerCubeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetSimulatePhysics(true);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);
}

void AMarkerCubeBase::BeginPlay()
{
	Super::BeginPlay();

	SetLastEnumIndex();
	SetupRandomMovementTimer();
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

void AMarkerCubeBase::SetMarkedState(FColor Color)
{
}

void AMarkerCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}