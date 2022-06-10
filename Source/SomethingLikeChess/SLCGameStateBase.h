// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SLCTypes.h"
#include "SLCGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API ASLCGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	EPieceTeam GetWinTeam() { return WinTeam; }

	void SetWinTeam(EPieceTeam InWinTeam) { WinTeam = InWinTeam; }

	UFUNCTION(BlueprintPure)
	bool GetGameEnded() { return bGameEnded; }

	void SetGameEnded(bool InbGameEnded) { bGameEnded = InbGameEnded; }

	UFUNCTION(BlueprintPure)
	int32 GetTeam1Score() { return Team1Score; }

	UFUNCTION(BlueprintPure)
	int32 GetTeam2Score() { return Team2Score; }

	void AddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral);

private:
	EPieceTeam WinTeam = EPieceTeam::Neutral;

	bool bGameEnded = false;

	int32 Team1Score = 0;

	int32 Team2Score = 0;
};
