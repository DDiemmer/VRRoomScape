// Fill out your copyright notice in the Description page of Project Settings.


#include "GeniusGame.h"

#include <VRRoomScape/Helper.h>

// Sets default values
AGeniusGame::AGeniusGame()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//scene root 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	//genius mesh 
	geniusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GeniusMesh"));
	geniusMesh->SetupAttachment(RootComponent);
	//create button child actors 
	buttonsStartActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("StartButton"));
	buttonsStartActor->SetupAttachment(RootComponent);

	UChildActorComponent* buttonsRedActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("RedButton"));
	buttonsRedActor->SetupAttachment(RootComponent);
	UChildActorComponent* buttonsBlueActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("BlueButton"));
	buttonsBlueActor->SetupAttachment(RootComponent);
	UChildActorComponent* buttonsGreenActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("GreenButton"));
	buttonsGreenActor->SetupAttachment(RootComponent);

	buttonsActors.Add(buttonsRedActor);
	buttonsActors.Add(buttonsBlueActor);
	buttonsActors.Add(buttonsGreenActor);
}

// Called when the game starts or when spawned
void AGeniusGame::BeginPlay()
{
	Super::BeginPlay();
}

void AGeniusGame::Initialize()
{
	for (size_t i = 0; i < buttonsActors.Num(); i++)
	{
		AActor* buttonActor = Cast<AActor>(buttonsActors[i]->GetChildActor());
		if (buttonActor != nullptr) {
			APushButton* cppPushbuttonClass = Cast<APushButton>(buttonActor);
			buttonsPush.Add(cppPushbuttonClass);
		}
	}

	AActor* buttonStartActor = Cast<AActor>(buttonsStartActor->GetChildActor());
	if (buttonStartActor != nullptr) {
		APushButton* cppPushbuttonClass = Cast<APushButton>(buttonStartActor);
		buttonStart = cppPushbuttonClass;
	}
}

void AGeniusGame::GlowAll()
{
	if (buttonStart != nullptr)
		buttonStart->SetButtonManager(this, 0);

	for (size_t i = 0; i < buttonsPush.Num(); i++)
	{
		UHelper::Print(FString::FromInt(i));
		if (buttonsPush[i] != nullptr) {
			buttonsPush[i]->UpdateButtonMaterial();
			buttonsPush[i]->GlowButton(0.5f, 4);

			buttonsPush[i]->SetButtonManager(this, i + 1);
		}
	}
}

void AGeniusGame::OnClick_Implementation(APushButton* pushButton, int idButton)
{
	UHelper::Print(FString::FromInt(idButton));
	if (idButton == 0 && !finishGame) {
		butttonBlinkOrder.Empty();
		SetButtonBlink();
	}
	else if (inGame) {
		ClickCheck(idButton);
	}
}

void AGeniusGame::SetButtonBlink()
{
	if (butttonBlinkOrder.Num() == 0)
	{
		itClicks = 0;
		for (size_t i = 0; i < startNumBlink; i++)
		{
			AddButtonOrder();
		}
	}
	else if (butttonBlinkOrder.Num() < maxNumBlink) {
		AddButtonOrder();
	}
	else {
		WinAction();
		return;
	}
	BlinkOrder();
}

void AGeniusGame::AddButtonOrder()
{
	int num = FMath::RandRange(1, buttonsPush.Num());
	butttonBlinkOrder.Add(num);
}

void AGeniusGame::BlinkOrder()
{
	float timeToBlink = 0;
	float timeToDark = 0.7f;

	for (size_t i = 0; i < butttonBlinkOrder.Num(); i++)
	{
		//button id 
		int idB = butttonBlinkOrder[i];
		timeToBlink = (timeToDark * i) + (0.7f * i) + 0.5f;

		FTimerHandle UniqueHandle;
		FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &AGeniusGame::BlinkButton, idB - 1, timeToDark, i == butttonBlinkOrder.Num() - 1);
		GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, timeToBlink, false);
	}
}

void AGeniusGame::BlinkButton(int idButton, float timeToDark, bool isLastToblink)
{
	buttonsPush[idButton]->GlowButton(timeToDark);
	if (isLastToblink)
		inGame = true;
}

void AGeniusGame::ClickCheck(int idButton)
{
	//check num button with it and buttonBlinkOrder 
	bool sameButton = (idButton == butttonBlinkOrder[itClicks]);
	//right button
	if (sameButton)
	{
		itClicks++;

		if (itClicks == butttonBlinkOrder.Num())
		{
			//star order again 
			itClicks = 0;
			//Add num on blick order 
			SetButtonBlink();
		}
		//else	
		//just wait until finish or missed the button
	}
	else {
		ErrorAction();
	}
}

void AGeniusGame::ErrorAction()
{
	UHelper::Print("Error button ");
	inGame = false;
}
void AGeniusGame::WinAction()
{
	UHelper::Print("win Genius");
	inGame = false;
	finishGame = true;
	GlowAll();
}
