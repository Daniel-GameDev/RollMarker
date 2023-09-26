// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MarkerCubeBase.generated.h"

UENUM(BlueprintType)
enum class EMarkerCubeActions : uint8
{
	EMCA_MoveX UMETA(DisplayName = "ImpulseX"),
	EMCA_MoveY UMETA(DisplayName = "ImpulseY"),
	EMCA_Jump UMETA(DisplayName = "Jump"),
	EMCA_Last UMETA(Hidden)
};

class UBoxComponent;

UCLASS()
class ROLLMARKER_API AMarkerCubeBase : public APawn
{
	GENERATED_BODY()

public:
	AMarkerCubeBase();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere, Category = "Impulse")
	float RandomImpulseIntervalTime = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Impulse")
	float MinImpulseValue = -500.f;

	UPROPERTY(EditAnywhere, Category = "Impulse")
	float MaxImpulseValue = 500.f;

	UPROPERTY(EditAnywhere, Category = "Impulse | Jump")
	float MinJumpImpulseValue = 300.f;

	UPROPERTY(EditAnywhere, Category = "Impulse | Jump")
	float MaxJumpImpulseValue = 500.f;

	UPROPERTY(EditAnywhere, Category = "Impulse | Jump")
	float JumpDelayTime = 3.f;

	UPROPERTY(VisibleAnywhere, Category = "Impulse | Jump")
	float JumpDelayTimeTemp;

	UPROPERTY(VisibleAnywhere, Category = "Impulse | Jump")
	bool bJumpAllowed = true;

	UPROPERTY(VisibleAnywhere, Category = "Impulse")
	TEnumAsByte<EMarkerCubeActions> MarkerCubeAction;

	uint8 LastEnumIndex;
	FTimerHandle TimerHandle;
	TArray<EMarkerCubeActions> CubeActionsArray;

	int8 GetRandomEnum(TArray<TEnumAsByte<EMarkerCubeActions>>ExcludedEnums);
	void SetLastEnumIndex();
	void SetupRandomMovementTimer();
	void RandomMovement();
	void AddRandImpulseX();
	void AddRandImpulseY();
	void Jump();

};
