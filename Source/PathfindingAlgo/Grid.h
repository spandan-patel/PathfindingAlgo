// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grid.generated.h"

USTRUCT(BlueprintType)
struct FNested2DArray 
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
		TArray<class ATile*> A;

	class ATile* operator[] (int32 i)
	{
		return A[i];
	}

	void AddTile(ATile* Tile)
	{
		A.Add(Tile);
	}
};

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDINGALGO_API UGrid : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrid();

	void CreateGrid();

	class ATile* GetTileFromWorldPoint(FVector WorldPosition);

	TArray<class ATile*> GetNeighbourTiles(class ATile* Tile);

	void DrawPathDebug();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:

	UPROPERTY(EditAnywhere)
		TArray<FNested2DArray> GridOfLevel;

	UPROPERTY(EditAnywhere)
		FVector2D GridWorldSize;

	UPROPERTY(EditAnywhere)
		float TileRadius;

	UPROPERTY(EditAnywhere)
		float TileDiameter;

	UPROPERTY(EditAnywhere)
		int32 GridSizeX; 
	
	UPROPERTY(EditAnywhere)
		int32 GridSizeY;

	UPROPERTY(EditAnywhere)
		class AActor* Ground;

	UPROPERTY(EditAnywhere)
		class AActor* Player;

	UPROPERTY(EditAnywhere)
		class AActor* NewTempTarget;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> TileToSpawn;

	UPROPERTY(EditAnywhere)
	TArray<class ATile*> Path;

	UPROPERTY(EditAnywhere)
		TArray<class ATile*> VisitedPath;
};
