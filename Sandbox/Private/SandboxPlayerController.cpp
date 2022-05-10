// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPlayerController.h"
#include "Engine/World.h"
#include "SandboxPawn.h"
//Добавляем библиотеку SandboxPawn для работы с ним в GameplayStatics
#include "Components/InputComponent.h"
//Добавляем библиотеку InputComponent для работы с клавишами
#include "Kismet/GameplayStatics.h"
//Функция упрощения работы, позволяет получить акторов со сцены и иноформацию о них

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)


void ASandboxPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	//Позволяет контроллеру устанавливать кастомные Bind
	if (InputComponent)
	{
		InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
		// Делаем Bind функции ChangePawn при срабатывании ChangePawn из инпута в эдиторе по нажатию клавиши
	}
	
}

void ASandboxPlayerController::BeginPlay()
{
	// TArray<AActor*> Pawns; не переобъявлен как в курсу, компилятор ругается на двойное объявление
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
	// Получим акторы класса и запишем их в массив объявленный в h
}

void ASandboxPlayerController::ChangePawn()
{
	if (Pawns.Num() <= 1) return;
	//Проверяем, что в массиве есть элементы
	ASandboxPawn* CurrentPawn = Cast<ASandboxPawn>(Pawns[CurrentPawnIndex]);
	// Назначаем во временный объект объект из массива по индексу
	CurrentPawnIndex = (CurrentPawnIndex + 1) % Pawns.Num();
	// Добавляем 1 при вызове смены павна, но не выходим за пределы массива
	if (!CurrentPawn) return; // Проверяем что объект существует
	UE_LOG(LogSandboxPlayerController, Error, TEXT("ChangePawn"));
	Possess(CurrentPawn);
	// Берем управление пешкой
}
