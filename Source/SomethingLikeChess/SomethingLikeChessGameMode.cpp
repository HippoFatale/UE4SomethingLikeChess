// Copyright Epic Games, Inc. All Rights Reserved.

#include "SomethingLikeChessGameMode.h"
#include "SomethingLikeChessCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SLCPlayerController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

ASomethingLikeChessGameMode::ASomethingLikeChessGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void ASomethingLikeChessGameMode::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlayers(Players);

	int32 Kings = Sets * 1;
	int32 Queens = Sets * 1;
	int32 Rooks = Sets * 2;
	int32 Bishops = Sets * 2;
	int32 Knights = Sets * 2;
	int32 PawnPieces = Sets * 8;
	SpawnPieces(Kings, Queens, Rooks, Bishops, Knights, PawnPieces);
}

FString ASomethingLikeChessGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString ErrorMessage = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	ASLCPlayerController* PlayerController = Cast<ASLCPlayerController>(NewPlayerController);

	if (PlayerController != nullptr)
	{
		if (bIsTeam1)
		{
			PlayerController->SetControllerTeam(EPieceTeam::Team1);
			bIsTeam1 = false;
		}
		else
		{
			PlayerController->SetControllerTeam(EPieceTeam::Team2);
			bIsTeam1 = true;
		}
	}

	return ErrorMessage;
}


void ASomethingLikeChessGameMode::SpawnPlayers(int32 InPlayers)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParameters;

	for (int i = 0; i < Players; i++)
	{
		World->SpawnActor<ASomethingLikeChessCharacter>(SLCCharacter, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, 130), FVector::ForwardVector.Rotation(), SpawnParameters);
	}
}

void ASomethingLikeChessGameMode::SpawnPieces(int32 InKings, int32 InQueens, int32 InRooks, int32 InBishops, int32 InKnights, int32 InPawns)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParameters;

	if (World != nullptr)
	{
		for (int i = 0; i < InKings; i++)
		{
			World->SpawnActor<AKing>(King, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, FloorLevel + rand() % 200), FVector::ForwardVector.Rotation(), SpawnParameters);
		}

		for (int i = 0; i < InQueens; i++)
		{
			World->SpawnActor<AQueen>(Queen, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, FloorLevel + rand() % 200), FVector::ForwardVector.Rotation(), SpawnParameters);
		}

		for (int i = 0; i < InRooks; i++)
		{
			World->SpawnActor<ARook>(Rook, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, FloorLevel + rand() % 200), FVector::ForwardVector.Rotation(), SpawnParameters);
		}

		for (int i = 0; i < InBishops; i++)
		{
			World->SpawnActor<ABishop>(Bishop, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, FloorLevel + rand() % 200), FVector::ForwardVector.Rotation(), SpawnParameters);
		}

		for (int i = 0; i < InKnights; i++)
		{
			World->SpawnActor<AKnight>(Knight, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, FloorLevel + rand() % 200), FVector::ForwardVector.Rotation(), SpawnParameters);
		}

		for (int i = 0; i < InPawns; i++)
		{
			World->SpawnActor<APawnChessPiece>(PawnPiece, FVector(Boarda1X + (rand() % (BoardSquares - 1)) * 100 + 50, Boarda1Y + (rand() % (BoardSquares - 1)) * 100 + 50, FloorLevel + rand() % 200), FVector::ForwardVector.Rotation(), SpawnParameters);
		}
	}
}
