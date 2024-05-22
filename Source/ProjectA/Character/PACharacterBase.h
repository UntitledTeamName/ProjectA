// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PACharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	ThirdPerson,
	FirstPerson
};


UCLASS()
class PROJECTA_API APACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void SetCharacterControlData(const class UPACharacterControlData* CharacterControlData);


	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))

	TMap<ECharacterControlType, class UPACharacterControlData*> CharacterControlManager;

};
