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

void ASLCGameStateBase::Victory(EPieceTeam InWinTeam)
{
	WinTeam = InWinTeam;
	bGameEnded = true;
	//if (SLCGameMode != NULL)
	//{
	//	SLCGameMode->SetPause(false);
	//}
}

void ASLCGameStateBase::Defeat(EPieceTeam InLoseTeam)
{
	if (InLoseTeam == EPieceTeam::Team1)
	{
		WinTeam = EPieceTeam::Team2;
	} 
	else if (InLoseTeam == EPieceTeam::Team2)
	{
		WinTeam = EPieceTeam::Team1;
	}
	bGameEnded = true;
	//if (SLCGameMode != NULL)
	//{
	//	SLCGameMode->SetPause(false);
	//}
}

void ASLCGameStateBase::UpdateTeam1Score(int32 InScore)
{
	Team1Score = Team1Score + InScore;
	if (Team1Score >= WinScore)
	{
		Victory(EPieceTeam::Team1);
	}
}

void ASLCGameStateBase::UpdateTeam2Score(int32 InScore)
{
	Team2Score = Team2Score + InScore;
	if (Team2Score >= WinScore)
	{
		Victory(EPieceTeam::Team2);
	}
}
