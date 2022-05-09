// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingCube.generated.h"

UCLASS()
class SOMETHINGLIKECHESS_API AFallingCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallingCube();

	//protected:
	//	// Called when the game starts or when spawned
	//	virtual void BeginPlay() override;
	//
	//public:	
	//	// Called every frame
	//	virtual void Tick(float DeltaTime) override;

public:
	//float GetProjectileRadius() { return ProjectileRadius; }

private:
	UPROPERTY(VisibleDefaultsOnly, Category = FallingCube)
	class UBoxComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(VisibleDefaultsOnly, Category = FallingCube)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	float FallingSpeed = 0.5f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FVector FallingCubeExtent = FVector(30.0f, 30.0f, 30.0f);
};