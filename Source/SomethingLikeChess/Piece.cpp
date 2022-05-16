// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "Projectile.h"
#include "FallingCube.h"
#include "WarningSquare.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SomethingLikeChessCharacter.h"

// Sets default values
APiece::APiece()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	CollisionComp->InitCapsuleSize(42.0f, 96.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Piece");
	CollisionComp->OnComponentHit.AddDynamic(this, &APiece::OverlapDestroy);
	RootComponent = CollisionComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->OnComponentHit.AddDynamic(this, &APiece::OverlapDestroy);

	NeutralMaterial = CreateDefaultSubobject<UMaterial>(TEXT("NeutralMateral"));
	Team1Material = CreateDefaultSubobject<UMaterial>(TEXT("Team1Materal"));
	Team2Material = CreateDefaultSubobject<UMaterial>(TEXT("Team2Materal"));
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APiece::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APiece::BP_PieceAttack()
{
	PieceAttack();
}

void APiece::PieceAttack()
{
	if (!bPieceAttackReady)
		return;

	SpecificPieceAttack();

	bPieceAttackReady = false;

	GetWorldTimerManager().SetTimer(PieceAtkCDHandle, this, &APiece::PieceAtkCDEnd, PieceAttackCooldown, false);
}

void APiece::PieceAtkCDEnd()
{
	bPieceAttackReady = true;
	GetWorldTimerManager().ClearTimer(PieceAtkCDHandle);
}

void APiece::HorizontalAttack(TArray<FVector> InAttackDirections)
{
	if (Projectile)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			for (FVector AttackDirection : InAttackDirections)
			{
				AttackDirection.Normalize();
				FVector SpawnLocation = GetActorLocation() + AttackDirection * CollisionComp->GetScaledCapsuleRadius();
				FRotator SpawnRotation = AttackDirection.Rotation();
				FTransform SpawnTransform(SpawnRotation, SpawnLocation);

				AProjectile* SpawnedProjectile = World->SpawnActorDeferred<AProjectile>(Projectile, SpawnTransform, this, this);
				SpawnTransform.SetLocation(SpawnLocation + AttackDirection * SpawnedProjectile->GetProjectileRadius() * 2);
				SpawnedProjectile->FinishSpawning(SpawnTransform);
			}
		}
	}
}

void APiece::VerticalAttack(TArray<FVector2D> InAttackLocations)
{
	if (Projectile && WarningSquare)
	{
		UWorld* World = GetWorld();

		if (World)
		{
			for (FVector2D AttackLocation : InAttackLocations)
			{
				FVector SpawnLocation = GetActorLocation() + FVector(AttackLocation.X * SquareSize, AttackLocation.Y * SquareSize, FallHeight);
				FVector WarningLocation = GetActorLocation();
				WarningLocation.Z = 0.0f;
				WarningLocation = WarningLocation + FVector(AttackLocation.X * SquareSize, AttackLocation.Y * SquareSize, 130.1f);
				FRotator SpawnRotation = FVector::DownVector.Rotation();
				FTransform SpawnTransform(SpawnRotation, SpawnLocation);
				FTransform WarningTransform(GetActorRotation(), WarningLocation);

				AProjectile* SpawnedProjectile = World->SpawnActorDeferred<AProjectile>(Projectile, SpawnTransform, this, this);
				SpawnedProjectile->FinishSpawning(SpawnTransform);
				AWarningSquare* SpawnedWarningSquare = World->SpawnActorDeferred<AWarningSquare>(WarningSquare, WarningTransform, this, this);
				SpawnedWarningSquare->FinishSpawning(WarningTransform);
			}
		}
	}
}

void APiece::TeamColorManager(EPieceTeam InPieceTeam)
{
	switch (InPieceTeam)
	{
	case EPieceTeam::Neutral:
		MeshComp->SetMaterial(0, NeutralMaterial);
		break;
	case EPieceTeam::Team1:
		MeshComp->SetMaterial(0, Team1Material);
		Projectile = Projectile1;
		WarningSquare = WarningSquare1;
		break;
	case EPieceTeam::Team2:
		MeshComp->SetMaterial(0, Team2Material);
		Projectile = Projectile2;
		WarningSquare = WarningSquare2;
		break;
	}
}

void APiece::OverlapDestroy(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (Cast<AProjectile>(OtherActor))
	{
		Destroy();
	}
}
