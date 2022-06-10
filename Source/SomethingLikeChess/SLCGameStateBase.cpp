// Fill out your copyright notice in the Description page of Project Settings.


#include "SLCGameStateBase.h"
#include "SomethingLikeChessCharacter.h"
#include "GameFramework/PlayerState.h"

void ASLCGameStateBase::AddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral)
{
	if (InTeam == EPieceTeam::Team1)
	{
		Team1Score = Team1Score + InScore;
	}
	else if (InTeam == EPieceTeam::Team2)
	{
		Team2Score = Team2Score + InScore;
	}
}
