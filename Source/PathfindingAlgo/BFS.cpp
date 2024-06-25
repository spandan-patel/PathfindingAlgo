// Fill out your copyright notice in the Description page of Project Settings.


#include "BFS.h"
#include "Tile.h"
#include "Grid.h"

UBFS::UBFS()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBFS::FindPath(FVector StartPos, FVector TargetPos)
{
	ATile* StartTile = Grid->GetTileFromWorldPoint(StartPos);
	ATile* TargetTile = Grid->GetTileFromWorldPoint(TargetPos);

	OpenTileQueue.Enqueue(StartTile);
	StartTile->IsVisited = true;

	while (!OpenTileQueue.IsEmpty())
	{
		ATile* CurrentTile;

		OpenTileQueue.Peek(CurrentTile);

		VisitedTiles.Add(CurrentTile);

		OpenTileQueue.Dequeue(CurrentTile);

		if (CurrentTile == TargetTile)
		{
			GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("BFS Target Found")));
			TracePath(StartTile, TargetTile);
			return;
		}

		for (ATile* NeighbourTile : Grid->GetNeighbourTiles(CurrentTile))
		{
			if (!NeighbourTile->Walkable)
				continue;

			if (!NeighbourTile->IsVisited)
			{
				NeighbourTile->ParentTile = CurrentTile;

				OpenTileQueue.Enqueue(NeighbourTile);
				NeighbourTile->IsVisited = true;
			}
		}
	}
}

void UBFS::BeginPlay()
{
	Super::BeginPlay();
}

void UBFS::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
