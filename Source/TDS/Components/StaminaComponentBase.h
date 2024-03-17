
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDS/FuncLibrary/TypesData.h"
#include "StaminaComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TDS_API UStaminaComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

private:

	FTimerHandle StaminaExpenceTimer;

	FTimerHandle StaminaRecoverTimer;

public:
	UStaminaComponentBase();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ExpenceStamina();

	UFUNCTION(BlueprintCallable)
	void RecoveryStamina();

	UFUNCTION(BlueprintCallable)
	void StartRecoveryStamina();

	UFUNCTION(BlueprintCallable)
	void StartExpenceStamina();

	UFUNCTION(BlueprintCallable)
	void StopRecoveryStamina();

	UFUNCTION(BlueprintCallable)
	void StopExpenceStamina();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxStamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CurrentStamina = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaExpenceRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRecoverRate = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRecoverDelay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRecoverDelayMin = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRecoverDelayMax = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaExpenceTime = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float StaminaRecoverTime = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool SprintRunEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool WalkEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool AimEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float ResSpeed = 600.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool SprintButtonReleased = true;

	UFUNCTION(BlueprintCallable)
	void CharacterUpdate();

	UFUNCTION(BlueprintCallable)
	void ChangeMovementSpeed(bool bCharacterMovement);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementState MovementState = EMovementState::Run_State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FCharacterSpeed MovementInfo;
};
