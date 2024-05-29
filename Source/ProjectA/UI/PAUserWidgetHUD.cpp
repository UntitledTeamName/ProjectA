// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAUserWidgetHUD.h"
#include "Character/PACharacterPlayer.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

UPAUserWidgetHUD::UPAUserWidgetHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UPAUserWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	ensure(HpProgressBar);
	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("StaminaBar")));
	ensure(StaminaProgressBar);



}


void UPAUserWidgetHUD::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}
}


