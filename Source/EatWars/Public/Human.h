#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Human.generated.h"

#define HIT_DURATION_TIME 0.1f

class UCapsuleComponent;
class UHealthBarComponent;
class AFoodPlayer;

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

	AFoodPlayer *GetPlayer();

	UFUNCTION(BlueprintCallable)
	AActor *GetClosestFood();

	bool IsMoving();

	void SetHp(float Value);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UHealthBarComponent *HealthBarComponent;

	AFoodPlayer *Player;
	bool Moving;

	UPROPERTY(EditAnywhere, Category = "Property")
	float Hp;

	UPROPERTY(EditAnywhere, Category = "Visuals")
	UMaterialInterface *HitMaterial;

	UMaterialInterface *OriginalMaterial;

	float HitDurationLeft;

};
