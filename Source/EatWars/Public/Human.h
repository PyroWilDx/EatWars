#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Human.generated.h"

#define HIT_DURATION_TIME 0.12f

class UCapsuleComponent;
class UHealthBarComponent;
class AFoodPlayer;
class UAnimMontage;

UCLASS()
class EATWARS_API AHuman : public ACharacter {
	GENERATED_BODY()

public:
	AHuman();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION()
	void NotifyHit(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, FVector NormalImpulse,
		const FHitResult &SweepResult);

	void DamageSelf(float Damage);
	
	UFUNCTION(BlueprintCallable)
	AFoodPlayer *GetPlayer();

	UFUNCTION(BlueprintCallable)
	AActor *GetClosestFood();

	bool IsMoving();

	void SetHp(float Value);

	void OnMontageEnded(UAnimMontage *Montage, bool bInterrupted);

	UFUNCTION(BlueprintCallable)
	bool GetIsDead();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage *DeathAnimMontage;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthBarComponent *HealthBarComponent;

	AFoodPlayer *Player;
	bool Moving;

	UPROPERTY(EditAnywhere, Category = "Property")
	float Hp;

	UPROPERTY(EditAnywhere, Category = "Visuals")
	UMaterialInterface *HitMaterial;

	UPROPERTY(EditAnywhere, Category = "Visuals")
	UMaterialInterface *HealMaterial;

	UMaterialInterface *OriginalMaterial;

	float HitDurationLeft;

	bool IsDead;
};
