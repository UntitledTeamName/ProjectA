// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PACharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PACharacterControlData.h"
#include "Physics/PACollision.h"
#include "Blueprint/UserWidget.h"
#include "Game/PAGameInstance.h"
#include "Components/WidgetComponent.h"
#include "Components/PACharacterStatComponent.h"


// Sets default values
APACharacterBase::APACharacterBase()
{

	UE_LOG(LogTemp, Log, TEXT("APACharacterBase Initializer"));
	// Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->SetCollisionProfileName(CPROFILE_PACAPSULE);

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;


	//GetCharacterMovement()->MaxWalkSpeed = *CastChecked<UPAGameInstance>(GetWorld()->GetGameInstance())->GetHttpDownloadManagerRef()->DataMap.Find("MaxSpeed");
	

	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -96.0f), FRotator(0.0f, -90.0f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ProjectA/Resource/Player/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (CharacterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);
	}


	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/ProjectA/Resource/Player/AnimStarterPack/UE4ASP_HeroTPP_AnimBlueprint.UE4ASP_HeroTPP_AnimBlueprint_C'"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> InfoBarWidgetRef(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/ProjectA/Blueprints/UI/WBP_InfoBar.WBP_InfoBar_C'"));
	if (InfoBarWidgetRef.Class)
	{
		InfoBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
		InfoBar->SetWidgetClass(InfoBarWidgetRef.Class);
	}

	// Stat Component

	Stat = CreateDefaultSubobject<UPACharacterStatComponent>(TEXT("Stat"));

	// Widget Component

	InfoBar->SetupAttachment(GetMesh());
	InfoBar->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));

	InfoBar->SetWidgetSpace(EWidgetSpace::Screen);
	InfoBar->SetDrawSize(FVector2D(300.0f, 75.0f));
	InfoBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	
}

// Called when the game starts or when spawned
void APACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("APACharacterBase BeginPlay"));

	
	if (IsLocallyControlled())
	{
		InfoBar->DestroyComponent(); 
	}
	
}

// Called every frame
void APACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APACharacterBase::SetCharacterControlData(const UPACharacterControlData* CharacterControlData)
{
	// Pawn
	bUseControllerRotationYaw = CharacterControlData->bUseControllerRotationYaw;

	// CharacterMovement
	GetCharacterMovement()->bOrientRotationToMovement = CharacterControlData->bOrientRotationToMovement;
	GetCharacterMovement()->bUseControllerDesiredRotation = CharacterControlData->bUseControllerDesiredRotation;
	GetCharacterMovement()->RotationRate = CharacterControlData->RotationRate;

}


