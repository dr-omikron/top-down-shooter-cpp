
#include "TDSCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TDS/Components/StaminaComponentBase.h"


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

	StaminaComponent = CreateDefaultSubobject<UStaminaComponentBase>(TEXT("StaminaComponent"));
	
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATDSCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ATDSCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitWeapon();
}

bool ATDSCharacter::CharacterMoving() const
{
	const FVector2D CharacterGroundVelocity(GetMovementComponent()->Velocity.X, GetMovementComponent()->Velocity.Y);
	if (CharacterGroundVelocity.Length())
		return true;
	return false;
}

void ATDSCharacter::InitWeapon()
{
	if(InitWeaponClass)
	{
		const FVector SpawnLocation = FVector(0);
		const FRotator SpawnRotation = FRotator(0);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.Owner = GetOwner();
		SpawnParameters.Instigator = GetInstigator();

		AWeaponBase* SpawnWeapon = Cast<AWeaponBase>(GetWorld()->SpawnActor(InitWeaponClass, &SpawnLocation, &SpawnRotation, SpawnParameters));
		if(SpawnWeapon)
		{
			FAttachmentTransformRules Rule(EAttachmentRule::SnapToTarget, false);
			SpawnWeapon->AttachToComponent(GetMesh(), Rule, FName("pistol_socket"));
			CurrentWeapon = SpawnWeapon;
			UE_LOG(LogTemp, Warning, TEXT("ATDSCharacter::InitWeapon - Dont Spawn"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ATDSCharacter::InitWeapon - CurrentWeapon = NULL"));
		}
	}
}

void ATDSCharacter::AttackCharacterEvent(bool bIsFiring)
{
	AWeaponBase* Weapon = nullptr;
	Weapon = GetCurrentWeapon();

	if(Weapon)
	{
		Weapon->SetWeaponStateFire(bIsFiring);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATDSCharacter::AttackCharacterEvent - CurrentWeapon = NULL"));
	}
}

void ATDSCharacter::ChangeMovementState()
{
	StaminaComponent->ChangeMovementSpeed(CharacterMoving());
	StaminaComponent->CharacterUpdate();
	GetCharacterMovement()->MaxWalkSpeed = StaminaComponent->ResSpeed;
}

