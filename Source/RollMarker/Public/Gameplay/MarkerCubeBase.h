// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Common/MarkerCubeTypes.h"
#include "MarkerCubeBase.generated.h"

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

	UPROPERTY(VisibleAnywhere)
	bool bGenerateOverlapEvents;

	UPROPERTY(VisibleAnywhere)
	bool bCanBeMarked;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EMarkerCubeState> MarkerCubeState = EMarkerCubeState::EMCS_Default;

	UPROPERTY(VisibleAnywhere)
	TEnumAsByte<EMarkerCubeType> MarkerCubeType;

	UPROPERTY(EditDefaultsOnly)
	FVector HitParticleScale = FVector(1.f);

	UFUNCTION()
	void SpawnHitEmitter(FVector Location);

	UFUNCTION()
	void PlayHitSound(FVector Location);

	UFUNCTION()
	virtual void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	FORCEINLINE UMaterialInstance* GetStaticMeshMaterial() { return (UMaterialInstance*)StaticMeshComponent->GetMaterial(0); }

	void SetBoxComponentGenerateOverlapEvents();

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

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterialInstance> DefaultMaterial;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> HitParticle;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> HitSound;

	UFUNCTION()
	void TransferStateToGameMode(bool bDefaultState);

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

public:
	bool CheckMarkConditions(AMarkerCubeBase* MarkerCubePtr);
	void Mark(UMaterialInstance* Material);
	void UnMark();

	FORCEINLINE EMarkerCubeState GetMarkerCubeState() { return MarkerCubeState; }

};
