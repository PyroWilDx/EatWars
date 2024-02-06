#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;

UCLASS()
class EATWARS_API ABreakableActor : public AActor {
	GENERATED_BODY()
	
public:
	ABreakableActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent *GeometryCollection;

};
