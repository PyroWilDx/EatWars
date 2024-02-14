#include "FoodPlayer.h"
#include "UObject/UObjectGlobals.h"
#include "Components/CapsuleComponent.h"
#include "Attacks.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EatWarsOverlay.h"
#include "Kismet/GameplayStatics.h"

AFoodPlayer::AFoodPlayer(const FObjectInitializer &ObjectInitializer) {
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 2000.f;
	GetCharacterMovement()->AirControl = 0.82f;
	GetCharacterMovement()->StandingDownwardForceScale = 0.2f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	EatWarsOverlayBP = nullptr;
	EatWarsOverlay = nullptr;

	ThrowAtkBp = nullptr;
	ThrowAtkSound = nullptr;
	ThrowAtkCd = 0.2f;
	ThrowAtkTimeAcc = ThrowAtkTimeAcc;
	ThrowAtkPositionAddZ = 100.f;
	ThrowAtkImpulseZ = 0.2f;
	ThrowAtkStrength = 1600.f;

	AnvilAtkBp = nullptr;
	AnvilAtkSound = nullptr;
	AnvilAtkCd = 1.0f;
	AnvilAtkTimeAcc = AnvilAtkCd;

	DecoyAtkBp = nullptr;
	DecoyAtkSound = nullptr;
	DecoyAtkCd = 5.6f;
	DecoyAtkTimeAcc = DecoyAtkCd;
	DecoyAtkPositionAddZ = 160.f;
	DecoyAtkStrength = 30.f;

	UltAtkBp = nullptr;
	UltAtkSound = nullptr;
	UltAtkCd = 22.0f;
	UltAtkTimeAcc = UltAtkCd;
	
	HitNumber = 0;
	KilledHumanCount = 0;
	TotalDamage = 0.f;

	IsDead = false;
}

void AFoodPlayer::BeginPlay() {
	Super::BeginPlay();

	if (EatWarsOverlayBP != nullptr) {
		EatWarsOverlay = CreateWidget<UEatWarsOverlay>(GetWorld(), EatWarsOverlayBP);
		EatWarsOverlay->AddToViewport();
	}
}

void AFoodPlayer::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (EatWarsOverlay != nullptr) {
		if (DecoyAtkTimeAcc < DecoyAtkCd) {
			EatWarsOverlay->SetSkillCdPercent(1.f - DecoyAtkTimeAcc / DecoyAtkCd);
		} else {
			EatWarsOverlay->SetSkillImgAlpha(1.f);
			EatWarsOverlay->SetSkillCdPercent(0.f);
		}
		if (UltAtkTimeAcc < UltAtkCd) {
			EatWarsOverlay->SetUltimateCdPercent(1.f - UltAtkTimeAcc / UltAtkCd);
		} else {
			EatWarsOverlay->SetUltimateImgAlpha(1.f);
			EatWarsOverlay->SetUltimateCdPercent(0.f);
		}
	}
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
		if (ThrowAtkTimeAcc >= ThrowAtkCd) {
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z += ThrowAtkPositionAddZ;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AAttacks *Spawned = World->SpawnActor<AAttacks>(ThrowAtkBp, SpawnLocation, SpawnRotation);
			FVector ImpulseDirection = GetActorForwardVector();
			ImpulseDirection.Z = ThrowAtkImpulseZ;
			ImpulseDirection.Normalize();
			Spawned->GetCapsuleComponent()->AddImpulse(ImpulseDirection * ThrowAtkStrength, NAME_None, true);
			UGameplayStatics::PlaySound2D(this, ThrowAtkSound);
			ThrowAtkTimeAcc = 0.f;
		}
	}
}

void AFoodPlayer::AnvilAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	AnvilAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (AnvilAtkTimeAcc >= AnvilAtkCd) {

		}
	}
}

void AFoodPlayer::DecoyAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	DecoyAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (DecoyAtkTimeAcc >= DecoyAtkCd) {
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z += DecoyAtkPositionAddZ;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AAttacks *Spawned = World->SpawnActor<AAttacks>(DecoyAtkBp, SpawnLocation, SpawnRotation);
			Spawned->SetThrower(this);
			DecoyAtkSet.insert(Spawned);
			FVector ImpulseDirection = GetActorForwardVector();
			ImpulseDirection.Normalize();
			Spawned->GetCapsuleComponent()->AddImpulse(ImpulseDirection * DecoyAtkStrength, NAME_None, true);
			if (EatWarsOverlay != nullptr) {
				EatWarsOverlay->SetSkillImgAlpha(ATK_IMG_ALPHA);
			}
			UGameplayStatics::PlaySound2D(this, DecoyAtkSound);
			DecoyAtkTimeAcc = 0.f;
		}
	}
}

void AFoodPlayer::UltAttack(float Value) {
	UWorld *World = GetWorld();
	float DeltaTime = World->GetDeltaSeconds();
	UltAtkTimeAcc += DeltaTime;
	if (Value != 0.f) {
		if (UltAtkTimeAcc >= UltAtkCd) {
			FVector SpawnLocation = GetActorLocation();
			SpawnLocation.Z -= GetCapsuleComponent()->GetScaledCapsuleHalfHeight() - 4.f;
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AAttacks *Spawned = World->SpawnActor<AAttacks>(UltAtkBp, SpawnLocation, SpawnRotation);
			Spawned->SetThrower(this);
			if (EatWarsOverlay != nullptr) {
				EatWarsOverlay->SetUltimateImgAlpha(ATK_IMG_ALPHA);
			}
			SpawnLocation.Z += 300.f;
			SetActorLocation(SpawnLocation);
			UGameplayStatics::PlaySound2D(this, UltAtkSound);
			UltAtkTimeAcc = 0.f;
		}
	}
}

AActor *AFoodPlayer::GetClosestFoodFromActor(AActor *Actor) {
	AActor *ClosestFood = this;
	float MinDist = Actor->GetDistanceTo(this);
	for (AActor *DecoyAtk : DecoyAtkSet) {
		float CurrDist = Actor->GetDistanceTo(DecoyAtk);
		if (CurrDist < MinDist) {
			ClosestFood = DecoyAtk;
			MinDist = CurrDist;
		}
	}
	return ClosestFood;
}

void AFoodPlayer::RemoveDecoyAtk(AAttacks *DecoyAtk) {
	DecoyAtkSet.erase(DecoyAtk);
}

void AFoodPlayer::IncrStats(float Damage, bool Killed) {
	if (Damage > 0.f) {
		HitNumber++;
		if (Killed) KilledHumanCount++;
		TotalDamage += Damage;
	}
}

FString AFoodPlayer::GetHitNumberString() {
	return FString::Printf(TEXT("Total Hits : %d"), HitNumber);
}

FString AFoodPlayer::GetKilledHumanCountString() {
	return FString::Printf(TEXT("Number of Human Killed : %d"), KilledHumanCount);
}

FString AFoodPlayer::GetTotalDamageString() {
	return FString::Printf(TEXT("Damage Dealt : %.2f (= %d Human)"), TotalDamage, (int) TotalDamage);
}

void AFoodPlayer::SetIsDead(bool Value) {
	IsDead = Value;
}

bool AFoodPlayer::GetIsDead() {
	return IsDead;
}
