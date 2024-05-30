// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PAAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PACharacterPlayer.h"

UPAAnimInstance::UPAAnimInstance()
{
	bHasRifle = true;

}

void UPAAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<APACharacterPlayer>(GetOwningActor());

	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UPAAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Movement)
	{
		Speed = Owner->GetVelocity().Size();
		Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());
		bIsCrouching = Owner->bIsCrouched;
		bEnableJump = Owner->GetVelocity().Z > 0;
		bIsJumping = Owner->GetVelocity().Z != 0 ? true : false;
		bIsSprinting = Owner->GetbIsSprinting();
		bIsProning = Owner->GetbIsProning();
		bIsAiming = Owner->GetbIsAiming();
		//Pitch = Owner->GetBaseAimRotation().Pitch;

		//UE_LOG(LogTemp, Log, TEXT("bisRunning  = %d"), bIsRunning);
		//UE_LOG(LogTemp, Log, TEXT("velocity = %f , Speed = %f"), Owner->GetVelocity().Z, Speed);
	}
	
}
