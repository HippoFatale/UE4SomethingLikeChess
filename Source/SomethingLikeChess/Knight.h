// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Knight.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API AKnight : public APiece
{
	GENERATED_BODY()

public:
	AKnight();

protected:
	virtual void SpecificPieceAttack() override;

private:
	TArray<FVector2D> KnightAttackLocations = { FVector2D(1.0f, 2.0f), FVector2D(2.0f, 1.0f), FVector2D(2.0f, -1.0f), FVector2D(1.0f, -2.0f), FVector2D(-1.0f, -2.0f), FVector2D(-2.0f, -1.0f), FVector2D(-2.0f, 1.0f), FVector2D(-1.0f, 2.0f) };
};