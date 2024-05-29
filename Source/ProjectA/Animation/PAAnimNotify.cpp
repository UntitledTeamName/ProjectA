// Fill out your copyright notice in the Description page of Project Settings.


#include "PAAnimNotify.h"
#include "interface/PAMovementInterface.h"

void UPAAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	//UE_LOG(LogTemp, Log, TEXT("animnotify called "));

	if (MeshComp)
	{

		IPAMovementInterface* Player = Cast<IPAMovementInterface>(MeshComp->GetOwner());
		if (Player)
		{
			Player->ToggleProneAnimEnd();
		}
	}

}
