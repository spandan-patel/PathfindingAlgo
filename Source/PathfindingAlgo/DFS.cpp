// Fill out your copyright notice in the Description page of Project Settings.


#include "DFS.h"
#include "Grid.h"
#include "Tile.h"

UDFS::UDFS()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDFS::FindPath(FVector StartPos, FVector TargetPos)
{
	ATile* StartTile = Grid->GetTileFromWorldPoint(StartPos);
	ATile* TargetTile = Grid->GetTileFromWorldPoint(TargetPos);

	RecursiveCheck(StartTile, StartTile, TargetTile);
}

void UDFS::BeginPlay()
{
	Super::BeginPlay();
}

void UDFS::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDFS::RecursiveCheck(ATile* CurrentTile, ATile* StartTile, ATile* TargetTile)
{
	OpenTileStack.Push(CurrentTile);
	CurrentTile->IsVisited = true;

	VisitedTiles.Add(CurrentTile);

	if (CurrentTile == TargetTile)
	{
		//DrawDebugSphere(GetWorld(), CurrentTile->WorldPosition, Grid->TileRadius * 1.2f, 5, FColor::Blue, true, -1, 0, 1.0f);
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("DFS Target Found")));
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
			NeighbourTile->IsVisited = true;
			RecursiveCheck(NeighbourTile, StartTile, TargetTile);
		}
	}

	OpenTileStack.Pop();
}
