// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SLCHUD.generated.h"

class UProgressBar;

UCLASS()
class SOMETHINGLIKECHESS_API USLCHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateHealthPercent(float InHealthPercent);

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};
