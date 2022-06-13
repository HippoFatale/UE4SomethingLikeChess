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
		Team1Score = Team1Score + InScore;
		if (Team1Score >= WinScore)
		{
			Victory(EPieceTeam::Team1);
		}
	}
	else if (InTeam == EPieceTeam::Team2)
	{
		Team2Score = Team2Score + InScore;
		if (Team2Score >= WinScore)
		{
			Victory(EPieceTeam::Team2);
		}
	}
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
