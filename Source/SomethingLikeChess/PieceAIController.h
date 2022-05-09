// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PieceAIController.generated.h"

/**
 * 
 */

class UBehaviorTree;

UCLASS()
class SOMETHINGLIKECHESS_API APieceAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = AAPiece)
	class UBehaviorTree* BTPiece;
};
