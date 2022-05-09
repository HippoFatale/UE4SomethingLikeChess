// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SomethingLikeChess.h"
#include "SLCTypes.h"
#include "GameFramework/Pawn.h"
#include "Piece.generated.h"

class ASomethingLikeChessCharacter;

UCLASS()
class SOMETHINGLIKECHESS_API APiece : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region Attack
public:
	UFUNCTION(BlueprintCallable)
	void BP_PieceAttack();

	void PieceAttack();

protected:
	virtual	void SpecificPieceAttack() { }

	void HorizontalAttack(TArray<FVector> InAttackDirections);

	void VerticalAttack(TArray<FVector2D> InAttackLocations);

private:
	void PieceAtkCDEnd();

public:
	int32 GetPieceAttackDamage() { return PieceAttackDamage; }

	int32 GetPieceScore() { return PieceScore; }

protected:
	UPROPERTY(EditDefaultsOnly)
	int32 PieceAttackDamage = 0;

	int32 KingAttackDamage = 8;
	int32 MajorAttackDamage = 4;
	int32 MinorAttackDamage = 2;
	int32 PawnAttackDamage = 1;

	int32 PieceScore = 0;

private:
	bool bPieceAttackReady = true;

	FTimerHandle PieceAtkCDHandle;

	UPROPERTY(EditDefaultsOnly)
	float PieceAttackCooldown = 5.0f;

	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> Projectile1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AProjectile> Projectile2;

	TSubclassOf<class AWarningSquare> WarningSquare;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWarningSquare> WarningSquare1;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AWarningSquare> WarningSquare2;

	UPROPERTY(EditDefaultsOnly)
	float FallHeight = 1000.0f;

	UPROPERTY(EditDefaultsOnly)
	float SquareSize = 100.0f;
#pragma endregion

#pragma region Team
public:
	void SetPieceTeam(EPieceTeam InPieceTeam) { PieceTeam = InPieceTeam; }

	EPieceTeam GetPieceTeam() { return PieceTeam; }

	UFUNCTION(BlueprintPure)
	EPieceTeam BP_GetPieceTeam() { return PieceTeam; }

	void TeamColorManager(EPieceTeam InPieceTeam);

private:
	EPieceTeam PieceTeam = EPieceTeam::Neutral;

	int32 TeamModifier = 0;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* NeutralMaterial;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Team1Material;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Team2Material;
#pragma endregion

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Piece)
	class UCapsuleComponent* CollisionComp;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = Piece)
	class UStaticMeshComponent* MeshComp;
};
