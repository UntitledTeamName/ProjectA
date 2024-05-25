// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/PAAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PACharacterPlayer.h"

UPAAnimInstance::UPAAnimInstance()
{

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
		bCrouching = Owner->bIsCrouched;
		bEnableJump = Owner->GetVelocity().Z > 0;
		bJumping = Owner->GetVelocity().Z > 0 ? true : false;
		bIsRunning = Owner->GetbIsRunning();

		//UE_LOG(LogTemp, Log, TEXT("bisRunning  = %d"), bIsRunning);
		//UE_LOG(LogTemp, Log, TEXT("velocity = %f , Speed = %f"), Owner->GetVelocity().Z, Speed);
	}
	
}
