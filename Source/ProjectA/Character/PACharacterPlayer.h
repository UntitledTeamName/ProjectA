// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PACharacterBase.h"
#include "InputActionValue.h"
#include "PACharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTA_API APACharacterPlayer : public APACharacterBase
{
	GENERATED_BODY()

public:
	APACharacterPlayer();


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool GetbIsRunning() { return bIsRunning; };
	
protected:

	void SetCharacterControl(ECharacterControlType NewCharacterControlType);
	virtual void SetCharacterControlData(const class UPACharacterControlData* CharacterControlData) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)  const override;



	// Camera Section
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> FollowCamera;


	// Input Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))
	
	TObjectPtr<class UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, Meta = (AllowPrivateAccess = "true"))

	TObjectPtr<class UInputAction> SprintAction;


	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartCrouch(const FInputActionValue& Value);
	void StopCrouch(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	


	ECharacterControlType CurrentCharacterControlType;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	float MaxWeight;
	
	UPROPERTY()
	bool bIsRunning;

	bool bCanSprint;


	// Rotation Section

	UFUNCTION(Server,Reliable, WithValidation)
	void ServerSetRotationRPC(FRotator NewRotation);

	UFUNCTION(NetMulticast,Unreliable)
	void ClientSetRotationMulticastRPC(FRotator NewRotation);


	//Sprint Section

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerSprintRPC();

	UFUNCTION(NetMulticast, Unreliable)
	void ClientSprintMulticastRPC();


	
	// Stamina

	void UpdateStamina();

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = Movement)
	float MaxStamina;

	UPROPERTY(Replicated, EditAnywhere,BlueprintReadOnly, Category = Movement)
	float CurrentStamina;

	UPROPERTY(EditAnywhere,Category = Movement)
	float StaminaDrainTime;
	
	UPROPERTY(EditAnywhere,Category = Movement)
	float StaminaRefillTime;

	UPROPERTY(EditAnywhere,Category = Movement)
	float DelayBeforeRefill;

	
	float CurrentRefillDelayTime;

	bool bHasStamina; 






	
};
