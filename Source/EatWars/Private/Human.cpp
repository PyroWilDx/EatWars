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

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SetRootComponent(Mesh);

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetupAttachment(GetRootComponent());

    HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBarComponent"));
    HealthBarComponent->SetupAttachment(GetRootComponent());

	Player = nullptr;
    MovementSpeed = 300.f;

    Hp = 0.f;

    HitMaterial = nullptr;
    HitDurationLeft = 0.f;

    RotationSpeed = 60000.f;
    CapsuleComponent->SetGenerateOverlapEvents(false);
    CapsuleComponent->OnComponentHit.AddDynamic(this, &AHuman::NotifyHit);
    CapsuleComponent->SetNotifyRigidBodyCollision(true);
    CapsuleComponent->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void AHuman::BeginPlay() {
    Super::BeginPlay();

    Player = Cast<AFoodPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    OriginalMaterial = Mesh->GetMaterial(0);

    SetHp(1.f);
}

void AHuman::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

    if (Player) {
        FVector PlayerLocation = Player->GetActorLocation();
        FVector Location = GetActorLocation();
        FRotator Rotation = GetActorRotation();

        FVector Direction = PlayerLocation - Location;
        Direction.Normalize();
        FVector TargetLocation = Location + Direction * MovementSpeed * DeltaTime;
        TargetLocation.Z = Location.Z;
        SetActorLocation(TargetLocation);
        Moving = true;

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
            Mesh->SetMaterial(0, OriginalMaterial);
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
        Mesh->SetMaterial(0, HitMaterial);
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