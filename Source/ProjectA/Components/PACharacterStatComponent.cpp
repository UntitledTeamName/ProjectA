// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PACharacterStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Game/PAGameInstance.h"
#include "NetWork/PAHttpDownloadManager.h"

// Sets default values for this component's properties
UPACharacterStatComponent::UPACharacterStatComponent()
{
	
	MaxHp = 200.0f;
	SetHp(MaxHp);

	//WalkSpeed = 500.0f;
	RunSpeed = 700.f;

	SetIsReplicated(true);
	
}


// Called when the game starts
void UPACharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetHp(MaxHp);

	UPAHttpDownloadManager* DownloadManager;
	DownloadManager = (Cast<UPAGameInstance>(GetWorld()->GetGameInstance()))->GetHttpDownloadManagerRef();
	if (DownloadManager)
	{

		DownloadManager->OnDataFetched.AddDynamic(this, &UPACharacterStatComponent::SetStatFromFetchedData);
	}
	
}

float UPACharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	


	return ActualDamage;
}

void UPACharacterStatComponent::SetStatFromFetchedData()
{
	UE_LOG(LogTemp, Log, TEXT("SetStatFromFetcehdData"));
	WalkSpeed = *(Cast<UPAGameInstance>(GetWorld()->GetGameInstance()))->GetHttpDownloadManagerRef()->DataMap.Find("MaxSpeed");
	
}

void UPACharacterStatComponent::SetHp(float NewHp)
{

	CurrentHp = FMath::Clamp<float>(NewHp, 0.0f, MaxHp);

	OnHpChanged.Broadcast(CurrentHp);
}



void UPACharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPACharacterStatComponent, WalkSpeed);
	DOREPLIFETIME(UPACharacterStatComponent, RunSpeed);


}



