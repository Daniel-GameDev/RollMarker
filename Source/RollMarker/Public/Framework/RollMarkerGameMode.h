// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollMarkerGameMode.generated.h"

class AMarkerBall;

UCLASS()
class ROLLMARKER_API ARollMarkerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMarkerBall> MarkerBall;

private:
	UPROPERTY(EditDefaultsOnly)
	FVector StartLocation = FVector(0.f, 0.f, 200.f);

public:
	UFUNCTION(BlueprintCallable)
	void BeginGame();

};
