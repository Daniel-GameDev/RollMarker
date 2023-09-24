// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/MarkerBall.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

AMarkerBall::AMarkerBall()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	StaticMeshComponent->SetSimulatePhysics(true);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereComponent->SetupAttachment(StaticMeshComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(StaticMeshComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMarkerBall::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void AMarkerBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* PlayerEnchancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerEnchancedInputComponent->BindAction(ForwardAction, ETriggerEvent::Triggered, this, &AMarkerBall::MoveForward);
		PlayerEnchancedInputComponent->BindAction(RightAction, ETriggerEvent::Triggered, this, &AMarkerBall::MoveRight);
		PlayerEnchancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMarkerBall::Look);
	}
}

void AMarkerBall::MoveForward(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Forward"));
	}
	const FVector MoveVector = Value.Get<FVector>();
	const FVector Forward = UKismetMathLibrary::GetForwardVector(GetControlRotation());
	StaticMeshComponent->AddImpulse(Forward * MoveVector * 5.f, NAME_None, true);
}

void AMarkerBall::MoveRight(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Right"));
	}
	const FVector MoveVector = Value.Get<FVector>();
	const FVector Forward = UKismetMathLibrary::GetForwardVector(GetControlRotation());
	StaticMeshComponent->AddAngularImpulseInDegrees(Forward * MoveVector * 5.f, NAME_None, true);
}

void AMarkerBall::Look(const FInputActionValue& Value)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Look"));
	}
}

void AMarkerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}