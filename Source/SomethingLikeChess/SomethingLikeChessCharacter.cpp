// Copyright Epic Games, Inc. All Rights Reserved.

#include "SomethingLikeChessCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "SLCGameStateBase.h"
#include "Piece.h"
#include "HealthInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SLCPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "SLCHUD.h"
//////////////////////////////////////////////////////////////////////////
// ASomethingLikeChessCharacter

ASomethingLikeChessCharacter::ASomethingLikeChessCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Team1Material = CreateDefaultSubobject<UMaterial>(TEXT("Team1Materal"));
	Team2Material = CreateDefaultSubobject<UMaterial>(TEXT("Team2Materal"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ASomethingLikeChessCharacter::BeginPlay()
{
	Super::BeginPlay();

	ServerSetPlayerColor(PlayerTeam);
	MulticastSetPlayerColor(PlayerTeam);
}

void ASomethingLikeChessCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASomethingLikeChessCharacter, PlayerTeam);
}

//////////////////////////////////////////////////////////////////////////
// Input

void ASomethingLikeChessCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASomethingLikeChessCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASomethingLikeChessCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ASomethingLikeChessCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ASomethingLikeChessCharacter::LookUpAtRate);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASomethingLikeChessCharacter::PlayerAttack);
}

void ASomethingLikeChessCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASomethingLikeChessCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASomethingLikeChessCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASomethingLikeChessCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASomethingLikeChessCharacter::PlayerAttack()
{
	if (!bPlayerAttackReady)
		return;

	//Draw RayTrace Camera->CenterOfScreen
	FHitResult CameraTraceHit;
	APlayerCameraManager* camManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector camLocation = camManager->GetCameraLocation();
	FVector camForward = camManager->GetCameraRotation().Vector();
	FVector CameraStart = camLocation + camForward * CameraBoom->TargetArmLength;
	FVector CameraEnd = CameraStart + camForward * 10000.0f;
	ECollisionChannel CameraChannel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(CameraTraceHit, CameraStart, CameraEnd, CameraChannel, QueryParams);
	DrawDebugLine(GetWorld(), CameraStart, CameraEnd, FColor::Red, false, 5.0f);

	//Draw RayTrace StartPointOfFire->ImpactPointOfCameraTrace
	FHitResult PlayerTraceHit;
	FVector PlayerStart = GetActorLocation();
	FVector PlayerTarget = PlayerStart + (CameraTraceHit.ImpactPoint - PlayerStart) * 10.0f;
	ECollisionChannel PlayerChannel = ECollisionChannel::ECC_Visibility;
	GetWorld()->LineTraceSingleByChannel(PlayerTraceHit, PlayerStart, PlayerTarget, PlayerChannel, QueryParams);
	FVector PlayerEnd;
	if (PlayerTraceHit.ImpactNormal == FVector::ZeroVector)
	{
		PlayerEnd = PlayerTraceHit.TraceEnd;
	}
	else
	{
		PlayerEnd = PlayerTraceHit.ImpactPoint;
	}
	DrawDebugLine(GetWorld(), PlayerStart, PlayerEnd, FColor::Blue, false, 5.0f);
	ASLCGameStateBase* ServerState = GetWorld()->GetGameState<ASLCGameStateBase>();
	if (ServerState)
	{
		FPlayerAttackInfo PlayerAttackInfo(PlayerStart, PlayerEnd, ServerState->GetServerWorldTimeSeconds());
		ServerPlayerAttack(PlayerAttackInfo);
	}

	bPlayerAttackReady = false;

	GetWorldTimerManager().SetTimer(PlayerAtkCDHandle, this, &ASomethingLikeChessCharacter::PlayerAtkCDEnd, PlayerAttackCooldown, false);

	if (PlayerTraceHit.Actor.IsValid() && PlayerTraceHit.Actor->IsA(APiece::StaticClass()))
	{
		APiece* HitPiece = Cast<APiece>(PlayerTraceHit.Actor);
		if (HitPiece->GetPieceTeam() != PlayerTeam)
		{
			FPieceTeamInfo HitPieceTeamInfo(HitPiece, PlayerTeam);
			ServerSetPieceTeam(HitPieceTeamInfo);
			UpdateScore(HitPiece->GetPieceScore());
		}
	}

}

void ASomethingLikeChessCharacter::PlayerAtkCDEnd()
{
	bPlayerAttackReady = true;
	GetWorldTimerManager().ClearTimer(PlayerAtkCDHandle);
}

void ASomethingLikeChessCharacter::ServerPlayerAttack_Implementation(FPlayerAttackInfo InPlayerAttackInfo)
{
	MulticastPlayerAttack(InPlayerAttackInfo);
}

void ASomethingLikeChessCharacter::MulticastPlayerAttack_Implementation(FPlayerAttackInfo InPlayerAttackInfo)
{
	if (IsLocallyControlled())
		return;
	DrawDebugLine(GetWorld(), InPlayerAttackInfo.StartPoint, InPlayerAttackInfo.EndPoint, FColor::Green, false, 5.0f);
}

void ASomethingLikeChessCharacter::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPercentage = Health / FullHealth;

	if (Health <= 0.0f)
	{
		bGameEnd = true;
		bVictory = false;

		//Destroy();
	}
}

void ASomethingLikeChessCharacter::UpdateScore(float ScoreChange)
{
	Score += ScoreChange;
}

void ASomethingLikeChessCharacter::SetPlayerTeam(EPieceTeam InPieceTeam)
{
	PlayerTeam = InPieceTeam;
	//SetPlayerColor(PlayerTeam);
	//ServerSetPlayerColor(PlayerTeam);
}

void ASomethingLikeChessCharacter::SetPlayerColor(EPieceTeam InPieceTeam)
{
	switch (InPieceTeam)
	{
	case EPieceTeam::Team1:
		GetMesh()->SetMaterial(0, Team1Material);
		break;
	case EPieceTeam::Team2:
		GetMesh()->SetMaterial(0, Team2Material);
		break;
	}
}

void ASomethingLikeChessCharacter::ServerSetPlayerColor_Implementation(EPieceTeam InPieceTeam)
{
	MulticastSetPlayerColor(InPieceTeam);
}

void ASomethingLikeChessCharacter::MulticastSetPlayerColor_Implementation(EPieceTeam InPieceTeam)
{
	SetPlayerColor(InPieceTeam);
}

void ASomethingLikeChessCharacter::ServerSetPieceTeam_Implementation(FPieceTeamInfo InPieceTeam)
{
	MulticastSetPieceTeam(InPieceTeam);
}

void ASomethingLikeChessCharacter::MulticastSetPieceTeam_Implementation(FPieceTeamInfo InPieceTeam)
{
	InPieceTeam.Piece->TeamColorManager(InPieceTeam.PieceTeam);
	InPieceTeam.Piece->SetPieceTeam(InPieceTeam.PieceTeam);
}
