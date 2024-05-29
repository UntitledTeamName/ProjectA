// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/PAGameInstance.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"
#include "NetWork/PAHttpDownloadManager.h"


UPAGameInstance::UPAGameInstance()
{


}

void UPAGameInstance::Init()
{
	Super::Init();

    UE_LOG(LogTemp, Log, TEXT("PAGameInstance Init"));
    HttpDownloadManager = NewObject<UPAHttpDownloadManager>(this);

    // 구글 스프레드시트 데이터 가져오기
    if (HttpDownloadManager)
    {
        HttpDownloadManager->FetchGoogleSheetData();

        UE_LOG(LogTemp, Log, TEXT("PAGameInstance Fetch Data"));
    }




}
