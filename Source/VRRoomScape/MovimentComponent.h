// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MovimentComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VRROOMSCAPE_API UMovimentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMovimentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		float movimentSpeed = 3.0f;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 0.6f;
	//post process 
	UPROPERTY(EditAnywhere, Category = "Components")
		class UPostProcessComponent* postProcessBlurWalk;

	UFUNCTION(BlueprintCallable)
		void MovePawn(float axisValue);

	UFUNCTION(BlueprintCallable)
		void RotatePawn(float axisValue);
private:

	bool bIsMoving = false;
	bool bIsRotate = false;
	class AVRPawn* pawn;

	void SetWeightWalkEffect(float weightValue);

};
