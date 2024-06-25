// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFindingBase.h"
#include "DijkstraPathFinding.generated.h"

/**
 * 
 */
UCLASS()
class PATHFINDINGALGO_API UDijkstraPathFinding : public UPathFindingBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDijkstraPathFinding();

	virtual void FindPath(FVector StartPos, FVector TargetPos) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	TArray<class ATile*> OpenTileSet;
	TSet<class ATile*> ClosedTileSet;
};
