// PAWN CPP FILE / ELIASGAMEDEVSTUDIO


#include "SandboxPawn.h"
#include "Components/StaticMeshComponent.h"
//��������� ���������� StaticMeshComponent ��� ������ � ������
#include "Camera/CameraComponent.h"
//��������� ���������� CameraComponent ��� ������ � �������
#include "Components/InputComponent.h"
//��������� ���������� InputComponent ��� ������ � ���������

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	//���������� � SceneComponent DefaultUSceneComponent � ��������� SceneComponent
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>("StaticMeshComponent");
	// ������� ������ ��� � ��������� � ������ ����������� � h
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	// ������������� ��� � ��������� ����������

	CameraComponent = CreateDefaultSubobject< UCameraComponent>("CameraComponent");
	// ������� camera � ��������� � ������ ����������� � h
	CameraComponent->SetupAttachment(GetRootComponent());
	// ������������� ������ � ��������� ����������
}

void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!VelocityVector.IsZero()) // �������� ����� ���� ����� IsControlled()
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		// ������ ���� ��������� ��������� ������ � ���������� � ���� ��������, ���������� �� ����������� �������� � ������� �������
		SetActorLocation(NewLocation);
		VelocityVector = FVector::ZeroVector;
		// ������ ������� � �������� ������ ����� ��������� �������������� ��������, ����� ������ ������� ��������� � ������ UnPossessed
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
	// Bind ������� �� PlayerInputComponent
	// ��� ������������ Input �� ���������� ������������ ����������� � Project Settings ������ �������� �� ����� � ���������� ����������� ������� 
}

void ASandboxPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!NewController) return;
	UE_LOG(LogSandboxPawn, Display, TEXT("%s possessed %s"), *GetName(), *NewController->GetName());
}

void ASandboxPawn::UnPossessed()
{
	Super::UnPossessed();

	UE_LOG(LogSandboxPawn, Display, TEXT("%s unpossessed"), *GetName());
}

void ASandboxPawn::MoveForward(float Amount)
{
	//UE_LOG(LogSandboxPawn, Display, TEXT("Move forward: %f"), Amount)
	VelocityVector.X = Amount;
	// ������ ����������� �������� �������� �������� �������� Axis
}

void ASandboxPawn::MoveRight(float Amount)
{
	//UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount)
	VelocityVector.Y = Amount;
	// ������ ����������� �������� �������� �������� �������� Axis
}


