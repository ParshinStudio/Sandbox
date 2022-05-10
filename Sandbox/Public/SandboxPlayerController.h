// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SandboxPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SANDBOX_API ASandboxPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	// переопределе€м InputComponent функцию в движке
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY()
	TArray<AActor*> Pawns;
	// ќбъ€вл€ем переменную временный массив акторов
	int32 CurrentPawnIndex = 0;
	// объ€вл€ем переменную колличества акторов
	void ChangePawn();
	// объ€вл€ем функцию смены Pawn
};

