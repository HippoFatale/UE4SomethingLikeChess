// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

AKnight::AKnight()
{
	PieceAttackDamage = MinorAttackDamage;
	PieceScore = 3;
}

void AKnight::SpecificPieceAttack()
{
	VerticalAttack(KnightAttackLocations);
}
