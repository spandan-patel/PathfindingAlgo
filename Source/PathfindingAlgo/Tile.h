// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Tile.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PATHFINDINGALGO_API ATile : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ATile();

	void AssignValue(bool IsWalkable, FVector WorldPos, int32 X, int32 Y);

	int32 GetFCost() const { return GCost + HCost; }

public:
	
	bool Walkable;
	bool IsVisited;

	FVector WorldPosition;

	int32 GridX;
	int32 GridY;

	int32 GCost;
	int32 HCost;

	class ATile* ParentTile;

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* TileMesh;

	class UStaticMeshComponent* GetMesh();

	//void SetTileTransform(FVector Location, float Size);
};
