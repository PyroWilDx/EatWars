#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attacks.generated.h"

#define MIN_TIME_BETWEEN_HITS 0.2f

class UCapsuleComponent;
class AFoodPlayer;

UCLASS()
class EATWARS_API AAttacks : public AActor {
	GENERATED_BODY()
	
public:	
	AAttacks();

	AAttacks(FName meshPath);

	virtual void Tick(float DeltaTime) override;

	UCapsuleComponent *GetCapsuleComponent();

	void SetThrower(AFoodPlayer *Value);

	float GetDamage();

	void IncrHitCount();

	bool ShouldHit();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	AFoodPlayer *Thrower;

	UPROPERTY(EditAnywhere, Category = "Property")
	bool DestroyAfterMaxHit;

	UPROPERTY(EditAnywhere, Category = "Property")
	float LivingDuration;
	float TimeSinceCreation;

	UPROPERTY(EditAnywhere, Category = "Property")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Property")
	int MaxHitCount;
	int HitCount;

	float TimeSinceLastHit;
};
