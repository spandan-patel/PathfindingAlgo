// Fill out your copyright notice in the Description page of Project Settings.


#include "PathFindingAlgorithmManager.h"
#include "Grid.h"
#include "AStarPathFinding.h"
#include "DijkstraPathFinding.h"
#include "BFS.h"
#include "DFS.h"
#include "Tile.h"

// Sets default values
APathFindingAlgorithmManager::APathFindingAlgorithmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyGrid = CreateDefaultSubobject<UGrid>(TEXT("My Grid"));
	MyGrid->SetupAttachment(RootComponent);

	MyAStarPath = CreateDefaultSubobject<UAStarPathFinding>(TEXT("My AStar Path"));
	MyAStarPath->SetupAttachment(RootComponent);

	MyDijkstraPath = CreateDefaultSubobject<UDijkstraPathFinding>(TEXT("My Dijkstra Path"));
	MyDijkstraPath->SetupAttachment(RootComponent);

	MyBFS = CreateDefaultSubobject<UBFS>(TEXT("My BFS"));
	MyBFS->SetupAttachment(RootComponent);

	MyDFS = CreateDefaultSubobject<UDFS>(TEXT("My DFS"));
	MyDFS->SetupAttachment(RootComponent);

	CurrentPathFindingAlgorithm = EPathFindingAlgorithmType::DIJKSTRA;	

	CurrentTime = 00.0f;
	DrawTileIndex = 0;
}

// Called when the game starts or when spawned
void APathFindingAlgorithmManager::BeginPlay()
{
	Super::BeginPlay();

	SeekerPosTemp = MyGrid->Player->GetActorLocation();

	TargetPosTemp = MyGrid->NewTempTarget->GetActorLocation();
	//TargetPosTemp = MyGrid->GridOfLevel[FMath::RandRange(0, MyGrid->GridSizeX - 1)].A[FMath::RandRange(0, MyGrid->GridSizeY - 1)]->WorldPosition;

	switch (CurrentPathFindingAlgorithm)
	{
		case EPathFindingAlgorithmType::BFS:
			MyBFS->FindPath(SeekerPosTemp, TargetPosTemp);
			break;

		case EPathFindingAlgorithmType::DFS:
			MyDFS->FindPath(SeekerPosTemp, TargetPosTemp);
			break;

		case EPathFindingAlgorithmType::DIJKSTRA:
			MyDijkstraPath->FindPath(SeekerPosTemp, TargetPosTemp);
			break;

		case EPathFindingAlgorithmType::ASTAR:
			MyAStarPath->FindPath(SeekerPosTemp, TargetPosTemp);
			break;
	}

	if (CurrentDrawPathType == EDrawPathType::BEGINDRAW)
	{
		MyGrid->DrawPathDebug();
		SetActorTickEnabled(false);
	}
	else
		SetActorTickEnabled(true);
}

// Called every frame
void APathFindingAlgorithmManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentTime += DeltaTime;

	if (CurrentTime >= 0.25f && DrawTileIndex < MyGrid->VisitedPath.Num())
	{
		ATile* CurrentTile = MyGrid->VisitedPath[DrawTileIndex];

		UMaterialInstanceDynamic* TileMat = UMaterialInstanceDynamic::Create(CurrentTile->GetMesh()->GetMaterial(0), this);
		TileMat->SetVectorParameterValue(FName(TEXT("TileColor")), FLinearColor(0.50f, 1.0f, 0.50f, 1.0f));

		CurrentTile->GetMesh()->SetMaterial(0, TileMat);

		DrawTileIndex++;
		CurrentTime = 0.0f;
	}

	if (DrawTileIndex == MyGrid->VisitedPath.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Draw Complete")));
		MyGrid->DrawPathDebug();
		SetActorTickEnabled(false);

		DrawTileIndex++;
		//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Tick Test Check")));
	}
}

