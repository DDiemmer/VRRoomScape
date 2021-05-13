// Fill out your copyright notice in the Description page of Project Settings.


#include "MotionControllerInteractable.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "HeadMountedDisplay.h"
#include "MotionControllerComponent.h"
#include "Pickup.h"

// Sets default values
AMotionControllerInteractable::AMotionControllerInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	root = RootComponent;

	motionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("Motion Controller"));
	motionController->bDisplayDeviceModel = true;
	motionController->SetupAttachment(root);
	//Mesh
	handMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand Skeletal Mesh"));
	handMesh->SetupAttachment(motionController);
	////grab colliders
	grabCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Grab Collider"));
	grabCollider->SetupAttachment(motionController);
}

// Called when the game starts or when spawned
void AMotionControllerInteractable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMotionControllerInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMotionControllerInteractable::InvertHandMotion()
{
	bIsleftHand = !bIsleftHand;
	motionController->bDisplayDeviceModel = false;

	if (bIsleftHand)
		motionController->MotionSource = "Left";
	else
		motionController->MotionSource = "Right";

	//change transform of mesh
	FVector newMeshLocation = handMesh->GetRelativeLocation();
	newMeshLocation.Y *= -1;
	handMesh->SetRelativeLocation(newMeshLocation);

	FVector newScale = handMesh->GetRelativeScale3D();
	newScale.X *= -1;
	handMesh->SetRelativeScale3D(newScale);
	//change grabcollider position
	FVector newSphereLocation = grabCollider->GetRelativeLocation();
	newSphereLocation.Y *= -1;
	grabCollider->SetRelativeLocation(newSphereLocation);
	motionController->bDisplayDeviceModel = true;
}

AActor* AMotionControllerInteractable::GetNearInteractable()
{
	TArray<AActor*> result;
	GetOverlappingActors(result, APickup::StaticClass());

	float nearDistActor = 9999;
	AActor* nearActor = nullptr;
	for (size_t i = 0; i < result.Num(); i++)
	{
		float distance = FVector::Distance(result[i]->GetActorLocation(), grabCollider->GetComponentLocation());
		if (distance < nearDistActor)
		{
			nearActor = result[i];
			nearDistActor = distance;
		}
	}
	return nearActor;
}

