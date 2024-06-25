// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PathFindingBase.h"
#include "BFS.generated.h"

/**
 * 
 */
UCLASS()
class PATHFINDINGALGO_API UBFS : public UPathFindingBase
{
	GENERATED_BODY()
	
public:

	UBFS();

	virtual void FindPath(FVector StartPos, FVector TargetPos) override;

	TQueue<class ATile*> OpenTileQueue;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
