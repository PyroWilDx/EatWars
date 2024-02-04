#include "Attacks.h"
#include "Components/CapsuleComponent.h"

AAttacks::AAttacks() {
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(CapsuleComponent);

	TimeSinceCreation = 0.f;
	LivingDuration = 0.f;

	Damage = 0.f;

	CapsuleComponent->SetGenerateOverlapEvents(false);
	CapsuleComponent->SetNotifyRigidBodyCollision(true);
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
	if (TimeSinceCreation > LivingDuration) {
		Destroy();
	}
}

UCapsuleComponent *AAttacks::GetCapsuleComponent() {
	return CapsuleComponent;
}

float AAttacks::GetDamage() {
	return Damage;
}
