// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableHandCollider.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AInteractableHandCollider::AInteractableHandCollider()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	//Mesh
	handMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand Skeletal Mesh"));
	handMesh->SetupAttachment(RootComponent);
	////grab colliders
	grabCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Grab Collider"));
	grabCollider->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AInteractableHandCollider::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractableHandCollider::InvertHandMotion()
{
	bIsleftHand = !bIsleftHand;
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
}

