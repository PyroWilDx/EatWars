#include "Human.h"
#include "Components/CapsuleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "FoodPlayer.h"

AHuman::AHuman() {
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SetRootComponent(Mesh);

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->SetupAttachment(Mesh);


	Player = nullptr;
    MovementSpeed = 200.f;

    RotationSpeed = 100000.f;
    CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AHuman::BeginOverlap);
}

void AHuman::BeginPlay() {
	Super::BeginPlay();

	Player = Cast<AFoodPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
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
}

void AHuman::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AHuman::BeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult &SweepResult) {
    if (OtherActor == Player) {

    }
}

AFoodPlayer *AHuman::GetPlayer() {
    return Player;
}

bool AHuman::IsMoving() {
    return Moving;
}

