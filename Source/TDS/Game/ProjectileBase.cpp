

#include "ProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"


AProjectileBase::AProjectileBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	BulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	BulletCollision->SetSphereRadius(16.f);

	BulletCollision->OnComponentHit.AddDynamic(this, &AProjectileBase::BulletCollisionSphereHit);
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::BulletCollisionSphereBeginOverlap);
	BulletCollision->OnComponentEndOverlap.AddDynamic(this, &AProjectileBase::BulletCollisionSphereEndOverlap);

	BulletCollision->bReturnMaterialOnMove = true;
	BulletCollision->SetCanEverAffectNavigation(false);

	RootComponent = BulletCollision;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Projectile Mesh"));
	BulletMesh->SetupAttachment(RootComponent);
	BulletMesh->SetCanEverAffectNavigation(false);

	BulletFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailBulletVFX"));
	BulletFX->SetupAttachment(RootComponent);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	BulletMovement->UpdatedComponent = RootComponent;
	BulletMovement->InitialSpeed = 1.f;
	BulletMovement->MaxSpeed = 0.f;
	BulletMovement->bRotationFollowsVelocity = true;
}

void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileBase::BulletCollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulce, const FHitResult& Hit)
{
}

void AProjectileBase::BulletCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
}

void AProjectileBase::BulletCollisionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
}

