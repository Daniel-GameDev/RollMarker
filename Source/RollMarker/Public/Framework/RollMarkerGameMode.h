// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay/Common/MarkerCubeTypes.h"
#include "RollMarkerGameMode.generated.h"

class AMarkerBall;

UCLASS()
class ROLLMARKER_API ARollMarkerGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AMarkerBall> MarkerBall;

private:
	UPROPERTY(EditDefaultsOnly)
	FVector StartLocation = FVector(0.f, 0.f, 200.f);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> Music;
	
	bool CheckEndGameCondition();
	void EndGame();

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TotalCubeNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 DefaultCubeNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CleanerCubeNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Time;

	UFUNCTION(BlueprintCallable)
	void BeginGame();

	UFUNCTION()
	void CubeTypeInGame(EMarkerCubeType MarkerCubeType, bool bDefaultState);

};
