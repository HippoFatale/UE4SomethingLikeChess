// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Bishop.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API ABishop : public APiece
{
	GENERATED_BODY()

public:
	ABishop();
	
protected:
	virtual void SpecificPieceAttack() override;

private:
	TArray<FVector> BishopProjectileDirections = { FVector(1.0f, 1.0f, 0.0f), FVector(-1.0f, 1.0f, 0.0f), FVector(-1.0f, -1.0f, 0.0f), FVector(1.0f, -1.0f, 0.0f)};
};
