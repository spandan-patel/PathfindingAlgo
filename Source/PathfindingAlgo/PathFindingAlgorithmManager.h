// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PathFindingAlgorithmManager.generated.h"

UENUM(BlueprintType)
enum EPathFindingAlgorithmType
{
	BFS,
	DFS,
	DIJKSTRA,
	ASTAR,
};

UENUM(BlueprintType)
enum EDrawPathType
{
	BEGINDRAW,
	TICKDRAW,
};

UCLASS()
class PATHFINDINGALGO_API APathFindingAlgorithmManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APathFindingAlgorithmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UGrid* MyGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UAStarPathFinding* MyAStarPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UDijkstraPathFinding* MyDijkstraPath;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UBFS* MyBFS;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UDFS* MyDFS;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EPathFindingAlgorithmType> CurrentPathFindingAlgorithm;

	UPROPERTY(EditAnywhere)
		TEnumAsByte<EDrawPathType> CurrentDrawPathType;

	FVector SeekerPosTemp;
	FVector TargetPosTemp;

	float CurrentTime = 00.0f;
	int32 DrawTileIndex = 0;
};
