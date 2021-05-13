// Fill out your copyright notice in the Description page of Project Settings.

#include "PushButton.h"
#include "Components/BoxComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Helper.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APushButton::APushButton()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	buttonPush = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButtonPush"));
	buttonPush->SetupAttachment(RootComponent);
	limitWall = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LimitWall"));
	limitWall->SetupAttachment(RootComponent);
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	boxCollider->SetupAttachment(RootComponent);

	springForce = CreateDefaultSubobject<UPhysicsConstraintComponent >(TEXT("SpringForce"));
	springForce->SetupAttachment(RootComponent);

	FVector springLocation = FVector(0, 0, 150);
	//configure spring force 
	springForce->ComponentName1.ComponentName = boxCollider->GetFName();
	springForce->ComponentName2.ComponentName = buttonPush->GetFName();
	springForce->SetWorldLocation(springLocation);
	boxCollider->SetWorldLocation(springLocation);
	showLimitWall = true;

	//boxCollider->bGenerateOverlapEvents = true;
	boxCollider->OnComponentEndOverlap.AddDynamic(this, &APushButton::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APushButton::BeginPlay()
{
	Super::BeginPlay();

	if (buttonPushMaterial != nullptr)
		buttonPush->SetMaterial(0, buttonPushMaterial);

	canActive = true;
}

void APushButton::GlowButton(float timeToDark, int amountBlinks)
{
	if (buttonPushMaterial == nullptr)
		return;

	//buttonPush->SetMaterial(0, buttonPushMaterial);

	if (amountBlinks > 0)
		buttonPushMaterial->SetScalarParameterValue(TEXT("Bloom"), maxBloom);

	if (timeToDark > 0 && amountBlinks > 0) {
		FTimerHandle UniqueHandle;
		FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &APushButton::DarkButton,timeToDark,amountBlinks);
		GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, timeToDark, false);
	}
}

void APushButton::DarkButton(float timeToDark, int amountBlinks)
{
	if (buttonPushMaterial == nullptr)
		return;

	buttonPushMaterial->SetScalarParameterValue(TEXT("Bloom"), minBloom);

	if (timeToDark > 0 && amountBlinks > 1)
	{
		FTimerHandle UniqueHandle;
		FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &APushButton::GlowButton, timeToDark, amountBlinks-1);
		GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, timeToDark, false);
	}
}

void APushButton::Initialize(UMaterialInterface* material) {

	//create dynamic material 
	if (buttonPushMaterial == nullptr)
		buttonPushMaterial = UMaterialInstanceDynamic::Create(material, buttonPush);

	//set parameter with Set***ParamaterValue
	buttonPushMaterial->SetVectorParameterValue("BaseColor", buttonPushColor);
	buttonPushMaterial->SetScalarParameterValue("Bloom", minBloom);
	buttonPush->SetMaterial(0, buttonPushMaterial);
	//set limit wall visibility 
	limitWall->SetVisibility(showLimitWall);
}

void APushButton::UpdateButtonMaterial() {

	buttonPushMaterial->SetVectorParameterValue("BaseColor", buttonPushColor);
	buttonPushMaterial->SetScalarParameterValue("Bloom", minBloom);
	buttonPush->SetMaterial(0, buttonPushMaterial);
}

void APushButton::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherComp == buttonPush && canActive) {
		GlowButton(0.3);
		
		if (clickSound != nullptr)
		{
			UGameplayStatics::PlaySoundAtLocation(this, clickSound, GetActorLocation());
		}
		if (buttonManager != nullptr)
			buttonManager->OnClick_Implementation(this, idButton);

		if (timeToReactive > 0) {
			canActive = false;

			FTimerHandle UniqueHandle;
			FTimerDelegate RespawnDelegate = FTimerDelegate::CreateUObject(this, &APushButton::SetCanActive,true);
			GetWorldTimerManager().SetTimer(UniqueHandle, RespawnDelegate, timeToReactive, false);
		}
	}
}

void APushButton::SetButtonManager(TScriptInterface<IButtonManagerInterface> _buttonManager, int id)
{
	buttonManager = _buttonManager;
	idButton = id;
}

void APushButton::SetCanActive(bool active)
{
	canActive = active;
}


