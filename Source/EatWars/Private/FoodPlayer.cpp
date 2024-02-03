#include "FoodPlayer.h"
#include "UObject/UObjectGlobals.h"
#include "Attacks.h"

AFoodPlayer::AFoodPlayer(const FObjectInitializer &ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AFoodPlayer::BeginPlay() {
	Super::BeginPlay();
}

void AFoodPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AFoodPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AFoodPlayer::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AFoodPlayer::MoveRight);
	PlayerInputComponent->BindAxis(FName("MoveJump"), this, &AFoodPlayer::MoveJump);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &AFoodPlayer::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &AFoodPlayer::LookUp);
	PlayerInputComponent->BindAxis(FName("NormalAttack"), this, &AFoodPlayer::NormalAttack);
}

void AFoodPlayer::MoveForward(float Value) {
	if (Value != 0.f) {
		FVector RightVector = GetActorForwardVector();
		AddMovementInput(RightVector, Value);
	}
}

void AFoodPlayer::MoveRight(float Value) {
	if (Value != 0.f) {
		FVector ForwardVector = GetActorRightVector();
		AddMovementInput(ForwardVector, Value);
	}
}

void AFoodPlayer::MoveJump(float Value) {
	if (Value != 0.f) {
		Jump();
	}
}

void AFoodPlayer::Turn(float Value) {
	AddControllerYawInput(Value);
}

void AFoodPlayer::LookUp(float Value) {
	AddControllerPitchInput(Value);
}

void AFoodPlayer::NormalAttack(float Value) {
	if (Value != 0.f) {
		FVector SpawnLocation = GetActorLocation();
		SpawnLocation.Z += 60.f;
		GetWorld()->SpawnActor<AAttacks>(ThrowAttack, SpawnLocation, FRotator::ZeroRotator);
	}
}
