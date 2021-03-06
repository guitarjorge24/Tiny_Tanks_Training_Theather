// Copyright of Jorge Luque

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ToonTanks/Actors/ProjectileBase.h"

#include "PawnBase.generated.h"

class AProjectileBase;
class UStaticMeshComponent;


UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnBase();
	virtual void HandleDestruction();
	
protected:
	/**
 	* @brief Rotate's the turret part of the mesh of the player tank or the enemy turret. 
 	* @param LocationToLookAt Could be the player (from the enemy's POV) or the cursor (from player's POV)
 	*/
	void RotateTurret(FVector LocationToLookAt);
	/** @brief bound to the "Fire" input action. Spawns projectiles. */
	void Fire();

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* HealthComponent; 
#pragma endregion
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;
	UPROPERTY(EditAnywhere, Category="Effects")
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category="Effects")
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UMatineeCameraShake> DeathShake;	
};
