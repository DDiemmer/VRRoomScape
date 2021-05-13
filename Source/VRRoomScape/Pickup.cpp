// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "MotionControllerComponent.h"
#include "Components/BoxComponent.h"
// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = root;

	base = CreateDefaultSubobject<UBoxComponent>(TEXT("Base"));
	base->SetSimulatePhysics(true);
	base->SetBoxExtent(FVector(1, 1, 1));
	base->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	base->SetupAttachment(root);

	interactiveCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interactive Collider"));
	interactiveCollider->SetupAttachment(base);

	representationObject = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Representation"));
	representationObject->SetupAttachment(base);

	bUsing = false;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	bSimulatePhysics = base->IsSimulatingPhysics();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::Pickup_Implementation(UMotionControllerComponent* motionController)
{
	if (!bUsing)
	{
		bUsing = true;

		currentMotionController = motionController;

		base->SetSimulatePhysics(false);
		base->AttachToComponent(motionController, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}
}

void APickup::Drop_Implementation(UMotionControllerComponent* motionController)
{
	if ((motionController == nullptr) || (currentMotionController == motionController))
	{
		bUsing = false;

		base->SetSimulatePhysics(bSimulatePhysics);
		currentMotionController = nullptr;
		base->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	}
}