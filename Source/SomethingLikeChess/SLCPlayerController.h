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

	void Defeat();

protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

private:
	UPROPERTY()
	class USLCHUD* SLCHUD;

	EPieceTeam ControllerTeam = EPieceTeam::Neutral;
};
