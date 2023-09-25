// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/MarkerCubeBase.h"
#include "Components/BoxComponent.h"

AMarkerCubeBase::AMarkerCubeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMarkerCubeBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMarkerCubeBase::RandomMovement()
{
}

void AMarkerCubeBase::AddImpulseX()
{
}

void AMarkerCubeBase::AddImpulseY()
{
}

void AMarkerCubeBase::Jump()
{
}

void AMarkerCubeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}