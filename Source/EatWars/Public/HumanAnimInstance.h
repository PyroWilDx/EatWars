#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "HumanAnimInstance.generated.h"

UCLASS()
class EATWARS_API UHumanAnimInstance : public UAnimInstance {
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
	class AHuman *Human;

	UPROPERTY(BlueprintReadOnly)
	FVector PlayerLocation;

	UPROPERTY(BlueprintReadOnly)
	bool IsMoving;
};
