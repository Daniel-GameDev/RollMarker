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
		PlayerEnchancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMarkerBall::Movement);
		PlayerEnchancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMarkerBall::Look);
	}
}

void AMarkerBall::Movement(const FInputActionValue& Value)
{
	//TODO: Add Velocity Check for Arrow and speed control
	const FVector2D MoveVector = Value.Get<FVector2D>();
	const FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());
	const FVector RightVector = UKismetMathLibrary::GetRightVector(GetControlRotation());
	StaticMeshComponent->AddAngularImpulseInDegrees(ForwardVector * MoveVector.Y * 5.f, NAME_None, true);
	StaticMeshComponent->AddAngularImpulseInDegrees(RightVector * MoveVector.X * 5.f, NAME_None, true);
}

void AMarkerBall::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookVector.Y);
	AddControllerYawInput(LookVector.X);
}

void AMarkerBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}