
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TDS/FuncLibrary/TypesData.h"

#include "WeaponBase.generated.h"



UCLASS()
class TDS_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class USceneComponent* SceneComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class USkeletalMeshComponent* SkeletalMeshWeapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UStaticMeshComponent* StaticMeshWeapon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UArrowComponent* ShootLocation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FXComponent")
	class UNiagaraComponent* ShootFX = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
	FWeaponInfo WeaponSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FireLogic")
	bool bWeaponFiring;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void FireTick(float DeltaTime);

	void WeaponInit();

	bool CheckWeaponCanFire();

	void Fire();

	FProjectileInfo GetProjectile() const;

	UFUNCTION(BlueprintCallable)
	void SetWeaponStateFire(bool bIsFire);

	float FireTime;

};
