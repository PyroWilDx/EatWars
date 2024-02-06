#include "BreakableActor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

ABreakableActor::ABreakableActor() {
	PrimaryActorTick.bCanEverTick = true;

	GeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("GeometryCollection"));
	SetRootComponent(GeometryCollection);
}

void ABreakableActor::BeginPlay() {
	Super::BeginPlay();
}

void ABreakableActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

