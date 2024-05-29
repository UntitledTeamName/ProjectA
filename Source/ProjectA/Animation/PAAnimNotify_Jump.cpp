// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PAAnimNotify_Jump.h"
#include "interface/PAMovementInterface.h"

void UPAAnimNotify_Jump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	//UE_LOG(LogTemp, Log, TEXT("animnotify called "));

	if (MeshComp)
	{

		IPAMovementInterface* Player = Cast<IPAMovementInterface>(MeshComp->GetOwner());
		if (Player)
		{
			Player->JumpAnimEnd();
		}
	}
}
