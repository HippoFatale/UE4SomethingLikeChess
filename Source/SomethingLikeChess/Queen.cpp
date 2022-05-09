// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"

AQueen::AQueen()
{
	PieceAttackDamage = MajorAttackDamage;
	PieceScore = 9;
}

void AQueen::SpecificPieceAttack()
{
	if (bCardinalAttackTurn)
	{
		bCardinalAttackTurn = false;
		CardinalAttack();
	} 
	else
	{
		bCardinalAttackTurn = true;
		InterCardinalAttack();
	}
}

void AQueen::CardinalAttack()
{
	HorizontalAttack(QueenCardinalProjectileDirections);
}

void AQueen::InterCardinalAttack()
{
	HorizontalAttack(QueenInterCardinalProjectileDirections);
}
