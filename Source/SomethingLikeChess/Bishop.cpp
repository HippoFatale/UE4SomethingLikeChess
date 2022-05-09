// Fill out your copyright notice in the Description page of Project Settings.


#include "Bishop.h"

ABishop::ABishop()
{
	PieceAttackDamage = MinorAttackDamage;
	PieceScore = 3;
}

void ABishop::SpecificPieceAttack()
{
	HorizontalAttack(BishopProjectileDirections);
}