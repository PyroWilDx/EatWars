#include "Human.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "FoodPlayer.h"
#include "Attacks.h"
#include "HealthBarComponent.h"

AHuman::AHuman() {
	PrimaryActorTick.bCanEverTick = true;

    GetMesh()->SetGenerateOverlapEvents(false);
    GetMesh()->SetNotifyRigidBodyCollision(true);
    GetMesh()->OnComponentHit.AddDynamic(this, &AHuman::NotifyHit);
    GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
    GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    GetCapsuleComponent()->SetGenerateOverlapEvents(false);
    GetCapsuleComponent()->SetNotifyRigidBodyCollision(true);
    GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AHuman::NotifyHit);
    GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

    HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBarComponent"));
    HealthBarComponent->SetupAttachment(GetRootComponent());

	Player = nullptr;
    MovementSpeed = 300.f;

    Hp = 0.f;

    HitMaterial = nullptr;
    HitDurationLeft = 0.f;

    RotationSpeed = 60000.f;
}

void AHuman::BeginPlay() {
    Super::BeginPlay();

    Player = Cast<AFoodPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    OriginalMaterial = GetMesh()->GetMaterial(0);

    SetHp(1.f);
}

void AHuman::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

    if (Player) {
        FVector PlayerLocation = Player->GetActorLocation();
        FVector Location = GetActorLocation();
        FRotator Rotation = GetActorRotation();

        FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Location, PlayerLocation);
        FRotator TargetRotation = FMath::RInterpTo(Rotation, LookAtRotation, DeltaTime, RotationSpeed);
        TargetRotation.Pitch = Rotation.Pitch;
        TargetRotation.Roll = Rotation.Roll;
        TargetRotation.Yaw -= 90.f;
        SetActorRotation(TargetRotation);
    }

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
    if (OtherActor == Player) {
        Player->Destroy();
    } else if (OtherActor->IsA(AAttacks::StaticClass())) {
        AAttacks *Atk = Cast<AAttacks>(OtherActor);
        if (Atk->GetHasHit()) return;
        Atk->SetHasHitTrue();
        GetMesh()->SetMaterial(0, HitMaterial);
        HitDurationLeft = HIT_DURATION_TIME;
        DamageSelf(Atk->GetDamage());
    }
}

void AHuman::DamageSelf(float Damage) {
    if (Hp - Damage <= 0) {
        Destroy();
    }
    SetHp(Hp - Damage);
}

AFoodPlayer *AHuman::GetPlayer() {
    return Player;
}

bool AHuman::IsMoving() {
    return Moving;
}

void AHuman::SetHp(float Value) {
    Hp = Value;
    HealthBarComponent->SetHealthPercent(Hp);
}