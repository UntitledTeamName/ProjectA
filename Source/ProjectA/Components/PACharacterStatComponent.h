// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "PACharacterStatComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /* CurrentHp */);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTA_API UPACharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPACharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;



	FORCEINLINE float GetMaxHealth() { return MaxHealth; }
	FORCEINLINE float GetCurrentHealth() { return CurrentHealth; }
	FORCEINLINE float GetStandMoveSpeed() { return StandMoveSpeed; }
	FORCEINLINE float GetSprintSpeed() { return MaxSprintSpeed; }
	FORCEINLINE float GetProneMoveSpeed() { return ProneMoveSpeed; }
	FORCEINLINE float GetCurrentMoveSpeed() { return CurrentMoveSpeed; }


	float ApplyDamage(float InDamage);


	UFUNCTION()
	void SetStatFromFetchedData();

protected:
	void SetHp(float NewHp);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;

	UPROPERTY(BlueprintReadOnly, Category = Stat)
	float MaxHealth;

	UPROPERTY(Transient, BlueprintReadOnly, Category = Stat)
	float CurrentHealth;

	//Movement Section

	UPROPERTY(Replicated, BlueprintReadWrite, Category = Movement)
	float CurrentMoveSpeed;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = Movement)
	float StandMoveSpeed;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Movement)
	float CrouchMoveSpeed;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Movement)
	float ProneMoveSpeed;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Movement)
	float MaxSprintSpeed;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Movement)
	float SprintAcceleration;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Movement)
	float JumpPower;

	//Property Section

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float MaxWeight;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float MaxStamina;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float SprintStamina;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float VaultStamina;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float ClimbingStamina;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float StaminaRecovery;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float StaminaRecoveryTime;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float StaminaDecreaseType;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float StaminaDecreaseAmount;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Property)
	float JumpStaminaDecrease;

	// Environment Section

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Environment)
	float InteractionDistance;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Environment)
	float VaultWallLow;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Environment)
	float VaultWallHigh;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Environment)
	float ClimbingLow;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Environment)
	float ClimbingHigh;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Attack)
	float KnifeAttackSpeed;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = Attack)
	float PistolReloadSpeed;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = Attack)
	float ClimbiRifleReloadSpeedngHigh;
	

		
};
