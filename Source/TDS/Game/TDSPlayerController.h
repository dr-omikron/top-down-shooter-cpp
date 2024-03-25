
#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "TDSPlayerController.generated.h"

UCLASS()
class ATDSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDSPlayerController();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* Move;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	class ATDSCharacter* PlayerCharacter;

	UFUNCTION(BlueprintCallable)
	FVector GetCursorLocation() const;
		
	UFUNCTION()
	void MovementTick(FVector2D MovementValue) const;

	UFUNCTION()
	void WatchTheCursor() const;

protected:
	
	virtual void SetupInputComponent() override;
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION()
	void OnMove(const FInputActionValue& Value);
};


