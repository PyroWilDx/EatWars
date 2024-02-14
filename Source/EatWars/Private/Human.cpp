#include "Human.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "FoodPlayer.h"
#include "Attacks.h"
#include "HealthBarComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimMontage.h"

AHuman::AHuman() {
	PrimaryActorTick.bCanEverTick = true;

    GetMesh()->SetGenerateOverlapEvents(false);
    GetMesh()->SetNotifyRigidBodyCollision(false);
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    GetCapsuleComponent()->SetGenerateOverlapEvents(false);
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AHuman::NotifyHit);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    GetCharacterMovement()->StandingDownwardForceScale = 0.2f;

    HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBarComponent"));
    HealthBarComponent->SetupAttachment(GetRootComponent());

    DeathAnimMontage = nullptr;

	Player = nullptr;
    Moving = true;

    Hp = 0.f;

    HitMaterial = nullptr;
    HitDurationLeft = 0.f;

    IsDead = false;
}

void AHuman::BeginPlay() {
    Super::BeginPlay();

    Player = Cast<AFoodPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    OriginalMaterial = GetMesh()->GetMaterial(0);

    SetHp(1.f);
}

void AHuman::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

    if (IsDead) return;

    if (HitDurationLeft > 0) {
        HitDurationLeft -= DeltaTime;
        if (HitDurationLeft <= 0) {
            GetMesh()->SetMaterial(0, OriginalMaterial);
        }
    }
}

void AHuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHuman::NotifyHit(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, FVector NormalImpulse,
        const FHitResult &SweepResult) {
    if (IsDead) return;

    if (OtherActor == Player) {
        Player->SetIsDead(true);
        //Player->Destroy();
    } else if (OtherActor->IsA(AAttacks::StaticClass())) {
        AAttacks *Atk = Cast<AAttacks>(OtherActor);
        if (!Atk->ShouldHit(this)) return;
        Atk->IncrHitCount();
        DamageSelf(Atk->GetDamage());
    }
}

void AHuman::DamageSelf(float Damage) {
    if (Hp - Damage <= 0.f) {
        IsDead = true;

        GetPlayer()->IncrStats(Damage, true);
        Destroy();
        return;
    }
    if (Damage > 0.f) GetMesh()->SetMaterial(0, HitMaterial);
    if (Damage < 0.f) GetMesh()->SetMaterial(0, HealMaterial);
    HitDurationLeft = HIT_DURATION_TIME;
    SetHp(Hp - Damage);
    Hp = std::min(Hp, 1.f);
    GetPlayer()->IncrStats(Damage, false);
}

AFoodPlayer *AHuman::GetPlayer() {
    return Player;
}

AActor *AHuman::GetClosestFood() {
    if (Player != nullptr) {
        return Player->GetClosestFoodFromActor(this);
    }
    return nullptr;
}

bool AHuman::IsMoving() {
    return Moving;
}

void AHuman::SetHp(float Value) {
    Hp = Value;
    HealthBarComponent->SetHealthPercent(Hp);
}

void AHuman::OnMontageEnded(UAnimMontage *Montage, bool bInterrupted) {
    Destroy();
}

bool AHuman::GetIsDead() {
    return IsDead;
}
