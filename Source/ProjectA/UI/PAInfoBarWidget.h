// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PAInfoBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAInfoBarWidget : public UUserWidget
{
	GENERATED_BODY()
	

	UPAInfoBarWidget(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeConstruct() override;





public:
	FORCEINLINE void SetMaxHp(float NewMaxHp) { MaxHp = NewMaxHp; }
	void UpdateHpBar(float NewCurrentHp);
	

protected:

	UPROPERTY()
	TObjectPtr<class UProgressBar> HpProgressBar;

	UPROPERTY()
	float MaxHp;

	UPROPERTY()
	float MaxStamina;
};
