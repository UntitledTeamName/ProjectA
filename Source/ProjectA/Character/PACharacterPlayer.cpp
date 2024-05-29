// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/PACharacterStatComponent.h"
#include "InputMappingContext.h"
#include "Character/PACharacterControlData.h"
#include "EnhancedInputComponent.h"
#include "Components/WidgetComponent.h"
#include "Animation/PAAnimInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Player/PAPlayerController.h"
#include "Net/UnrealNetwork.h"

APACharacterPlayer::APACharacterPlayer()
{
	// Camera
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	// 컨트롤러와 카메라붐 회전 동기화 
	CameraBoom->bUsePawnControlRotation = true;

	TPPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TPPCamera"));
	TPPCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// 컨트롤러와 카메라 회전 동기화
	TPPCamera->bUsePawnControlRotation = true;


	/*
	FPPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPPCamera"));
	FPPCamera->SetupAttachment(GetMesh());
	FPPCamera->SetRelativeLocation(FVector(0.0f, 15.0f, 0.0f));
	FPPCamera->SetRelativeRotation(FRotator(0.0f, 90.0f, -90.0f));
	*/
	bReplicates = true;
	

	// ConstructorHelpers Section

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_Jump.IA_Jump'"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_Move.IA_Move'"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_Look.IA_Look'"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> CrouchActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_Crouch.IA_Crouch'"));
	if (nullptr != CrouchActionRef.Object)
	{
		CrouchAction = CrouchActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> SprintActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_Sprint.IA_Sprint'"));
	if (nullptr != SprintActionRef.Object)
	{
		SprintAction = SprintActionRef.Object;
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> ProneActionRef(TEXT("/Script/EnhancedInput.InputAction'/Game/ProjectA/Input/Actions/IA_Prone.IA_Prone'"));
	if (nullptr != ProneActionRef.Object)
	{
		ProneAction = ProneActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> RifleMeshRef(TEXT("/Game/ProjectA/Resource/MilitaryWeapDark/Weapons/Assault_Rifle_B.Assault_Rifle_B"));
	if (RifleMeshRef.Succeeded())
	{

		USkeletalMeshComponent* RifleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RifleMesh"));
		RifleMesh->SetSkeletalMesh(RifleMeshRef.Object);

		RifleMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Weapon_Socket"));

	}


	static ConstructorHelpers::FObjectFinder<UPACharacterControlData> ThirdPersonDataRef(TEXT("/Script/ProjectA.PACharacterControlData'/Game/ProjectA/CharacterControl/PAC_ThirdPerson.PAC_ThirdPerson'"));
	if (ThirdPersonDataRef.Object)
	{
		CharacterControlManager.Add(ECharacterControlType::ThirdPerson, ThirdPersonDataRef.Object);
	}

	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Script/EnhancedInput.InputMappingContext'/Game/ProjectA/Input/IMC_Default.IMC_Default'"));
	if (nullptr != InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}


	CurrentCharacterControlType = ECharacterControlType::ThirdPerson;


	// Stamina Section

	MaxStamina = 500.0f;
	CurrentStamina = 500.0f;
	StaminaDrainTime = 5.0f;
	StaminaRefillTime = 5.0f;
	DelayBeforeRefill = 20.0f;

	bIsSprinting = false;
	bIsProning = false;
	bCanSprint = true;
	bCanJump = true;


}

void APACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();


	SetCharacterControl(CurrentCharacterControlType);

}

void APACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!bIsCrouched)
	UpdateStamina();

	UE_LOG(LogTemp, Log, TEXT("bcansprint %d"), bCanSprint);

}

void APACharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	

	// 인풋 액션 바인딩
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APACharacterPlayer::StopJumping);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::Look);

	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::StartCrouch);
	EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &APACharacterPlayer::StopCrouch);

	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &APACharacterPlayer::StartSprint);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &APACharacterPlayer::StopSprint);
	

	EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Started, this, &APACharacterPlayer::ToggleProne);



}

void APACharacterPlayer::SetCharacterControl(ECharacterControlType NewCharacterControlType)
{
	
	if (!IsLocallyControlled())
	{
		return;
	}
	

	UPACharacterControlData* NewCharacterControl = CharacterControlManager[NewCharacterControlType];

	check(NewCharacterControl);

	SetCharacterControlData(NewCharacterControl);

	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		UInputMappingContext* NewMappingContext = NewCharacterControl->InputMappingContext;
		if (NewMappingContext)
		{
			Subsystem->AddMappingContext(NewMappingContext, 0);
			//UE_LOG(LogTemp, Log, TEXT("enhancedInputMapped"));
		}
	}

}

void APACharacterPlayer::SetCharacterControlData(const UPACharacterControlData* CharacterControlData)
{
	Super::SetCharacterControlData(CharacterControlData);

	CameraBoom->TargetArmLength = CharacterControlData->TargetArmLength;
	CameraBoom->SetRelativeRotation(CharacterControlData->RelativeRotation);
	CameraBoom->bUsePawnControlRotation = CharacterControlData->bUsePawnControlRotation;
	CameraBoom->bInheritPitch = CharacterControlData->bInheritPitch;
	CameraBoom->bInheritYaw = CharacterControlData->bInheritYaw;
	CameraBoom->bInheritRoll = CharacterControlData->bInheritRoll;
	CameraBoom->bDoCollisionTest = CharacterControlData->bDoCollisionTest;
}

void APACharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	

}

void APACharacterPlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	APAPlayerController* PC = Cast<APAPlayerController>(GetController());

	// 키 동시입력 제한
	if (PC->IsInputKeyDown(EKeys::W) && PC->IsInputKeyDown(EKeys::S)) return;
	if (PC->IsInputKeyDown(EKeys::A) && PC->IsInputKeyDown(EKeys::D)) return;


	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (bIsSprinting)
	{
		if (MovementVector.Y != 0) MovementVector.Y = 0;
		if (MovementVector.X == -1) MovementVector.X = 1;

		AddMovementInput(ForwardDirection, MovementVector.X);
	}
	else
	{
		if (MovementVector.Y != 0 || MovementVector.X == -1) bCanSprint = false;
	
		
		AddMovementInput(ForwardDirection, MovementVector.X);
		AddMovementInput(RightDirection, MovementVector.Y);

	}
}


void APACharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	
	/* Y축 상하반전하기 위해 네거티브 처리 */
	AddControllerPitchInput(-LookAxisVector.Y);


	// 캐릭터의 회전 동기화
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = Controller->GetControlRotation().Yaw;
	

	if (HasAuthority())
	{
		SetActorRotation(NewRotation);
	}
	else
	{
		ServerSetRotationRPC(NewRotation);
	}
	
}

void APACharacterPlayer::Jump(const FInputActionValue& Value)
{
	if (!bIsProning && !bIsCrouched && bCanJump)
	{
		bPressedJump = true;
		bCanSprint = false;
		JumpKeyHoldTime = 0.0f;
	}
}

void APACharacterPlayer::StopJumping(const FInputActionValue& Value)
{
	if (!bIsProning && !bIsCrouched && bCanJump)
	{
		bPressedJump = false;
		ResetJumpState();
	}
}

void APACharacterPlayer::StartCrouch(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Log, TEXT("STartCrouch"));
	Crouch();
	bIsCrouched = true;
	bCanSprint = false;
}

void APACharacterPlayer::StopCrouch(const FInputActionValue& Value)
{

	UE_LOG(LogTemp, Log, TEXT("uncrouch"));
	UnCrouch();
	
	bIsCrouched = false;
	bCanSprint = true;
}

void APACharacterPlayer::ToggleProne()
{
	bIsProning = !bIsProning;
}

void APACharacterPlayer::ProneAnimEnd()
{
	if (!GetbIsProning())
	{
		GetCharacterMovement()->MaxWalkSpeed = GetStatComponent()->GetStandMoveSpeed();

		bCanSprint = true;
		bCanJump = true;

		UE_LOG(LogTemp, Log, TEXT("Prone to stand called "));
	}

	if (GetbIsProning())
	{
		bCanSprint = false;
		bCanJump = false;
		GetCharacterMovement()->MaxWalkSpeed = GetStatComponent()->GetProneMoveSpeed();
		UE_LOG(LogTemp, Log, TEXT("Stand to prone called "));
	}
}

void APACharacterPlayer::JumpAnimEnd()
{
	bCanSprint = true;
}


void APACharacterPlayer::ClientSetRotationMulticastRPC_Implementation(FRotator NewRotation)
{
	SetActorRotation(NewRotation);

}
void APACharacterPlayer::ServerSetRotationRPC_Implementation(FRotator NewRotation)
{
	SetActorRotation(NewRotation);

	ClientSetRotationMulticastRPC(NewRotation);

}
bool APACharacterPlayer::ServerSetRotationRPC_Validate(FRotator NewRotation)
{
	return true;
}





void APACharacterPlayer::StartSprint(const FInputActionValue& Value)
{
	
	if (GetVelocity().Size() <= KINDA_SMALL_NUMBER )
	{
		bIsSprinting = false;
		
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("stamina %d cansprint %d !bisproning %d !biscrouched %d "), bHasStamina, bCanSprint,! bIsProning, !bIsCrouched);
	if (HasAuthority())
	{
		if (bHasStamina && bCanSprint && !bIsProning && !bIsCrouched )
		{

			GetCharacterMovement()->MaxWalkSpeed = Stat->GetSprintSpeed();
			bIsSprinting = true;
		}
	}
	else
	{
		ServerSprintRPC();
	}

	
}

void APACharacterPlayer::StopSprint(const FInputActionValue& Value)
{
	// Server logic
	if (!bIsCrouched && !bIsProning)
	{
		GetCharacterMovement()->MaxWalkSpeed = Stat->GetStandMoveSpeed();
		UE_LOG(LogTemp, Log, TEXT("sprint stop"));

		bIsSprinting = false;
		bCanSprint = true;
	
	}
		
	
}


void APACharacterPlayer::ServerSprintRPC_Implementation()
{
	if (bHasStamina && bCanSprint && !bIsProning && !bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = Stat->GetSprintSpeed();
		bIsSprinting = true;
	}

	ClientSprintMulticastRPC();
}
bool APACharacterPlayer::ServerSprintRPC_Validate()
{
	if (GetVelocity().Size() <= 710.0f)
		return true;
	else 
		return false;
}

void APACharacterPlayer::ClientSprintMulticastRPC_Implementation()
{
	if (bHasStamina && bCanSprint && !bIsProning && !bIsCrouched)
	{
		GetCharacterMovement()->MaxWalkSpeed = Stat->GetSprintSpeed();
		bIsSprinting = true;
	}

}

void APACharacterPlayer::UpdateStamina()
{
	
		if (bIsSprinting )
		{
			CurrentStamina -= StaminaDrainTime;
			CurrentRefillDelayTime = DelayBeforeRefill;
		}

		if (!bIsSprinting && CurrentStamina < MaxStamina)
		{
			CurrentRefillDelayTime--;
			if (CurrentRefillDelayTime <= KINDA_SMALL_NUMBER)
			{
				CurrentStamina += StaminaRefillTime;
			}
		}

		if (CurrentStamina <= KINDA_SMALL_NUMBER)
		{
			bHasStamina = false;
			bCanSprint = false;
			StopSprint(0.0f);
		}
		else if (CurrentStamina > 300.0f)
		{
			
			bHasStamina = true;
		}
	
}


