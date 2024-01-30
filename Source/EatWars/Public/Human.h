#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Human.generated.h"

UCLASS()
class EATWARS_API AHuman : public APawn {
	GENERATED_BODY()

public:
	AHuman();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

private:
	class AFoodPlayer *Player;
	bool Moving;

public:
	AFoodPlayer *GetPlayer();

	bool IsMoving();
};
