#include "FoodPlayer.h"
#include "UObject/UObjectGlobals.h"
#include "Components/CapsuleComponent.h"
#include "Attacks.h"

AFoodPlayer::AFoodPlayer(const FObjectInitializer &ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	ThrowAtkBp = nullptr;
	ThrowAtkCd = 0.2f;
	ThrowAtkTimeAcc = 0.f;
	ThrowAtkPositionAddZ = 60.f;
	ThrowAtkImpulseZ = 0.26f;
	ThrowAtkStrength = 1600.f;

	AnvilAtkBp = nullptr;
	AnvilAtkCd = 1.0f;
	AnvilAtkTimeAcc = 0.f;

	DecoyAtkBp = nullptr;
	DecoyAtkCd = 1.0f;
	DecoyAtkTimeAcc = 0.f;

	UltAtkBp = nullptr;
	UltAtkCd = 1.0f;
	UltAtkTimeAcc = 0.f;
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
	PlayerInputComponent->BindAxis(FName("ThrowAttack"), this, &AFoodPlayer::ThrowAttack);
	PlayerInputComponent->BindAxis(FName("AnvilAttack"), this, &AFoodPlayer::AnvilAttack);
	PlayerInputComponent->BindAxis(FName("DecoyAttack"), this, &AFoodPlayer::DecoyAttack);
	PlayerInputComponent->BindAxis(FName("UltAttack"), this, &AFoodPlayer::UltAttack);
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

void AFoodPlayer::ThrowAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	ThrowAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (ThrowAtkTimeAcc > ThrowAtkCd) {
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z += ThrowAtkPositionAddZ;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AAttacks *Spawned = World->SpawnActor<AAttacks>(ThrowAtkBp, SpawnLocation, SpawnRotation);
			FVector ImpulseDirection = GetActorForwardVector();
			ImpulseDirection.Z = ThrowAtkImpulseZ;
			ImpulseDirection.Normalize();
			Spawned->GetCapsuleComponent()->AddImpulse(ImpulseDirection * ThrowAtkStrength, NAME_None, true);
			ThrowAtkTimeAcc = 0.f;
		}
	}
}

void AFoodPlayer::AnvilAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	AnvilAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (AnvilAtkTimeAcc > AnvilAtkCd) {

		}
	}
}

void AFoodPlayer::DecoyAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	DecoyAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (DecoyAtkTimeAcc > DecoyAtkCd) {

		}
	}
}

void AFoodPlayer::UltAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	UltAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (UltAtkTimeAcc > UltAtkCd) {

		}
	}
}
