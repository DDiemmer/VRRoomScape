// Fill out your copyright notice in the Description page of Project Settings.

#include "Helper.h"
#include "Engine.h"

void UHelper::Print(FString text_to_print, bool print_to_log, FColor color, float TimeToDisplay)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, TimeToDisplay, color, text_to_print);
	}
	if (print_to_log)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *text_to_print);
	}
}


