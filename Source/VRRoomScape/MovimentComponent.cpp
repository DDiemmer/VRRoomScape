// Fill out your copyright notice in the Description page of Project Settings.


#include "MovimentComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "VRPawn.h"
#include <VRRoomScape/Helper.h>

// Sets default values for this component's properties
UMovimentComponent::UMovimentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//post process 
	postProcessBlurWalk = CreateDefaultSubobject<UPostProcessComponent>(TEXT("Post process walk blur"));
	//get pawn 
	pawn = Cast<AVRPawn>(GetOwner());
}

// Called when the game starts
void UMovimentComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UMovimentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Move the pawn
void UMovimentComponent::MovePawn(float axisValue)
{
	float velocity = axisValue * movimentSpeed;
	FVector dir = pawn->GetForwardDirection();
	dir.Z = 0;
	FVector moviment = pawn->GetActorLocation() + (dir * velocity);

	bIsMoving = FMath::Abs(axisValue) > 0;

	if (!bIsRotate || (postProcessBlurWalk->Settings.WeightedBlendables.Array[0].Weight < FMath::Abs(axisValue) && FMath::Abs(axisValue) > 0.2))
		SetWeightWalkEffect(axisValue);

	pawn->TeleportTo(moviment, pawn->GetActorRotation());
}

//to Rotate the Pawn 
void UMovimentComponent::RotatePawn(float axisValue)
{
	float velocity = axisValue * rotationSpeed;
	FRotator rotation = pawn->GetActorRotation();
	rotation.Yaw += velocity;
	bIsRotate = FMath::Abs(axisValue) > 0;
	if (!bIsMoving || (postProcessBlurWalk->Settings.WeightedBlendables.Array[0].Weight < FMath::Abs(axisValue) && FMath::Abs(axisValue) > 0.2))
		SetWeightWalkEffect(axisValue);

	pawn->SetActorRotation(rotation);
}

void UMovimentComponent::SetWeightWalkEffect(float weightValue)
{
	float value = FMath::Abs(weightValue);
	/*FString TheFloatStr = FString::SanitizeFloat(value);
	UHelper::Print(TheFloatStr);*/
	postProcessBlurWalk->Settings.WeightedBlendables.Array[0].Weight = value <= 0.2 ? 0 : value;
}