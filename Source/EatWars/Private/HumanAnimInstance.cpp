#include "HumanAnimInstance.h"
#include "Human.h"
#include "FoodPlayer.h"

void UHumanAnimInstance::NativeInitializeAnimation() {
	Super::NativeInitializeAnimation();

	Human = Cast<AHuman>(TryGetPawnOwner());
}

void UHumanAnimInstance::NativeUpdateAnimation(float DeltaTime) {
	Super::NativeUpdateAnimation(DeltaTime);

	if (Human) {
		AActor *ClosestFood = Human->GetClosestFood();
		if (ClosestFood != nullptr) {
			ClosestFoodLocation = ClosestFood->GetActorLocation();
		} else {
			ClosestFoodLocation = Human->GetActorLocation();
		}
		IsMoving = Human->IsMoving();
	}
}
