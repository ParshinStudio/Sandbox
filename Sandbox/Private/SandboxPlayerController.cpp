// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Engine/World.h"
#include "SandboxPawn.h"
//��������� ���������� SandboxPawn ��� ������ � ��� � GameplayStatics
#include "Components/InputComponent.h"
//��������� ���������� InputComponent ��� ������ � ���������
#include "Kismet/GameplayStatics.h"
//������� ��������� ������, ��������� �������� ������� �� ����� � ����������� � ���

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)


void ASandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//��������� ����������� ������������� ��������� Bind
	if (InputComponent)
	{
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
		// ������ Bind ������� ChangePawn ��� ������������ ChangePawn �� ������ � ������� �� ������� �������
	}
	
}

void ASandboxPlayerController::BeginPlay()
{
	// TArray<AActor*> Pawns; �� ������������ ��� � �����, ���������� �������� �� ������� ����������
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
	// ������� ������ ������ � ������� �� � ������ ����������� � h
}

void ASandboxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) return;
	//���������, ��� � ������� ���� ��������
	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	// ��������� �� ��������� ������ ������ �� ������� �� �������
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	// ��������� 1 ��� ������ ����� �����, �� �� ������� �� ������� �������
	if (!CurrentPawn) return; // ��������� ��� ������ ����������
	UE_LOG(LogSandboxPlayerController, Error, TEXT("ChangePawn"));
	Possess(CurrentPawn);
	// ����� ���������� ������
}
