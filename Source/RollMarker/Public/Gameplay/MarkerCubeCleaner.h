// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gameplay/MarkerCubeBase.h"
#include "MarkerCubeCleaner.generated.h"

UCLASS()
class ROLLMARKER_API AMarkerCubeCleaner : public AMarkerCubeBase
{
	GENERATED_BODY()

public:
	AMarkerCubeCleaner();
	
protected:
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

};
