// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterBase.h"

// Sets default values
APACharacterBase::APACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

