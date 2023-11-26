
#include "TDSPlayerController.h"
#include "TDS/Character/TDSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"

ATDSPlayerController::ATDSPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::CardinalCross;
}

void ATDSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter = Cast<ATDSCharacter>(GetCharacter());
}

void ATDSPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	WatchTheCursor();
}

void ATDSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Move, ETriggerEvent::Triggered, this, &ATDSPlayerController::OnMove);
	}
}

void ATDSPlayerController::OnMove(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();
	MovementTick(MovementValue);
}

void ATDSPlayerController::MovementTick(FVector2D MovementValue) const
{
	if (PlayerCharacter)
	{
		PlayerCharacter->AddMovementInput({ 0.f, 1.f, 0.f }, MovementValue.Y);
		PlayerCharacter->AddMovementInput({ 1.f, 0.f, 0.f }, MovementValue.X);
	}
}

void ATDSPlayerController::WatchTheCursor() const
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, HitResult);
	if(PlayerCharacter)
	{
		const FRotator CharacterRotation = UKismetMathLibrary::FindLookAtRotation(PlayerCharacter->GetActorLocation(), HitResult.Location);
		PlayerCharacter->SetActorRotation(FQuat(FRotator(0.0f, CharacterRotation.Yaw, 0.0f)));
	}
	
}
