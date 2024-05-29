// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "NetWork/PAHttpDownloadManager.h"
#include "PAGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UPAGameInstance();

public:
	virtual void Init() override;

	UPAHttpDownloadManager* GetHttpDownloadManagerRef() { return HttpDownloadManager; };

protected:
	UPROPERTY()
	TObjectPtr<UPAHttpDownloadManager> HttpDownloadManager;
	

	
};
