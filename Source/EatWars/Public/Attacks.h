#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Attacks.generated.h"

class UCapsuleComponent;

UCLASS()
class EATWARS_API AAttacks : public AActor {
	GENERATED_BODY()
	
public:	
	AAttacks();

	AAttacks(FName meshPath);

	static float LivingDuration;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UCapsuleComponent *GetCapsuleComponent();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent *CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *Mesh;

	float TimeSinceCreation;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage;

};
