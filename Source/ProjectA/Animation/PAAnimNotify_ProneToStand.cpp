// Fill out your copyright notice in the Description page of Project Settings.


#include "PAAnimNotify_ProneToStand.h"
#include "Character/PACharacterPlayer.h"
#include "Components/PACharacterStatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPAAnimNotify_ProneToStand::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	//UE_LOG(LogTemp, Log, TEXT("animnotify called "));

	if (MeshComp)
	{
		if (APACharacterPlayer* Player = Cast<APACharacterPlayer>(MeshComp->GetOwner()))
		{
			if (!Player->GetbIsProning())
			{
				
				Player->GetCharacterMovement()->MaxWalkSpeed = Player->GetStatComponent()->GetStandMoveSpeed();

				UE_LOG(LogTemp, Log, TEXT("Prone to stand called "));
			}
		}
	}

}
