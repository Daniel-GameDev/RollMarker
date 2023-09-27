// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MarkerCubeCleaner.h"

AMarkerCubeCleaner::AMarkerCubeCleaner()
{
	bGenerateOverlapEvents = true;
	bCanBeMarked = false;
}

void AMarkerCubeCleaner::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AMarkerCubeBase* MarkerCubePtr = Cast<AMarkerCubeBase>(OtherActor))
	{
		if (MarkerCubeState == EMarkerCubeState::EMCS_Default)
		{
			if (MarkerCubePtr->GetMarkerCubeState() == EMarkerCubeState::EMCS_Default) return;

			MarkerCubePtr->UnMark();
		}
		else if (CheckMarkConditions(MarkerCubePtr))
		{
			MarkerCubePtr->Mark(GetStaticMeshMaterial());
		}
	}
}
