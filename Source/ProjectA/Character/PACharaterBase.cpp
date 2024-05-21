// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharaterBase.h"

// Sets default values
APACharaterBase::APACharaterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APACharaterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APACharaterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APACharaterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

