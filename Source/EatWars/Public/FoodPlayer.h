#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FoodPlayer.generated.h"

class FObjectInitializer;

UCLASS()
class EATWARS_API AFoodPlayer : public ACharacter {
	GENERATED_BODY()

public:
	AFoodPlayer(const FObjectInitializer &ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float Value);

	void MoveRight(float Value);

	void MoveJump(float Value);

	void Turn(float Value);

	void LookUp(float Value);

	void NormalAttack(float Value);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
