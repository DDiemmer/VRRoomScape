// Fill out your copyright notice in the Description page of Project Settings.


#include "VRPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Helper.h"

// Sets default values
AVRPawn::AVRPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//scene 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	vROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROriginScene"));
	vROrigin->SetupAttachment(RootComponent);
	//camera
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->FieldOfView = 110.0f;
	camera->SetupAttachment(vROrigin);
}

// Called when the game starts or when spawned
void AVRPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*PlayerInputComponent->BindAxis("MotionControllerThumbLeft_Y", this, &AVRPawn::MoveRig);
	PlayerInputComponent->BindAxis("MotionControllerThumbLeft_X", this, &AVRPawn::RotateRig);*/
}

FVector AVRPawn::GetForwardDirection()
{
	return camera->GetForwardVector();
}

