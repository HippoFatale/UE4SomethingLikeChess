// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

AKing::AKing()
{
	PieceAttackDamage = KingAttackDamage;
	PieceScore = 4;
}

void AKing::SpecificPieceAttack()
{
	VerticalAttack(KingAttackLocations);
}
