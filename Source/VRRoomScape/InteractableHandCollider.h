// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableHandCollider.generated.h"

UCLASS()
class VRROOMSCAPE_API AInteractableHandCollider : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AInteractableHandCollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
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
};
