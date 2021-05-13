// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ControllerState.h"
#include "MotionControllerInteractable.generated.h"

UCLASS()
class VRROOMSCAPE_API AMotionControllerInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMotionControllerInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//scene
	UPROPERTY(EditAnywhere, Category = "Components")
		USceneComponent* root;
	//motion controller 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UMotionControllerComponent* motionController;
	//meshs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USkeletalMeshComponent* handMesh;
	////sphere collider
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USphereComponent* grabCollider;

	UFUNCTION(BlueprintCallable)
		void InvertHandMotion();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		bool bIsleftHand = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Status)
		TEnumAsByte<EControllerState> controllerState;

	UFUNCTION(BlueprintCallable)
		AActor* GetNearInteractable();

};
