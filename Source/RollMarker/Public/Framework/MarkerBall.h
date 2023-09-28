// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MarkerBall.generated.h"

class USphereComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class InputActionValue;
class UNiagaraComponent;

UCLASS()
class ROLLMARKER_API AMarkerBall : public APawn
{
	GENERATED_BODY()

public:
	AMarkerBall();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly)
	float SpeedMultiplier = 5.f;

	UPROPERTY(EditDefaultsOnly)
	FVector HitParticleScale = FVector(0.5f);

	UFUNCTION()
	void Movement(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

private:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UMaterialInstance> Material;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UNiagaraComponent> NiagaraComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UParticleSystem> HitParticle;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USoundBase> HitSound;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void DrawBallDirectionArrow();

};