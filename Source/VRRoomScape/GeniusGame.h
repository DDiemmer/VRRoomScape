// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushButton.h"
#include "ButtonManagerInterface.h"
#include "GeniusGame.generated.h"


UCLASS()
class VRROOMSCAPE_API AGeniusGame : public AActor, public IButtonManagerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGeniusGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//mesh of the genius 
	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Components")
		class UStaticMeshComponent* geniusMesh;
	//variables
	//max number of times the buttons blinked 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int maxNumBlink = 12;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int startNumBlink = 3;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		UChildActorComponent* buttonsStartActor;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		TArray<UChildActorComponent*> buttonsActors;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		APushButton* buttonStart;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		TArray<APushButton*> buttonsPush;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
		TArray<int> butttonBlinkOrder;

private:
	bool inGame = false;

	int numberButtons;
	/*iterator to know what order click*/
	int itClicks = 0;
	/* Set buttons to blink */
	void SetButtonBlink();
	/*Add random button id in array*/
	void AddButtonOrder();
	/*Blink the buttons on the order of array*/
	void BlinkOrder();
	/*Blink button by id*/
	void BlinkButton(int idButton, float timeToDark, bool isLastToblink = false);
	/* Check button clicked*/
	void ClickCheck(int idButton);
	/*Wrong button action*/
	void ErrorAction();

	void WinAction();
	bool finishGame = false;

public:
	//call on constructor of the blueprint 
	UFUNCTION(BlueprintCallable)
		void Initialize();
	UFUNCTION(BlueprintCallable)
		void GlowAll();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Button Manager Interface")
		void OnClick(class APushButton* pushButton, int idButton = 0);

	virtual void OnClick_Implementation(class APushButton* pushButton, int idButton = 0) override;
};
