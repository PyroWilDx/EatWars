#include "Attacks.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "FoodPlayer.h"
#include "Components/BoxComponent.h"

AAttacks::AAttacks() {
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SetRootComponent(CapsuleComponent);
	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetGenerateOverlapEvents(false);
	CapsuleComponent->SetNotifyRigidBodyCollision(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(CapsuleComponent);
	Mesh->SetGenerateOverlapEvents(false);

	DestroyAfterMaxHit = false;

	LivingDuration = 0.f;
	TimeSinceCreation = 0.f;

	Damage = 0.f;

	MaxHitCount = 1;
	HitCount = 0;

	TimeSinceLastHit = MIN_TIME_BETWEEN_HITS;

	MultipleActorHit = false;
	HitActors = std::unordered_map<AActor *, int>();
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

	TimeSinceLastHit += DeltaTime;
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
	TimeSinceLastHit = 0.f;
}

bool AAttacks::ShouldHit(AActor *Actor) {
	bool Result = (HitCount < MaxHitCount);
	Result = Result && (TimeSinceLastHit > MIN_TIME_BETWEEN_HITS);
	Result = Result || (MultipleActorHit && (!HitActors.contains(Actor) || HitActors[Actor] < MaxHitCount));
	if (Result) {
		if (HitActors.contains(Actor)) HitActors[Actor]++;
		else HitActors[Actor] = 1;
	}
	return Result;
}

void AAttacks::UltGrow(UBoxComponent *UltBox, float DeltaTime) {
	FVector Scale = UltBox->GetComponentScale();
	const double m = 6;
	float c = 1.f + DeltaTime;
	float sX = std::min(Scale.X * c, 1. * m);
	float sY = std::min(Scale.Y * c, 1.4 * m);
	float sZ = std::min(Scale.Z * c, 0.28 * m);
	UltBox->SetWorldScale3D(FVector(sX, sY, sZ));
	FVector Location = UltBox->GetComponentLocation();
	float lX = std::min(Location.X * c, 0. * m);
	float lY = std::min(Location.Y * c, 0. * m);
	float lZ = std::min(Location.Z * c, 10.6 * m);
	UltBox->SetWorldLocation(FVector(lX, lY, lZ));

	Scale = Mesh->GetComponentScale();
	sX = std::min(Scale.X * c, 1. * m);
	sY = std::min(Scale.Y * c, 1. * m);
	sZ = std::min(Scale.Z * c, 1. * m);
	Mesh->SetWorldScale3D(FVector(sX, sY, sZ));
}
