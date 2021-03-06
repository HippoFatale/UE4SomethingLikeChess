// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerStart.h"
#include "SomethingLikeChessCharacter.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "PawnChessPiece.h"
#include "SomethingLikeChessGameMode.generated.h"


UCLASS(minimalapi)
class ASomethingLikeChessGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASomethingLikeChessGameMode();

	//virtual void PostLogin(APlayerController* NewPlayer) override;

protected:
	virtual void BeginPlay() override;

#pragma region SetPlayerTeam SpawnPlayer
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

private:
	bool bIsTeam1 = true;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class ASomethingLikeChessCharacter> SLCCharacter;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	int32 Players = 2;
#pragma endregion

#pragma region SpawnPieces
protected:
	void SpawnPieces(int32 InKings, int32 InQueens, int32 InRooks, int32 InBishops, int32 InKnights, int32 InPawns);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	TSubclassOf<class AKing> King;

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	TSubclassOf<class AQueen> Queen;

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	TSubclassOf<class ARook> Rook;

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	TSubclassOf<class ABishop> Bishop;

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	TSubclassOf<class AKnight> Knight;

	UPROPERTY(EditDefaultsOnly, Category = "Piece")
	TSubclassOf<class APawnChessPiece> PawnPiece;

	int BoardSquares = 28 - 2;
	float SquareSize = 100.0f;

	float Boarda1X = -(1800.0f - SquareSize * 1);
	float Boarda1Y = -(1400.0f - SquareSize * 1);
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	float FloorLevel = 130.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	int32 Sets = 2;

	int32 Kings = Sets * 1;
	int32 Queens = Sets * 1;
	int32 Rooks = Sets * 2;
	int32 Bishops = Sets * 2;
	int32 Knights = Sets * 2;
	int32 PawnPieces = Sets * 8;
#pragma endregion
};