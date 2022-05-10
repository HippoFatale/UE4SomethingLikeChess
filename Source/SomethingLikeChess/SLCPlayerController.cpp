// Fill out your copyright notice in the Description page of Project Settings.


#include "SLCPlayerController.h"
#include "SLCTypes.h"
#include "SLCHUD.h"
#include "SLCGameOver.h"
#include "SomethingLikeChessCharacter.h"

void ASLCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (BP_SLCHUD != nullptr && IsLocalPlayerController())
	{
		SLCHUD = CreateWidget<USLCHUD>(this, BP_SLCHUD);
		SLCHUD->AddToViewport();
	}
}

void ASLCPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ASomethingLikeChessCharacter* PlayerCharacter = Cast<ASomethingLikeChessCharacter>(InPawn);
	if (PlayerCharacter != nullptr)
	{
		PlayerCharacter->SetPlayerTeam(GetControllerTeam());
	}
}

void ASLCPlayerController::GameOver()
{
	if (BP_SLCGameOver != nullptr)
	{
		SetPause(true);
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
		SLCGameOver = CreateWidget<USLCGameOver>(this, BP_SLCGameOver);
		SLCGameOver->AddToViewport();
	}
}

void ASLCPlayerController::UpdateHealthPercent(float InHealthPercent)
{
	if (SLCHUD != nullptr)
	{
		SLCHUD->UpdateHealthPercent(InHealthPercent);
	}
}
