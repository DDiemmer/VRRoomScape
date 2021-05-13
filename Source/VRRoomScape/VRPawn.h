// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VRPawn.generated.h"

UCLASS()
class VRROOMSCAPE_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//scene
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
		USceneComponent* vROrigin;
	//camera
	UPROPERTY(EditDefaultsOnly, Category = "Components")
		class UCameraComponent* camera;

	FVector GetForwardDirection();
};
