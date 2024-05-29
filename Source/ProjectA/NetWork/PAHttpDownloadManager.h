// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "PAHttpDownloadManager.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDataFetched);

UCLASS()
class PROJECTA_API UPAHttpDownloadManager : public UObject
{
	GENERATED_BODY()


public:

	UPAHttpDownloadManager();
	
	UFUNCTION(BlueprintCallable, Category = HTTP)
	void FetchGoogleSheetData();


	UPROPERTY()
	TMap<FString, float> DataMap;

	FOnDataFetched OnDataFetched;

protected:
	
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);



};
