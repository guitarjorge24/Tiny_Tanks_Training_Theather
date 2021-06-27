// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectileBase::AProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	// #ToDoJ: does this OnComponentHit work without having to recreate the BP?
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->InitialSpeed = MovementSpeed;
	ProjectileMovementComponent->MaxSpeed = MovementSpeed;
	InitialLifeSpan = 3.f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//#ToDoJ: to delete this var after turning off bUseUnity. Do I need to include Components/StaticMeshComponent.h ?
	FVector Location = ProjectileMesh->GetComponentLocation();
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                            FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* ProjectileOwner = GetOwner(); // The pawn that spawned the projectile. Set in APawnBase::Fire().
	if (!ProjectileOwner) { return; }

	// "OtherActor != this" in case there's components of the projectile that could overlap with itself.
	//  Check that OtherActor is not the owner to avoid applying damage to the pawn that spawned the projectile.
	if (OtherActor && OtherActor != this && OtherActor != ProjectileOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, ProjectileOwner->GetInstigatorController(),
			this, DamageType);
	}

	Destroy();
}