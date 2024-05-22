// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PAPlayerController.h"

void APAPlayerController::BeginPlay()
{

	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
