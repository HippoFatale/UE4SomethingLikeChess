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
	void Lose(EPieceTeam InPieceTeam);
};
