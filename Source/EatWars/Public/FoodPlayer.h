#pragma once

#include <unordered_set>
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoodPlayer.generated.h"

class FObjectInitializer;
class AAttacks;

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

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> ThrowAtkBp;
	float ThrowAtkCd;
	float ThrowAtkTimeAcc;
	float ThrowAtkPositionAddZ;
	float ThrowAtkImpulseZ;
	float ThrowAtkStrength;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> AnvilAtkBp;
	float AnvilAtkCd;
	float AnvilAtkTimeAcc;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> DecoyAtkBp;
	float DecoyAtkCd;
	float DecoyAtkTimeAcc;
	float DecoyAtkPositionAddZ;
	float DecoyAtkStrength;
	std::unordered_set<AAttacks *> DecoyAtkSet;

	UPROPERTY(EditAnywhere, Category = "Attacks")
	TSubclassOf<AAttacks> UltAtkBp;
	float UltAtkCd;
	float UltAtkTimeAcc;
};
