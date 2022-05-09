// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnChessPiece.h"

APawnChessPiece::APawnChessPiece()
{
	PieceAttackDamage = PawnAttackDamage;
	PieceScore = 1;
}

void APawnChessPiece::SpecificPieceAttack()
{
	VerticalAttack(PawnAttackLocations);
}
