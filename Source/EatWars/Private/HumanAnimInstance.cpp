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
		if (Human->GetPlayer()) {
			PlayerLocation = Human->GetPlayer()->GetActorLocation();
		}
		IsMoving = Human->IsMoving();
	}
}
