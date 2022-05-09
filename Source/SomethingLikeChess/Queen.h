// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Queen.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API AQueen : public APiece
{
	GENERATED_BODY()

public:
	AQueen();

protected:
	virtual void SpecificPieceAttack() override;

private:
	void CardinalAttack();
	void InterCardinalAttack();

private:
	bool bCardinalAttackTurn = true;

	TArray<FVector> QueenCardinalProjectileDirections = { FVector::ForwardVector, FVector::BackwardVector, FVector::RightVector, FVector::LeftVector };
	TArray<FVector> QueenInterCardinalProjectileDirections = { FVector(1.0f, 1.0f, 0.0f), FVector(-1.0f, 1.0f, 0.0f), FVector(-1.0f, -1.0f, 0.0f), FVector(1.0f, -1.0f, 0.0f) };
};
