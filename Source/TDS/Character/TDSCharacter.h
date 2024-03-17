// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDS/Game/WeaponBase.h"
#include "TDSCharacter.generated.h"


UCLASS(Blueprintable)
class ATDSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATDSCharacter();
		
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
	class UStaminaComponentBase* StaminaComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AWeaponBase* CurrentWeapon = nullptr;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Demo")
	TSubclassOf<AWeaponBase> InitWeaponClass = nullptr;
	
	UFUNCTION(BlueprintCallable)
	void ChangeMovementState();

	UFUNCTION(BlueprintCallable)
	bool CharacterMoving() const;

	UFUNCTION(BlueprintCallable)
	void InitWeapon();

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetCurrentWeapon() const { return CurrentWeapon; }

	UFUNCTION(BlueprintCallable)
	void AttackCharacterEvent(bool bIsFiring);

};
