#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Human.generated.h"

#define HIT_DURATION_TIME 0.1f

class UCapsuleComponent;
class UHealthBarComponent;
class AFoodPlayer;

UCLASS()
class EATWARS_API AHuman : public APawn {
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

	bool IsMoving();

	void SetHp(float Value);

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent *Mesh;

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
