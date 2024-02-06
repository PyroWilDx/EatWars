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

	TimeSinceCreation = 0.f;
	LivingDuration = 0.f;

	Damage = 0.f;

	HasHit = false;

	CapsuleComponent->SetGenerateOverlapEvents(false);
	//CapsuleComponent->OnComponentHit.AddDynamic(this, &AAttacks::NotifyHit);
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

//void AAttacks::NotifyHit(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
//		UPrimitiveComponent *OtherComp, FVector NormalImpulse,
//		const FHitResult &SweepResult) {
//		HasHit = true;
//}

UCapsuleComponent *AAttacks::GetCapsuleComponent() {
	return CapsuleComponent;
}

float AAttacks::GetDamage() {
	return Damage;
}

void AAttacks::SetHasHitTrue() {
	HasHit = true;
}

bool AAttacks::GetHasHit() {
	return HasHit;
}
