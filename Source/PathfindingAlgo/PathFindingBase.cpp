// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFindingBase.h"
#include "Tile.h"
#include "Grid.h"

// Sets default values for this component's properties
UPathFindingBase::UPathFindingBase()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UPathFindingBase::FindPath(FVector StartPos, FVector TargetPos)
{
}

int32 UPathFindingBase::GetDistance(ATile* TileA, ATile* TileB)
{
	int32 DistacneX = FMath::Abs(TileA->GridX - TileB->GridX);
	int32 DistacneY = FMath::Abs(TileA->GridY - TileB->GridY);

	if (DistacneX > DistacneY)
	{
		return (14 * DistacneY) + (10 * (DistacneX - DistacneY));
	}
	else
	{
		return (14 * DistacneX) + (10 * (DistacneY - DistacneX));
	}
}

void UPathFindingBase::TracePath(ATile* StartTile, ATile* EndTile)
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("%d Tiles Visited"), VisitedTiles.Num()));
	TArray<class ATile*> Path;

	class ATile* CurrentTile = EndTile;

	while (CurrentTile != StartTile)
	{
		Path.Add(CurrentTile);
		CurrentTile = CurrentTile->ParentTile;
	}

	Algo::Reverse(Path);

	Grid->Path = Path;
	Grid->VisitedPath = VisitedTiles;
}

// Called when the game starts
void UPathFindingBase::BeginPlay()
{
	Super::BeginPlay();

	Grid = Cast<UGrid>(GetOwner()->FindComponentByClass<UGrid>());
}


// Called every frame
void UPathFindingBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
