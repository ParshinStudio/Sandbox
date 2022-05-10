// PAWN CPP FILE / ELIASGAMEDEVSTUDIO


#include "SandboxPawn.h"
#include "Components/StaticMeshComponent.h"
//Добавляем библиотеку StaticMeshComponent для работы с мешами
#include "Camera/CameraComponent.h"
//Добавляем библиотеку CameraComponent для работы с камерой
#include "Components/InputComponent.h"
//Добавляем библиотеку InputComponent для работы с клавишами

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

ASandboxPawn::ASandboxPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	//Записываем в SceneComponent DefaultUSceneComponent с названием SceneComponent
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject< UStaticMeshComponent>("StaticMeshComponent");
	// Создаем статик меш и назначаем в объект объявленный в h
	StaticMeshComponent->SetupAttachment(GetRootComponent());
	// Приаттачиваем меш к корневому компоненту

	CameraComponent = CreateDefaultSubobject< UCameraComponent>("CameraComponent");
	// Создаем camera и назначаем в объект объявленный в h
	CameraComponent->SetupAttachment(GetRootComponent());
	// Приаттачиваем камеру к корневому компоненту
}

void ASandboxPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASandboxPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!VelocityVector.IsZero()) // проверка может быть через IsControlled()
	{
		const FVector NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		// Каждый кадр проверяем положение актора и прибавляем к нему скорость, умноженную на направление движения в еденицу времени
		SetActorLocation(NewLocation);
		VelocityVector = FVector::ZeroVector;
		// Задаем локацию и обнуляем вектор после окончания математической операции, чтобы объект перстал двигаться в случае UnPossessed
	}

}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent)
	PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASandboxPawn::MoveRight);
	// Bind функций на PlayerInputComponent
	// При срабатывании Input из компонента активируются назначенные в Project Settings аксисы согласно их имени и вызываются привязанные функции 
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
	// Задаем направлению движения значение согласно значению Axis
}

void ASandboxPawn::MoveRight(float Amount)
{
	//UE_LOG(LogSandboxPawn, Display, TEXT("Move right: %f"), Amount)
	VelocityVector.Y = Amount;
	// Задаем направлению движения значение согласно значению Axis
}


