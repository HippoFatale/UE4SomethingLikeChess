// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SomethingLikeChess.h"
#include "GameFramework/Character.h"
#include "SomethingLikeChessCharacter.generated.h"

class ASLCPlayerController;

UCLASS(config=Game)
class ASomethingLikeChessCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASomethingLikeChessCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

#pragma region Attack
public:
	void PlayerAttack();

	void PlayerAtkCDEnd();

	UFUNCTION(Server, Reliable)
	void ServerPlayerAttack(FPlayerAttackInfo InPlayerAttackInfo);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayerAttack(FPlayerAttackInfo InPlayerAttackInfo);

public:
	bool bPlayerAttackReady = true;

	FTimerHandle PlayerAtkCDHandle;

	float PlayerAttackCooldown = 5.0f;
#pragma endregion

#pragma region HP
public:
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float HealthChange);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth = 64.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPercentage = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PreviousHealth =  HealthPercentage;
#pragma endregion

#pragma region Team
public:
	EPieceTeam GetPlayerTeam() { return PlayerTeam; }

	void SetPlayerTeam(EPieceTeam InPieceTeam);

	void SetPlayerColor(EPieceTeam InPieceTeam);

	UFUNCTION(Server, Reliable)
	void ServerSetPlayerColor(EPieceTeam InPieceTeam);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetPlayerColor(EPieceTeam InPieceTeam);

	UFUNCTION(Server, Reliable)
	void ServerSetPieceTeam(FPieceTeamInfo InPieceTeam);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetPieceTeam(FPieceTeamInfo InPieceTeam);

private:
	UPROPERTY(Replicated)
	EPieceTeam PlayerTeam = EPieceTeam::Neutral;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Team1Material;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* Team2Material;
#pragma endregion
};

