
// Fill out your copyright notice in the Description page of Project Settings.

#include "NetWork/PAHttpDownloadManager.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Json.h"
#include "JsonUtilities.h"

UPAHttpDownloadManager::UPAHttpDownloadManager()
{
}

void UPAHttpDownloadManager::FetchGoogleSheetData()
{
    // HTTP Module ��������
    FHttpModule* Http = &FHttpModule::Get();

    // HTTP Request ����
    TSharedRef<IHttpRequest> Request = Http->CreateRequest();

    // Google Sheets API URL ����
    FString GoogleSheetID = TEXT("13C5VU1wYk2-a-fvgarkmWjrTmstYMWFrjz4odifs03s");
    FString GoogleSheetRange = TEXT("Values");
    FString ApiKey = TEXT("AIzaSyCbHmpnJPmgVL6qyXGM78taeMY90bQVLp0");
    FString Url = FString::Printf(TEXT("https://sheets.googleapis.com/v4/spreadsheets/%s/values/%s?key=%s"), *GoogleSheetID, *GoogleSheetRange, *ApiKey);

    Request->SetURL(Url);
    Request->SetVerb("GET");
    Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

    // Request �Ϸ� �� �ݹ� ����
    Request->OnProcessRequestComplete().BindUObject(this, &UPAHttpDownloadManager::OnResponseReceived);

    // Request ����
    Request->ProcessRequest();

    UE_LOG(LogTemp, Log, TEXT("UPAHttpDownloadManager Fetching Google Sheet Data"));
}

void UPAHttpDownloadManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
    UE_LOG(LogTemp, Log, TEXT("UPAHttpDownloadManager OnResponseReceived start"));
    if (bWasSuccessful && Response.IsValid())
    {
        UE_LOG(LogTemp, Log, TEXT("UPAHttpDownloadManager OnResponseReceived valid"));
        FString ResponseString = Response->GetContentAsString();

        // JSON �Ľ�
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);

        if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
        {
            UE_LOG(LogTemp, Log, TEXT("UPAHttpDownloadManager OnResponseReceived deserialized"));
            const TArray<TSharedPtr<FJsonValue>>* Rows;

            if (JsonObject->TryGetArrayField(TEXT("values"), Rows))
            {

                UE_LOG(LogTemp, Log, TEXT("UPAHttpDownloadManager getarrayfield"));
            

                for (const TSharedPtr<FJsonValue>& RowValue : *Rows)
                {
                    const TArray<TSharedPtr<FJsonValue>>& Row = RowValue->AsArray();
                    if (Row.Num() == 2)
                    {
                        FString Key = Row[0]->AsString();
                        float Value = FCString::Atof(*Row[1]->AsString());

                        DataMap.Add(Key, Value);

                       // UE_LOG(LogTemp, Log, TEXT("UPAHttpDownloadManager DataMap added: %s - %f"), *Key, Value);
                    }
                }

                // ������ �α� ���
                for (const TPair<FString, float>& Pair : DataMap)
                {
                    UE_LOG(LogTemp, Log, TEXT("%s: %f"), *Pair.Key, Pair.Value);
                }


                OnDataFetched.Broadcast();
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to deserialize JSON response"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to fetch Google Sheet data"));
    }
}