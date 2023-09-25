// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MarkerCubeBase.generated.h"

UENUM(BlueprintType) // <<<<
enum class EMarkerCubeActions : uint8
{
	EMCA_MoveX UMETA(DisplayName = "ImpulseX"),
	EMCA_MoveY UMETA(DisplayName = "ImpulseY"),
	EMCA_Jump UMETA(DisplayName = "Jump")
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

	UFUNCTION()
	void RandomMovement();

	UFUNCTION()
	void AddImpulseX();

	UFUNCTION()
	void AddImpulseY();

	UFUNCTION()
	void Jump();

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	float RandomImpulseIntervalTime = 0.2;

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
	float JumpDelayTemp;

	UPROPERTY(EditAnywhere, Category = "Impulse | Jump")
	bool bJumpAllowed = true;

};
