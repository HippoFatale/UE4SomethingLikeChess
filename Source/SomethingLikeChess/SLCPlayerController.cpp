// Fill out your copyright notice in the Description page of Project Settings.


#include "SLCPlayerController.h"
#include "SLCTypes.h"
#include "SLCHUD.h"
#include "SomethingLikeChessCharacter.h"
#include "SLCGameStateBase.h"

void ASLCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (BP_SLCHUD != nullptr && IsLocalPlayerController())
	{
		SLCHUD = CreateWidget<USLCHUD>(this, BP_SLCHUD);
		SLCHUD->AddToViewport(0);
	}

	SLCGameStateBase = GetWorld() != NULL ? Cast<ASLCGameStateBase>(GetWorld()->GetGameState()) : NULL;
}

void ASLCPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASomethingLikeChessCharacter* PlayerCharacter = Cast<ASomethingLikeChessCharacter>(InPawn);
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->SetPlayerTeam(GetControllerTeam());
	}
}

void ASLCPlayerController::UpdateHealthPercent(float InHealthPercent)
{
	if (SLCHUD != nullptr)
	{
		SLCHUD->UpdateHealthPercent(InHealthPercent);
	}
}

void ASLCPlayerController::Victory(EPieceTeam InWinTeam)
{
	ServerGameEnd();

	SLCGameStateBase->SetWinTeam(InWinTeam);
}

void ASLCPlayerController::Defeat(EPieceTeam InLoseTeam)
{
	ServerGameEnd();

	if (InLoseTeam == EPieceTeam::Team1)
	{
		SLCGameStateBase->SetWinTeam(EPieceTeam::Team2);
	} 
	else if (InLoseTeam == EPieceTeam::Team2)
	{
		SLCGameStateBase->SetWinTeam(EPieceTeam::Team1);
	}
}

void ASLCPlayerController::GameEnd()
{
	SLCGameStateBase->SetGameEnded(true);
	SetPause(false);
}

void ASLCPlayerController::ServerGameEnd_Implementation()
{
	MulticastGameEnd();
}

void ASLCPlayerController::MulticastGameEnd_Implementation()
{
	GameEnd();
}
