// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupInterface.h"

#include "Pickup.generated.h"

UCLASS()
class VRROOMSCAPE_API APickup : public AActor, public IPickupInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
		USceneComponent* root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
		class UBoxComponent* base;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
		class UBoxComponent* interactiveCollider;

	UPROPERTY(EditAnywhere, Category = "Pickup")
		class UMotionControllerComponent* currentMotionController;
	//variables
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pickup")
		bool bUsing;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Components")
		class UStaticMeshComponent* representationObject;

	bool bSimulatePhysics;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Interface")
		void Pickup(class UMotionControllerComponent* motionController);

	virtual void Pickup_Implementation(class UMotionControllerComponent* motionController) override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pickup Interface")
		void Drop(class UMotionControllerComponent* motionController);

	virtual void Drop_Implementation(class UMotionControllerComponent* motionController) override;
};
