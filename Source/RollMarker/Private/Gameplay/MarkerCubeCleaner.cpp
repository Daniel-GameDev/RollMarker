// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MarkerCubeCleaner.h"

AMarkerCubeCleaner::AMarkerCubeCleaner()
{
	bGenerateOverlapEvents = true;
	bCanBeMarked = false;
}

void AMarkerCubeCleaner::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMarkerCubeBase* MarkerCuberPtr = Cast<AMarkerCubeBase>(OtherActor))
	{
		if (MarkerCubeState == EMarkerCubeState::EMCS_Default)
		{
			if (MarkerCuberPtr->GetMarkerCubeState() == EMarkerCubeState::EMCS_Default) return;

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("UNMARK By Cleaner"));
			}

			MarkerCuberPtr->UnMark();
		}
		else
		{
			MarkerCuberPtr->CheckMarkConditions(OtherActor);
		}
	}
}
