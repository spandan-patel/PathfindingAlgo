// Fill out your copyright notice in the Description page of Project Settings.


#include "DijkstraPathFinding.h"
#include "Tile.h"
#include "Grid.h"

UDijkstraPathFinding::UDijkstraPathFinding()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDijkstraPathFinding::FindPath(FVector StartPos, FVector TargetPos)
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
			if (OpenTileSet[index]->GetFCost() < CurrentTile->GetFCost())
			{
				CurrentTile = OpenTileSet[index];
			}
		}

		OpenTileSet.Remove(CurrentTile);
		ClosedTileSet.Add(CurrentTile);
		//DrawDebugSphere(GetWorld(), CurrentTile->WorldPosition, Grid->TileRadius, 5, FColor::Blue, true, -1, 0, 1.0f);

		if (CurrentTile == TargetTile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Dikstra Target Found")));
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
				NeighbourTile->HCost = 0;

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

void UDijkstraPathFinding::BeginPlay()
{
	Super::BeginPlay();
}

void UDijkstraPathFinding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
