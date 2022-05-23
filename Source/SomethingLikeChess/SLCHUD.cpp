// Fill out your copyright notice in the Description page of Project Settings.


#include "SLCHUD.h"
#include "Components/ProgressBar.h"

void USLCHUD::UpdateHealthPercent(float InHealthPercent)
{
	HealthBar->SetPercent(InHealthPercent);
}

void USLCHUD::UpdateScoreText(float InScoreText)
{
	//ScoreText->Bind(InScoreText);
}
