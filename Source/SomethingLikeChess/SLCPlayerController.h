// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SLCTypes.h"
#include "SLCPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API ASLCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class USLCHUD> BP_SLCHUD;

	void UpdateHealthPercent(float InHealthPercent);

	void SetControllerTeam(EPieceTeam InControllerTeam) { ControllerTeam = InControllerTeam; }

	EPieceTeam GetControllerTeam() { return ControllerTeam; }

	void Victory(EPieceTeam InWinTeam);

	void Defeat(EPieceTeam InLoseTeam);

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	void GameEnd();

	UFUNCTION(Server, Reliable)
	void ServerGameEnd();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastGameEnd();

private:
	UPROPERTY()
	class USLCHUD* SLCHUD;

	UPROPERTY(EditDefaultsOnly)
	class ASLCGameStateBase* SLCGameStateBase;

	EPieceTeam ControllerTeam = EPieceTeam::Neutral;
};
