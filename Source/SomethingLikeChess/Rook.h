// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Piece.h"
#include "Rook.generated.h"

/**
 * 
 */
UCLASS()
class SOMETHINGLIKECHESS_API ARook : public APiece
{
	GENERATED_BODY()
	
public:
	ARook();

protected:
	virtual void SpecificPieceAttack() override;

private:
	TArray<FVector> RookProjectileDirections = { FVector::ForwardVector, FVector::BackwardVector, FVector::RightVector, FVector::LeftVector };
};
