

#include "StaminaComponentBase.h"


UStaminaComponentBase::UStaminaComponentBase()
{
	
	PrimaryComponentTick.bCanEverTick = true;
}


void UStaminaComponentBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;
	StaminaRecoverDelay = StaminaRecoverDelayMin;
}


void UStaminaComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStaminaComponentBase::CharacterUpdate()
{
	switch (MovementState)
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
}

void UStaminaComponentBase::ChangeMovementSpeed(bool bCharacterMovement)
{
	if (!WalkEnabled && !SprintRunEnabled && !AimEnabled)
	{
		MovementState = EMovementState::Run_State;
	}

	if (SprintButtonReleased && SprintRunEnabled && CurrentStamina > 0.0f)
	{
		WalkEnabled = false;
		AimEnabled = false;

		MovementState = EMovementState::SprintRun_State;
		if (bCharacterMovement)
		{
			StopRecoveryStamina();
			StartExpenceStamina();
		}
		else
		{
			StopExpenceStamina();
			StartRecoveryStamina();
		}

	}

	if (SprintRunEnabled && CurrentStamina <= 0)
	{
		StopExpenceStamina();
		WalkEnabled = false;
		AimEnabled = false;
		MovementState = EMovementState::Run_State;
		StartRecoveryStamina();
	}

	if (!SprintRunEnabled && CurrentStamina < MaxStamina)
	{
		StopExpenceStamina();
		StartRecoveryStamina();
	}

	if (WalkEnabled && !SprintRunEnabled && AimEnabled)
	{
		MovementState = EMovementState::AimWalk_State;
	}

	if (WalkEnabled && !SprintRunEnabled && !AimEnabled)
	{
		MovementState = EMovementState::Walk_State;
	}

	if (!WalkEnabled && !SprintRunEnabled && AimEnabled)
	{
		MovementState = EMovementState::Aim_State;
	}
}

void UStaminaComponentBase::ExpenceStamina()
{
	if (CurrentStamina >= 0.0f)
	{
		CurrentStamina -= StaminaExpenceRate;
	}
}

void UStaminaComponentBase::RecoveryStamina()
{
	if (CurrentStamina < MaxStamina)
	{
		CurrentStamina += StaminaRecoverRate;
	}
	else
	{
		StopRecoveryStamina();
	}
}

void UStaminaComponentBase::StartRecoveryStamina()
{
	if (CurrentStamina <= 0)
	{
		StaminaRecoverDelay = StaminaRecoverDelayMax;

		if(SprintButtonReleased)
			SprintButtonReleased = false;
	}
	else
	{
		StaminaRecoverDelay = StaminaRecoverDelayMin;
	}
	if (!GetWorld()->GetTimerManager().IsTimerActive(StaminaRecoverTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimer, this, &UStaminaComponentBase::RecoveryStamina,
			StaminaRecoverTime, true, StaminaRecoverDelay);
	}
}

void UStaminaComponentBase::StartExpenceStamina()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(StaminaExpenceTimer))
	{
		GetWorld()->GetTimerManager().SetTimer(StaminaExpenceTimer, this, &UStaminaComponentBase::ExpenceStamina,
			StaminaExpenceTime, true, 0.0f);
	}
}

void UStaminaComponentBase::StopRecoveryStamina()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(StaminaRecoverTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);
	}
}

void UStaminaComponentBase::StopExpenceStamina()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(StaminaExpenceTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaExpenceTimer);
	}
}