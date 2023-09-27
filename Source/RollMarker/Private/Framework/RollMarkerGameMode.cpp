// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/RollMarkerGameMode.h"
#include "Framework/MarkerBall.h"
#include "Kismet/GameplayStatics.h"

void ARollMarkerGameMode::BeginGame()
{
	FActorSpawnParameters ActorSpawnParameters;
	if (GetWorld() && MarkerBall)
	{
		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetShowMouseCursor(false);
		//FInputModeGameOnly InputMode;
		//UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetInputMode(InputMode);

		//AMarkerBall* PlayerPawn = GetWorld()->SpawnActor<AMarkerBall>(MarkerBall, StartLocation, FRotator(), ActorSpawnParameters);
		//GetWorld()->GetFirstPlayerController()->Possess(PlayerPawn);
		//PlayerPawn->PossessedBy(UGameplayStatics::GetPlayerController(GetWorld(), 0));

		AActor* PlayerPawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MarkerBall, FTransform(StartLocation), ESpawnActorCollisionHandlingMethod::Undefined, nullptr);
		if (AMarkerBall* MarkerBallPawn = Cast<AMarkerBall>(PlayerPawn))
		{
			GetWorld()->GetFirstPlayerController()->Possess(MarkerBallPawn);
		}
		UGameplayStatics::FinishSpawningActor(PlayerPawn, FTransform(StartLocation));
	}
}
