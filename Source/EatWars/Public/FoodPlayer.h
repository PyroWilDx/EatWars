#pragma once

#include <unordered_set>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoodPlayer.generated.h"

#define ATK_IMG_ALPHA 0.42f

class FObjectInitializer;
class AAttacks;
class UEatWarsOverlay;
class USoundBase;

UCLASS()
class EATWARS_API AFoodPlayer : public ACharacter {
	GENERATED_BODY()

public:
	AFoodPlayer(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	AActor *GetClosestFoodFromActor(AActor *Actor);

	UFUNCTION(BlueprintCallable)
	void RemoveDecoyAtk(AAttacks *DecoyAtk);

	void IncrStats(float Damage, bool Killed);

	UFUNCTION(BlueprintCallable)
	FString GetHitNumberString();

	UFUNCTION(BlueprintCallable)
	FString GetKilledHumanCountString();

	UFUNCTION(BlueprintCallable)
	FString GetTotalDamageString();

	void SetIsDead(bool Value);

	UFUNCTION(BlueprintCallable)
	bool GetIsDead();

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void MoveJump(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	void ThrowAttack(float Value);

	void AnvilAttack(float Value);

	void DecoyAttack(float Value);

	void UltAttack(float Value);

	UPROPERTY(EditAnyWhere)
	TSubclassOf<UEatWarsOverlay> EatWarsOverlayBP;
	UEatWarsOverlay *EatWarsOverlay;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> ThrowAtkBp;
	UPROPERTY(EditAnywhere, Category = "Attacks")
	USoundBase *ThrowAtkSound;
	float ThrowAtkCd;
	float ThrowAtkTimeAcc;
	float ThrowAtkPositionAddZ;
	float ThrowAtkImpulseZ;
	float ThrowAtkStrength;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> AnvilAtkBp;
	UPROPERTY(EditAnywhere, Category = "Attacks")
	USoundBase *AnvilAtkSound;
	float AnvilAtkCd;
	float AnvilAtkTimeAcc;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> DecoyAtkBp;
	UPROPERTY(EditAnywhere, Category = "Attacks")
	USoundBase *DecoyAtkSound;
	float DecoyAtkCd;
	float DecoyAtkTimeAcc;
	float DecoyAtkPositionAddZ;
	float DecoyAtkStrength;
	std::unordered_set<AAttacks *> DecoyAtkSet;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> UltAtkBp;
	UPROPERTY(EditAnywhere, Category = "Attacks")
	USoundBase *UltAtkSound;
	float UltAtkCd;
	float UltAtkTimeAcc;

	bool IsDead;

	int HitNumber;
	int KilledHumanCount;
	float TotalDamage;
};
