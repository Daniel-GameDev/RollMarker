// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/RollMarkerGameMode.h"
#include "Framework/MarkerBall.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/RollMarkerPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void ARollMarkerGameMode::BeginGame()
{
	FActorSpawnParameters ActorSpawnParameters;
	if (GetWorld() && MarkerBall)
	{
		FInputModeGameOnly InputMode;
		GetWorld()->GetFirstPlayerController()->SetInputMode(InputMode);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false);
		if (ARollMarkerPlayerController* RollMarkerPlayerController = Cast<ARollMarkerPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			RollMarkerPlayerController->CreateUserWidget(RollMarkerPlayerController->GameWidget);
		}

		AActor* PlayerPawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MarkerBall, FTransform(StartLocation), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);
		if (AMarkerBall* MarkerBallPawn = Cast<AMarkerBall>(PlayerPawn))
		{
			GetWorld()->GetFirstPlayerController()->Possess(MarkerBallPawn);
		}
		UGameplayStatics::FinishSpawningActor(PlayerPawn, FTransform(StartLocation));
	}
}

bool ARollMarkerGameMode::CheckEndGameCondition()
{
	if (TotalCubeNum == 0) return true;

	return false;
}

void ARollMarkerGameMode::EndGame()
{
	if (GetWorld())
	{
		if (ARollMarkerPlayerController* RollMarkerPlayerController = Cast<ARollMarkerPlayerController>(GetWorld()->GetFirstPlayerController()))
		{
			UWidgetLayoutLibrary::RemoveAllWidgets(this);
			RollMarkerPlayerController->SetShowMouseCursor(true);
			RollMarkerPlayerController->CreateUserWidget(RollMarkerPlayerController->EndGameWidget);
		}
	}
}

void ARollMarkerGameMode::CubeTypeInGame(EMarkerCubeType MarkerCubeType, bool bDefaultState)
{
	switch (MarkerCubeType)
	{
	case EMarkerCubeType::EMCT_Default:
		if (bDefaultState)
		{
			DefaultCubeNum++;
			TotalCubeNum++;
		}
		else
		{
			DefaultCubeNum--;
			TotalCubeNum--;
		}
		break;
	case EMarkerCubeType::EMCS_Cleaner:
		if (bDefaultState)
		{
			CleanerCubeNum++;
			TotalCubeNum++;
		}
		else
		{
			CleanerCubeNum--;
			TotalCubeNum--;
		}
		break;
	default:
		break;
	}

	if (CheckEndGameCondition())
	{
		EndGame();
	}
}
