// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarningSquare.generated.h"

UCLASS()
class SOMETHINGLIKECHESS_API AWarningSquare : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarningSquare();

//protected:
//	// Called when the game starts or when spawned
//	virtual void BeginPlay() override;
//
//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category = WarningSquare)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleDefaultsOnly, Category = WarningSquare)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FVector WarningSquareExtent = FVector(50.0f, 50.0f, 1.0f);
};
