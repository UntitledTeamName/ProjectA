// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PACharacterStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Game/PAGameInstance.h"
#include "NetWork/PAHttpDownloadManager.h"

// Sets default values for this component's properties
UPACharacterStatComponent::UPACharacterStatComponent()
{
	
	MaxHealth = 200.0f;
	SetHp(MaxHealth);

	//WalkSpeed = 500.0f;
	MaxSprintSpeed = 700.f;
	ProneMoveSpeed = 100.0f;
	SetIsReplicated(true);
	
}


// Called when the game starts
void UPACharacterStatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SetHp(MaxHealth);

	UPAHttpDownloadManager* DownloadManager;
	DownloadManager = (Cast<UPAGameInstance>(GetWorld()->GetGameInstance()))->GetHttpDownloadManagerRef();
	if (DownloadManager)
	{

		DownloadManager->OnDataFetched.AddDynamic(this, &UPACharacterStatComponent::SetStatFromFetchedData);
	}
	
}

float UPACharacterStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHealth;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0, InDamage);

	SetHp(PrevHp - ActualDamage);
	if (CurrentHealth <= KINDA_SMALL_NUMBER)
	{
		OnHpZero.Broadcast();
	}
	
	return ActualDamage;
}

void UPACharacterStatComponent::SetStatFromFetchedData()
{
	UE_LOG(LogTemp, Log, TEXT("SetStatFromFetcehdData"));
	CurrentMoveSpeed = *(Cast<UPAGameInstance>(GetWorld()->GetGameInstance()))->GetHttpDownloadManagerRef()->DataMap.Find("MaxSpeed");
	StandMoveSpeed = *(Cast<UPAGameInstance>(GetWorld()->GetGameInstance()))->GetHttpDownloadManagerRef()->DataMap.Find("MaxSpeed");

	UE_LOG(LogTemp, Log, TEXT("SetStatFromFetcehdData StandMoveSpeed %f"),StandMoveSpeed);




}

void UPACharacterStatComponent::SetHp(float NewHp)
{

	CurrentHealth = FMath::Clamp<float>(NewHp, 0.0f, MaxHealth);

	OnHpChanged.Broadcast(CurrentHealth);
}



void UPACharacterStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPACharacterStatComponent, StandMoveSpeed);
	DOREPLIFETIME(UPACharacterStatComponent, MaxSprintSpeed);


}



