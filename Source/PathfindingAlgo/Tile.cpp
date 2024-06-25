// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
ATile::ATile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = false;

	// ...
	Walkable = false;
	IsVisited = false;
	WorldPosition = FVector(0.0f, 0.0f, 0.0f);

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Mesh"));
	TileMesh->SetSimulatePhysics(false);
	TileMesh->SetGenerateOverlapEvents(false);
	TileMesh->SetCollisionProfileName("NoCollision");
	RootComponent = TileMesh;
}

void ATile::AssignValue(bool IsWalkable, FVector WorldPos, int32 X, int32 Y)
{
	Walkable = IsWalkable;
	WorldPosition = WorldPos;
	GridX = X;
	GridY = Y;
}

UStaticMeshComponent* ATile::GetMesh()
{
	return TileMesh;
}
