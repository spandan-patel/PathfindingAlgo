// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFindingBase.h"
#include "DFS.generated.h"

/**
 * 
 */
UCLASS()
class PATHFINDINGALGO_API UDFS : public UPathFindingBase
{
	GENERATED_BODY()

public:

	UDFS();

	virtual void FindPath(FVector StartPos, FVector TargetPos) override;

	TArray<class ATile*> OpenTileStack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void RecursiveCheck(class ATile* CurrentTile, class ATile* StartTile, class ATile* TargetTile);
};
