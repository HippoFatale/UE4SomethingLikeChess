// Fill out your copyright notice in the Description page of Project Settings.


#include "WarningSquare.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SomethingLikeChessCharacter.h"
#include "Piece.h"

// Sets default values
AWarningSquare::AWarningSquare()
{
	//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	   //PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->InitBoxExtent(WarningSquareExtent);
	CollisionComp->BodyInstance.SetCollisionProfileName("NoCollision");
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->BodyInstance.SetCollisionProfileName("NoCollision");

	InitialLifeSpan = 1.5f;
}