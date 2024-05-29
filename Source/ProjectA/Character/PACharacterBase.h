// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/PACharacterStatComponent.h"
#include "PACharacterBase.generated.h"

UENUM()
enum class ECharacterControlType : uint8
{
	ThirdPerson,
	FirstPerson
};

UENUM()
enum class ECharacterState : uint8
{

	StandIdle,
	StandMoving,
	Sprinting,
	Jumping,
	Vaulting,
	WallClimbing,
	StandFiring,
	StandAiming,
	StandAimFiring,
	StandReloading,
	StandAimReloading,
	StandtoCrouch,
	StandtoProne,
	CrouchIdle,
	CrouchMoving,
	CrouchAiming,
	CrouchAimFiring,
	CrouchReloading,
	CrouchAimReloading,
	CrouchtoStand,
	CrouchtoProne,
	ProneIdle,
	ProneMoving,
	ProneFiring,
	ProneAiming,
	ProneAimFiring,
	ProneReloading,
	ProneAimReloading,
	PronetoStand,
	PronetoCrouch,
	Interaction,
	Death


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

	UPACharacterStatComponent* GetStatComponent() { return Stat; };

protected:
	virtual void SetCharacterControlData(const class UPACharacterControlData* CharacterControlData);


protected:
	
	// Stat Section

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPACharacterStatComponent> Stat;
	

	// Widget Section

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Widget, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent > InfoBar;



	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAccess = "true"))
	TMap<ECharacterControlType, class UPACharacterControlData*> CharacterControlManager;











};
