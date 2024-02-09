#include "Attacks.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "FoodPlayer.h"

AAttacks::AAttacks() {
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(CapsuleComponent);

	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetGenerateOverlapEvents(false);
	CapsuleComponent->SetNotifyRigidBodyCollision(true);

	Mesh->SetGenerateOverlapEvents(false);

	DestroyAfterMaxHit = false;

	LivingDuration = 0.f;
	TimeSinceCreation = 0.f;

	Damage = 0.f;

	MaxHitCount = 1;
	HitCount = 0;
}

AAttacks::AAttacks(FName meshPath) : AAttacks() {
	UStaticMesh *StaticMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(),
								nullptr, *meshPath.ToString()));
	Mesh->SetStaticMesh(StaticMesh);
}

void AAttacks::BeginPlay() {
	Super::BeginPlay();
}

void AAttacks::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	TimeSinceCreation += DeltaTime;
	if ((TimeSinceCreation > LivingDuration)
		|| (DestroyAfterMaxHit && HitCount >= MaxHitCount)) {
		Destroy();
	}
}

UCapsuleComponent *AAttacks::GetCapsuleComponent() {
	return CapsuleComponent;
}

void AAttacks::SetThrower(AFoodPlayer *Value) {
	Thrower = Value;
}

float AAttacks::GetDamage() {
	return Damage;
}

void AAttacks::IncrHitCount() {
	HitCount++;
}

bool AAttacks::ShouldHit() {
	return HitCount < MaxHitCount;
}
