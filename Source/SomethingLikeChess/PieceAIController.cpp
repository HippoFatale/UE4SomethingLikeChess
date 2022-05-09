// Fill out your copyright notice in the Description page of Project Settings.


#include "PieceAIController.h"
#include "BehaviorTree/BehaviorTree.h"

// Called when the game starts or when spawned
void APieceAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BTPiece);
}