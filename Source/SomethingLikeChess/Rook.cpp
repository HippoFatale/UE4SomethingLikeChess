// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"

ARook::ARook()
{
	PieceAttackDamage = MajorAttackDamage;
	PieceScore = 5;
}

void ARook::SpecificPieceAttack()
{
	HorizontalAttack(RookProjectileDirections);
}
