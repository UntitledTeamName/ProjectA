// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PAAnimNotify_Jump.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAAnimNotify_Jump : public UAnimNotify
{
	GENERATED_BODY()
	

protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

};
