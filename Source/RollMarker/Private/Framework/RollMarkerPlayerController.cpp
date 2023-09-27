// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/RollMarkerPlayerController.h"
#include "Blueprint/UserWidget.h"

void ARollMarkerPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
	if (StartWidget)
	{
		CreateUserWidget(StartWidget);
	}
}

void ARollMarkerPlayerController::CreateUserWidget(TSubclassOf<UUserWidget> Widget)
{
	if (GetWorld() && Widget)
	{
		UUserWidget* WidgetToCreate = CreateWidget<UUserWidget>(GetWorld(), Widget);
		WidgetToCreate->AddToViewport();
	}
}
