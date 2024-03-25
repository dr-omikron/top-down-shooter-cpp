
#include "WeaponBase.h"

#include "NiagaraComponent.h"
#include "ProjectileBase.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"


AWeaponBase::AWeaponBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = SceneComponent;

	SkeletalMeshWeapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshWeapon->SetGenerateOverlapEvents(false);
	SkeletalMeshWeapon->SetCollisionProfileName(TEXT("NoCollision"));
	SkeletalMeshWeapon->SetupAttachment(RootComponent);

	StaticMeshWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshWeapon->SetGenerateOverlapEvents(false);
	StaticMeshWeapon->SetCollisionProfileName(TEXT("NoCollision"));
	StaticMeshWeapon->SetupAttachment(RootComponent);

	ShootFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ShootWeaponVFX"));
	ShootFX->SetupAttachment(RootComponent);

	ShootLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootLocation"));
	ShootLocation->SetupAttachment(RootComponent);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	WeaponInit();
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FireTick(DeltaTime);
}

void AWeaponBase::FireTick(float DeltaTime)
{
	if (bWeaponFiring)
		if (FireTime < 0.f)
			Fire();
		else
			FireTime -= DeltaTime;
}

void AWeaponBase::WeaponInit()
{
	if(SkeletalMeshWeapon && !SkeletalMeshWeapon->SkeletalMesh)
	{
		SkeletalMeshWeapon->DestroyComponent();
	}

	if(StaticMeshWeapon && !StaticMeshWeapon->GetStaticMesh())
	{
		StaticMeshWeapon->DestroyComponent();
	}
}

bool AWeaponBase::CheckWeaponCanFire()
{
	return true;
}

FProjectileInfo AWeaponBase::GetProjectile() const
{
	return WeaponSettings.ProjectileSettings;
}

void AWeaponBase::SetWeaponStateFire(bool bIsFire)
{
	if (CheckWeaponCanFire())
		bWeaponFiring = bIsFire;
	else
		bWeaponFiring = false;
}

void AWeaponBase::Fire()
{
	FireTime = WeaponSettings.RateOfFire;

	if(ShootLocation)
	{
		const FVector SpawnLocation = ShootLocation->GetComponentLocation();
		const FRotator SpawnRotation = ShootLocation->GetComponentRotation();
		FProjectileInfo ProjectileInfo;
		ProjectileInfo = GetProjectile();

		if(ProjectileInfo.Projectile)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParameters.Owner = GetOwner();
			SpawnParameters.Instigator = GetInstigator();

			AProjectileBase* SpawnProjectile = Cast<AProjectileBase>(GetWorld()->SpawnActor(ProjectileInfo.Projectile, &SpawnLocation, &SpawnRotation, SpawnParameters));

			if(SpawnProjectile)
			{
				SpawnProjectile->InitialLifeSpan = 20.f;
			}

			if(ShootFX)
			{
				ShootFX->Activate(true);
			}
		}
		else
		{
			//Trace
		}
	}	
	
}