// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "King.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API AKing : public APiece
{
	GENERATED_BODY()

public:
	AKing();

protected:
	virtual void SpecificPieceAttack() override;

private:
	TArray<FVector2D> KingAttackLocations = { FVector2D(0.0f, 1.0f), FVector2D(1.0f, 1.0f), FVector2D(1.0f, 0.0f), FVector2D(1.0f, -1.0f), FVector2D(0.0f, -1.0f), FVector2D(-1.0f, -1.0f), FVector2D(-1.0f, 0.0f), FVector2D(-1.0f, 1.0f) };
};
