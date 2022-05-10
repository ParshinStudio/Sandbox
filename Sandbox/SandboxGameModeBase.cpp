// Copyright Epic Games, Inc. All Rights Reserved.


#include "SandboxGameModeBase.h"
#include "SandboxPawn.h"
// ���������� ����� ����� ��� ������ � SandboxPawn
#include "SandboxPlayerController.h"
// ���������� ����� ����������� ��� ������ � SandboxPlayerController

ASandboxGameModeBase::ASandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	// ������ � ���� ���� ASandboxPawn ��� DefaultPawnClass � ������ ����� ���������� ������� StaticClass
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
	// ������ � ���� ���� ASandboxPlayerController ��� PlayerControllerClass � ������ ����� ���������� ������� StaticClass

}