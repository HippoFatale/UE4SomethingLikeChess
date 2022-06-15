// Fill out your copyright notice in the Description page of Project Settings.


#include "SLCGameStateBase.h"
#include "SomethingLikeChessCharacter.h"
#include "SomethingLikeChessGameMode.h"
#include "GameFramework/PlayerState.h"

void ASLCGameStateBase::BeginPlay()
{
	Super::BeginPlay();

	SLCGameMode = GetWorld() != NULL ? Cast<ASomethingLikeChessGameMode>(GetWorld()->GetAuthGameMode()) : NULL;
}

void ASLCGameStateBase::AddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral)
{
	if (InTeam == EPieceTeam::Team1)
	{
		UpdateTeam1Score(InScore);
		if (!bIsNeutral)
		{
			UpdateTeam2Score(-InScore);
		}
	}
	else if (InTeam == EPieceTeam::Team2)
	{
		UpdateTeam2Score(InScore);
		if (!bIsNeutral)
		{
			UpdateTeam1Score(-InScore);
		}
	}
}

void ASLCGameStateBase::ServerAddScore_Implementation(EPieceTeam InTeam, int32 InScore, bool bIsNeutral)
{
	MulticastAddScore(InTeam, InScore, bIsNeutral);
}

void ASLCGameStateBase::ClientAddScore_Implementation(EPieceTeam InTeam, int32 InScore, bool bIsNeutral)
{
	MulticastAddScore(InTeam, InScore, bIsNeutral);
}

void ASLCGameStateBase::MulticastAddScore_Implementation(EPieceTeam InTeam, int32 InScore, bool bIsNeutral)
{
	AddScore(InTeam, InScore, bIsNeutral);
}

void ASLCGameStateBase::GameEnd(EPieceTeam InTeam, bool bWin)
{
	bGameEnded = true;

	if (bWin)
	{
		WinTeam = InTeam;
	} 
	else
	{
		if (InTeam == EPieceTeam::Team1)
		{
			WinTeam = EPieceTeam::Team2;
		}
		else if (InTeam == EPieceTeam::Team2)
		{
			WinTeam = EPieceTeam::Team1;
		}
	}
}

void ASLCGameStateBase::ServerGameEnd_Implementation(EPieceTeam InTeam, bool bWin)
{
	MulticastGameEnd(InTeam, bWin);
}

void ASLCGameStateBase::MulticastGameEnd_Implementation(EPieceTeam InTeam, bool bWin)
{
	GameEnd(InTeam, bWin);
}

void ASLCGameStateBase::UpdateTeam1Score(int32 InScore)
{
	Team1Score = Team1Score + InScore;
	if (Team1Score >= WinScore)
	{
		MulticastGameEnd(EPieceTeam::Team1, true);
	}
}

void ASLCGameStateBase::UpdateTeam2Score(int32 InScore)
{
	Team2Score = Team2Score + InScore;
	if (Team2Score >= WinScore)
	{
		MulticastGameEnd(EPieceTeam::Team2, true);
	}
}
