// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APAPlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	APAPlayerController();



protected:
	virtual void BeginPlay() override;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UUserWidget > UserWidgetHUD;
	
};
