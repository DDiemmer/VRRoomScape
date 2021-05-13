// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButtonManagerInterface.h"
#include "PushButton.generated.h"

UCLASS()
class VRROOMSCAPE_API APushButton : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Components")
		class UStaticMeshComponent* buttonPush;
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Components")
		class UStaticMeshComponent* limitWall;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UBoxComponent* boxCollider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UPhysicsConstraintComponent* springForce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		UMaterialInstanceDynamic* buttonPushMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		FLinearColor buttonPushColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		USoundBase* clickSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		float maxBloom = 7.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		float minBloom = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		bool showLimitWall = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button Attributes")
		float timeToReactive = 0.2f;

public:
	UFUNCTION(BlueprintCallable)
		void GlowButton(float timeToDark, int amountBlinks = 1);
	UFUNCTION(BlueprintCallable)
		void DarkButton(float timeToDark, int amountBlinks = 1);
	//call on constructor of the blueprint 
	UFUNCTION(BlueprintCallable)
		void Initialize(UMaterialInterface* material);
	//to update button material when its actor is a child of another object
	UFUNCTION()
		void UpdateButtonMaterial();

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void SetButtonManager(TScriptInterface<IButtonManagerInterface> _buttonManager, int id = 0);

	UFUNCTION()
		void SetCanActive(bool active);

private:
	class TScriptInterface<IButtonManagerInterface> buttonManager;
	int idButton;
	bool canActive = true;
};
