// Fill out your copyright notice in the Description page of Project Settings.


#include "AStarPathFinding.h"
#include "Grid.h"
#include "Tile.h"
#include "Algo/Reverse.h"

// Sets default values for this component's properties
UAStarPathFinding::UAStarPathFinding()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAStarPathFinding::FindPath(FVector StartPos, FVector TargetPos)
{
	ATile* StartTile = Grid->GetTileFromWorldPoint(StartPos);
	ATile* TargetTile = Grid->GetTileFromWorldPoint(TargetPos);

	//if(StartTile && TargetTile)

	OpenTileSet.Add(StartTile);
	VisitedTiles.Add(StartTile);

	while (OpenTileSet.Num() > 0)
	{
		ATile* CurrentTile = OpenTileSet[0];
		

		for (int32 index = 1; index < OpenTileSet.Num(); index++)
		{
			if (OpenTileSet[index]->GetFCost() < CurrentTile->GetFCost() || (OpenTileSet[index]->GetFCost() == CurrentTile->GetFCost() && OpenTileSet[index]->HCost < CurrentTile->HCost))
			{
				CurrentTile = OpenTileSet[index];
			}
		}

		OpenTileSet.Remove(CurrentTile);
		ClosedTileSet.Add(CurrentTile);
		//DrawDebugSphere(GetWorld(), CurrentTile->WorldPosition, Grid->TileRadius, 5, FColor::Blue, true, -1, 0, 1.0f);

		if (CurrentTile == TargetTile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("A* Target Found")));
			TracePath(StartTile, TargetTile);
			return;
		}

		for (ATile* NeighbourTile : Grid->GetNeighbourTiles(CurrentTile))
		{
			if (!NeighbourTile->Walkable || ClosedTileSet.Contains(NeighbourTile))
				continue;

			int32 NewCostToNeighbour = CurrentTile->GCost + GetDistance(CurrentTile, NeighbourTile);

			if (NewCostToNeighbour < NeighbourTile->GCost || !OpenTileSet.Contains(NeighbourTile))
			{
				NeighbourTile->GCost = NewCostToNeighbour;
				NeighbourTile->HCost = GetDistance(NeighbourTile, TargetTile);

				NeighbourTile->ParentTile = CurrentTile;

				if (!OpenTileSet.Contains(NeighbourTile))
				{
					OpenTileSet.Add(NeighbourTile);
					VisitedTiles.Add(NeighbourTile);
				}
			}
		}
	}
}

// Called when the game starts
void UAStarPathFinding::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void UAStarPathFinding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

