// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PathFindingBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDINGALGO_API UPathFindingBase : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPathFindingBase();

	virtual void FindPath(FVector StartPos, FVector TargetPos);

	int32 GetDistance(class ATile* TileA, class ATile* TileB);

	void TracePath(class ATile* StartTile, class ATile* EndTile);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:

	class UGrid* Grid;

	UPROPERTY(EditAnywhere)
		class AActor* Seeker;

	UPROPERTY(EditAnywhere)
		class AActor* Target;

	TArray<class ATile*> VisitedTiles;
};
