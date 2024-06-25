// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "DrawDebugHelpers.h"
#include "Tile.h"
#include "Kismet\KismetSystemLibrary.h"

// Sets default values for this component's properties
UGrid::UGrid()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UGrid::BeginPlay()
{
	Super::BeginPlay();

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Message Showed"));

	TileDiameter = TileRadius * 2.0f;

	GridSizeX = FMath::RoundToInt32(GridWorldSize.X / TileDiameter);
	GridSizeY = FMath::RoundToInt32(GridWorldSize.Y / TileDiameter);

	//Ground->SetActorLocation(FVector());

	//DrawDebugBox(GetWorld(), GetComponentLocation(), FVector(GridSizeX, GridSizeY, 1.0f), FColor::White, true, -1, 0, 1.0f);

	CreateGrid();

	/*float RandomX = FMath::FRandRange(GridOfLevel[0].A[0]->WorldPosition.X, GridOfLevel[GridSizeX - 1].A[GridSizeY - 1]->WorldPosition.X);
	float RandomY = FMath::FRandRange(GridOfLevel[0].A[0]->WorldPosition.Y, GridOfLevel[GridSizeX - 1].A[GridSizeY - 1]->WorldPosition.Y);
	FVector RandomPosition = FVector(RandomX, RandomY, Player->GetActorLocation().Z);

	Player->SetActorLocation(RandomPosition);*/

	ATile* PlayerTile = GetTileFromWorldPoint(Player->GetActorLocation());

	UMaterialInstanceDynamic* TileMat = UMaterialInstanceDynamic::Create(PlayerTile->GetMesh()->GetMaterial(0), this);
	TileMat->SetVectorParameterValue(FName(TEXT("TileColor")), FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));

	PlayerTile->GetMesh()->SetMaterial(0, TileMat);

	//DrawDebugSphere(GetWorld(), PlayerTile->WorldPosition, TileRadius * 1.2f, 5, FColor::Red, true, -1, 0, 1.0f);
}


// Called every frame
void UGrid::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrid::CreateGrid()
{
	FVector WorldBottomLeft = GetComponentLocation() - GetRightVector() * GridWorldSize.Y / 2 - GetForwardVector() * GridWorldSize.X / 2;

	//DrawDebugSphere(GetWorld(), WorldBottomLeft, 5.0f, 10, FColor::Blue, true, -1, 0, 1.0f);

	for (int32 i = 0; i < GridSizeX; i++)
	{
		FNested2DArray TempArray;

		for (int32 j = 0; j < GridSizeY; j++)
		{
			FVector WorldPoint = WorldBottomLeft + GetForwardVector() * (i * TileDiameter + TileRadius) + GetRightVector() * (j * TileDiameter + TileRadius);
			FActorSpawnParameters SpawnInfo;

			ATile* NewTile = GetWorld()->SpawnActor<ATile>(TileToSpawn, WorldPoint + GetUpVector(), FRotator::ZeroRotator, SpawnInfo);
			NewTile->SetActorScale3D(FVector::OneVector * TileRadius * 0.019f);

			TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
			traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

			TArray<AActor*> ActorsToIgnore;
			ActorsToIgnore.Add(Ground);

			TArray<AActor*> OutActors;

			UClass* SeekClass = NULL;

			bool IsWalkable = !UKismetSystemLibrary::SphereOverlapActors(GetWorld(), WorldPoint, TileRadius, traceObjectTypes, SeekClass, ActorsToIgnore, OutActors);

			NewTile->AssignValue(IsWalkable, WorldPoint, i, j);

			TempArray.AddTile(NewTile);

			/*if (IsWalkable)
				DrawDebugSphere(GetWorld(), WorldPoint, TileRadius, 5, FColor::Blue, true, -1, 0, 1.0f);
			else
				DrawDebugSphere(GetWorld(), WorldPoint, TileRadius, 5, FColor::Red, true, -1, 0, 1.0f);*/

			//FActorSpawnParameters SpawnInfo;

			//GetWorld()->SpawnActor<AActor>(TempTile, WorldPoint + GetUpVector() * 0.5f, FRotator::ZeroRotator, SpawnInfo);
		}

		GridOfLevel.Add(TempArray);
	}

	FVector CenterOfGrid = FVector((GridOfLevel[0].A[0]->WorldPosition.X + GridOfLevel[GridSizeX - 1].A[GridSizeY - 1]->WorldPosition.X) / 2.0f, (GridOfLevel[0].A[0]->WorldPosition.Y + GridOfLevel[GridSizeX - 1].A[GridSizeY - 1]->WorldPosition.Y) / 2.0f, 0.0f);
	
	Ground->SetActorLocation(CenterOfGrid);
	Ground->SetActorScale3D(FVector((GridSizeX * TileRadius / 50.0f) + (TileDiameter / 100.0f), (GridSizeY * TileRadius / 50.0f) + (TileDiameter / 100.0f), 1.0f));
}

ATile* UGrid::GetTileFromWorldPoint(FVector WorldPosition)
{
	float PercentX = (WorldPosition.X / GridWorldSize.X) + 0.5f;
	float PercentY = (WorldPosition.Y / GridWorldSize.Y) + 0.5f;

	//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("X p: %f, Y p: %f"), PercentX, PercentY));

	int32 X = FMath::FloorToInt32(FMath::Clamp((GridSizeX) * PercentX, 0, GridSizeX - 1));
	int32 Y = FMath::FloorToInt32(FMath::Clamp((GridSizeY) * PercentY, 0, GridSizeY - 1));

	//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("X : %d, Y : %d"), X, Y));

	//DrawDebugSphere(GetWorld(), PlayerTile->GetComponentLocation(), TileRadius * 1.2f, 5, FColor::White, true, -1, 0, 1.0f);

	return GridOfLevel[X].A[Y];
}

TArray<class ATile*> UGrid::GetNeighbourTiles(ATile* Tile)
{
	TArray<class ATile*> Neighbours;

	for (int32 IndexX = -1; IndexX <= 1; IndexX++)
	{
		for (int32 IndexY = -1; IndexY <= 1; IndexY++)
		{
			if (IndexX == 0 && IndexY == 0)
				continue;

			int32 TempX = Tile->GridX + IndexX;
			int32 TempY = Tile->GridY + IndexY;

			if (TempX >= 0 && TempX < GridSizeX && TempY >= 0 && TempY < GridSizeY)
			{
				Neighbours.Add(GridOfLevel[TempX].A[TempY]);
			}
		}
	}

	//GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Neighbours Found %d"), Neighbours.Num()));

	return Neighbours;
}

void UGrid::DrawPathDebug()
{
	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("Path Found %d"), Path.Num()));

	for (int32 index = 0; index < Path.Num(); index++)
	{
		//DrawDebugSphere(GetWorld(), Path[index]->WorldPosition, TileRadius, 5, FColor::White, true, -1, 0, 1.0f);

		UMaterialInstanceDynamic* TileMat = UMaterialInstanceDynamic::Create(Path[index]->GetMesh()->GetMaterial(0), this);
		TileMat->SetVectorParameterValue(FName(TEXT("TileColor")), FLinearColor(0.0f, 0.0f, 0.0f, 0.0f));

		Path[index]->GetMesh()->SetMaterial(0, TileMat);
	}
}
