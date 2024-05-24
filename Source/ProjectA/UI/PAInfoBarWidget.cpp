// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PAInfoBarWidget.h"
#include "Components/ProgressBar.h"


UPAInfoBarWidget::UPAInfoBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	MaxHp = -1.0f;
}

void UPAInfoBarWidget::NativeConstruct()
{

	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	ensure(HpProgressBar);
	


}

void UPAInfoBarWidget::UpdateHpBar(float NewCurrentHp)
{
	ensure(MaxHp > 0.0f);
	if (HpProgressBar)
	{
		HpProgressBar->SetPercent(NewCurrentHp / MaxHp);
	}

}
