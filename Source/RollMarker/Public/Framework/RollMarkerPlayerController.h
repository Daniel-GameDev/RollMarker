// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RollMarkerPlayerController.generated.h"

UCLASS()
class ROLLMARKER_API ARollMarkerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UserWidget)
	TSubclassOf<UUserWidget> StartWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UserWidget)
	TSubclassOf<UUserWidget> GameWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UserWidget)
	TSubclassOf<UUserWidget> EndGameWidget;

	UFUNCTION()
	void CreateUserWidget(TSubclassOf<UUserWidget> Widget);

	//UFUNCTION()
	//void StartCameraShake();

};
