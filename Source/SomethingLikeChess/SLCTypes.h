#pragma once

#include "SLCTypes.generated.h"

class APiece;
class ASomethingLikeChessCharacter;

USTRUCT()
struct FPlayerAttackInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FVector StartPoint;

	UPROPERTY()
	FVector EndPoint;

	UPROPERTY()
	float GameTime;

	FPlayerAttackInfo()
	{

	}

	FPlayerAttackInfo(FVector InStartPoint, FVector InEndPoint, float InGameTime)
	{
		StartPoint = InStartPoint;
		EndPoint = InEndPoint;
		GameTime = InGameTime;
	}
};

UENUM(BlueprintType)
enum class EPieceTeam : uint8
{
	Neutral,
	Team1,
	Team2
};

USTRUCT()
struct FPieceTeamInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	APiece* Piece;

	UPROPERTY()
	EPieceTeam PieceTeam;

	FPieceTeamInfo()
	{

	}

	FPieceTeamInfo(APiece* InPiece, EPieceTeam InPieceTeam)
	{
		Piece = InPiece;
		PieceTeam = InPieceTeam;
	}
};

USTRUCT()
struct FPlayerTeamInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	ASomethingLikeChessCharacter* SLCCharacter;

	UPROPERTY()
	EPieceTeam PlayerTeam;

	FPlayerTeamInfo()
	{

	}

	FPlayerTeamInfo(ASomethingLikeChessCharacter* InSLCCharacter, EPieceTeam InPlayerTeam)
	{
		SLCCharacter = InSLCCharacter;
		PlayerTeam = InPlayerTeam;
	}
};

USTRUCT()
struct FGameResultInfo
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EPieceTeam PlayerTeam;

	UPROPERTY()
	bool bVictory;

	FGameResultInfo()
	{

	}

	FGameResultInfo(EPieceTeam InPlayerTeam, bool InbVictory)
	{
		PlayerTeam = InPlayerTeam;
		bVictory = InbVictory;
	}
};