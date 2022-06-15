// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SLCTypes.h"
#include "SLCGameStateBase.generated.h"

class ASomethingLikeChessGameMode;

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API ASLCGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	EPieceTeam GetWinTeam() { return WinTeam; }

	UFUNCTION(BlueprintPure)
	bool GetGameEnded() { return bGameEnded; }

	UFUNCTION(BlueprintPure)
	int32 GetTeam1Score() { return Team1Score; }

	UFUNCTION(BlueprintPure)
	int32 GetTeam2Score() { return Team2Score; }

	void AddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral);

	UFUNCTION(Server, Reliable)
	void ServerAddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral);

	UFUNCTION(Client , Reliable)
	void ClientAddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastAddScore(EPieceTeam InTeam, int32 InScore, bool bIsNeutral);

	void GameEnd(EPieceTeam InTeam, bool bWin);

	UFUNCTION(Server, Reliable)
	void ServerGameEnd(EPieceTeam InTeam, bool bWin);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastGameEnd(EPieceTeam InTeam, bool bWin);

private:
	UFUNCTION(BlueprintCallable)
	void UpdateTeam1Score(int32 InScore);

	UFUNCTION(BlueprintCallable)
	void UpdateTeam2Score(int32 InScore);

private:
	int32 Team1Score = 0;

	int32 Team2Score = 0;

	EPieceTeam WinTeam = EPieceTeam::Neutral;

	bool bGameEnded = false;

	ASomethingLikeChessGameMode* SLCGameMode;

	UPROPERTY(EditDefaultsOnly)
	int32 WinScore = 24;
};
