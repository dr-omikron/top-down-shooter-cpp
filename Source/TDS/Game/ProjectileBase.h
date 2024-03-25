
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDS/FuncLibrary/TypesData.h"
#include "ProjectileBase.generated.h"

UCLASS()
class TDS_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectileBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UStaticMeshComponent* BulletMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class USphereComponent* BulletCollision = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	class UProjectileMovementComponent* BulletMovement = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FXComponent")
	class UNiagaraComponent* BulletFX = nullptr;
		
	FProjectileInfo ProjectileASettings;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void BulletCollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulce, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
	void BulletCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
	void BulletCollisionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

};
