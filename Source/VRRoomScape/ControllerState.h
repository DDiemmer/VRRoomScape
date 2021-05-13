// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ControllerState.generated.h"
/**
 *
 */
UENUM(BlueprintType)
enum EControllerState
{
	Open		UMETA(DisplayName = "Open"),
	CanGrab		UMETA(DisplayName = "CanGrab"),
	Grab		UMETA(DisplayName = "Grab")
};
