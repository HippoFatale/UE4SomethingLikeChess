// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingCube.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "SomethingLikeChessCharacter.h"
#include "Piece.h"

// Sets default values
AFallingCube::AFallingCube()
{
	//	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	   //PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	CollisionComp->InitBoxExtent(FallingCubeExtent);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFallingCube::OnHit);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->ProjectileGravityScale = FallingSpeed;
	ProjectileMovement->InitialSpeed = 0.0f;
	ProjectileMovement->MaxSpeed = 0.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->BodyInstance.SetCollisionProfileName("NoCollision");

	InitialLifeSpan = 10.0f;
}

//// Called when the game starts or when spawned
//void AProjectile::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AProjectile::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void AFallingCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ASomethingLikeChessCharacter* SLCPlayer;
	SLCPlayer = Cast<ASomethingLikeChessCharacter>(OtherActor);

	APiece* ProjectileOwner = GetInstigator<APiece>();

	if (SLCPlayer && ProjectileOwner)
	{
		if (SLCPlayer->GetPlayerTeam() != ProjectileOwner->GetPieceTeam())
			SLCPlayer->UpdateHealth((ProjectileOwner->GetPieceAttackDamage()) * -1);
	}

	Destroy();
}