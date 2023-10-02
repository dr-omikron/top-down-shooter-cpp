
#include "TDSCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ATDSCharacter::ATDSCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false;
	
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false;
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATDSCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ATDSCharacter::CharacterUpdate()
{
	float ResSpeed = 600.0f;
	switch(MovementState)
	{
	case EMovementState::Aim_State: 
		ResSpeed = MovementInfo.AimSpeed;
		break;
	case EMovementState::AimWalk_State:
		ResSpeed = MovementInfo.AimWalkSpeed;
		break;
	case EMovementState::Walk_State: 
		ResSpeed = MovementInfo.WalkSpeed;
		break;
	case EMovementState::Run_State: 
		ResSpeed = MovementInfo.RunSpeed;
		break;
	case EMovementState::SprintRun_State:
		ResSpeed = MovementInfo.SprintRunSpeed;
		break;
	default: 
		break;
	}

	GetCharacterMovement()->MaxWalkSpeed = ResSpeed;
}

void ATDSCharacter::ChangeMovementState()
{
	if(!WalkEnabled && !SprintRunEnabled && !AimEnabled)
	{
		MovementState = EMovementState::Run_State;
	}

	if(SprintRunEnabled)
	{
		WalkEnabled = false;
		AimEnabled = false;
		MovementState = EMovementState::SprintRun_State;
	}

	if(WalkEnabled && !SprintRunEnabled && AimEnabled)
	{
		MovementState = EMovementState::AimWalk_State;
	}

	if(WalkEnabled && !SprintRunEnabled && !AimEnabled)
	{
		MovementState = EMovementState::Walk_State;
	}

	if(!WalkEnabled && !SprintRunEnabled && AimEnabled)
	{
		MovementState = EMovementState::Aim_State;
	}

	CharacterUpdate();
}

