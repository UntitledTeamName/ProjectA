// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PAUserWidgetHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAUserWidgetHUD : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPAUserWidgetHUD(const FObjectInitializer& ObjectInitializer);



protected:
	virtual void NativeConstruct() override;




public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);
	//void UpdateStaminaBar();


protected:




	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	TObjectPtr<class UProgressBar> StaminaProgressBar;

	UPROPERTY()
	float MaxHp;

	UPROPERTY()
	float MaxStamina;


};
