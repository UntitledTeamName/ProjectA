// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PAPlayerController.h"
#include "UI/PAUserWidgetHUD.h"

APAPlayerController::APAPlayerController()
{

	// Widget Component
	static ConstructorHelpers::FClassFinder<UUserWidget> UserWidgetHUDRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ProjectA/Blueprints/UI/WBP_PAHUD.WBP_PAHUD_C'"));
	if (UserWidgetHUDRef.Class)
	{
		UserWidgetHUD = CreateWidget<UUserWidget>(GetWorld(), UserWidgetHUDRef.Class);
		if (UserWidgetHUD)
		{
			UserWidgetHUD->AddToViewport();
		}
	}
}

void APAPlayerController::BeginPlay()
{

	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}
