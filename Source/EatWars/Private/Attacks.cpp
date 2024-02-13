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
	const float s1 = 1.32f;
	const float s2 = 1.12f;
	const float w = 20.f;
	const float h = 9.2f;
	float c = 1.f + DeltaTime;
	float sX = Scale.X;
	float sY = Scale.Y;
	float sZ = Scale.Z * c * s1;
	if (sZ > 0.28f * h) {
		sZ = 0.28f * h;
		sX = std::min(sX * c * s2, 1.f * w);
		sY = std::min(sY * c * s2, 1.4f * w);
	}
	UltBox->SetWorldScale3D(FVector(sX, sY, sZ));
	FVector Location = UltBox->GetComponentLocation();
	float lZ = std::min(Location.Z * c * s1, 10.6 * h);
	UltBox->SetRelativeLocation(FVector(0, 0, lZ));

	Scale = Mesh->GetComponentScale();
	sX = Scale.X;
	sY = Scale.Y;
	sZ = Scale.Z * c * s1;
	if (sZ > 1.f * h) {
		sZ = 1.f * h;
		sX = std::min(sX * c * s2, 1.f * w);
		sY = std::min(sY * c * s2, 1.f * w);
	}
	Mesh->SetWorldScale3D(FVector(sX, sY, sZ));
}
