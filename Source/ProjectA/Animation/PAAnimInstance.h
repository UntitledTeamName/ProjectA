// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PAAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API UPAAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPAAnimInstance();

	bool GetbIsRunning() { return bIsRunning; };
	void SetbIsRunning(bool NewValue) {
		bIsRunning = NewValue;
	}

protected:

	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Chracter)
	TObjectPtr<class APACharacterPlayer> Owner;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category = Chracter)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chracter)
	float Speed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chracter)
	float Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chracter)
	bool bEnableJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chracter)
	bool bJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chracter)
	bool bCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Chracter)
	bool bIsRunning;


	



	
};
