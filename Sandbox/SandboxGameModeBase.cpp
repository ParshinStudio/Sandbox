// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandboxGameModeBase.h"
#include "SandboxPawn.h"
// Подключаем хедер пешки для работы с SandboxPawn
#include "SandboxPlayerController.h"
// Подключаем хедер контроллера для работы с SandboxPlayerController

ASandboxGameModeBase::ASandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	// Задаем в гейм моде ASandboxPawn как DefaultPawnClass в движке через встроенную функцию StaticClass
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
	// Задаем в гейм моде ASandboxPlayerController как PlayerControllerClass в движке через встроенную функцию StaticClass

}