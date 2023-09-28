// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class EMarkerCubeActions : uint8
{
	EMCA_MoveX UMETA(DisplayName = "Impulse | Move X"),
	EMCA_MoveY UMETA(DisplayName = "Impulse | Move Y"),
	EMCA_Jump UMETA(DisplayName = "Jump"),
	EMCA_Last UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EMarkerCubeState : uint8
{
	EMCS_Default UMETA(DisplayName = "Default"),
	EMCS_Marked UMETA(DisplayName = "Marked")
};

UENUM(BlueprintType)
enum class EMarkerCubeType : uint8
{
	EMCT_Default UMETA(DisplayName = "Default Cube"),
	EMCS_Cleaner UMETA(DisplayName = "Cleaner Cube")
};