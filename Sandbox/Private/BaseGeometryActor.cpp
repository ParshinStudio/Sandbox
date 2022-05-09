// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"
DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All, All)

ABaseGeometryActor::ABaseGeometryActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
	// Создание и определение BaseMesh как RootComponent

	// MyMeshComponent->SetupAttachment(RootComponent);
	// Как приаттачить один меш к другому
}

void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();
	// В InitialLocation назнчаем положение меша в мире
	SetColor(GeometryData.Color);
	// Назначаем Color в структуре GeometryData
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
	
	//PrintStingTypes();
	//PrintTypes();
	//PrintTransform();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogBaseGeometry, Error, TEXT("Actor is dead %s"), *GetName());
}

void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement();

}

void ABaseGeometryActor::PrintTypes()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Weapons num: %i, Kills num: %i"), WeaponsNum, KillsNum);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	UE_LOG(LogTemp, Warning, TEXT("IsDead: %d"), IsDead);
	UE_LOG(LogTemp, Warning, TEXT("HasWeapon: %d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::PrintStingTypes()
{
	FString Name = "John Conor";
	UE_LOG(LogBaseGeometry, Display, TEXT("Name: %S"), *Name);

	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsdeadStr = "Is dead = " + FString(IsDead ? "True" : "False");

	FString Stat = FString::Printf(TEXT("All stats \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsdeadStr);
	UE_LOG(LogBaseGeometry, Warning, TEXT("%s"), *Stat);
	// Выводим лог состоящий из объявленных в header переменных

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, Stat, true, FVector2D(1.5f, 1.5f));
		// Вывод лога на экран
	}
}

void ABaseGeometryActor::PrintTransform()
{

	FTransform Transform = GetActorTransform();
	FVector Location = Transform.GetLocation();
	FRotator Rotation = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();
	// Временные переменные для объявление  в UE_LOG(LogTemp)

	UE_LOG(LogTemp, Warning, TEXT("Actor name %s"), *GetName());
	UE_LOG(LogTemp, Warning, TEXT("Transform %s"), *Transform.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Location %s"), *Location.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Rotation %s"), *Rotation.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Scale %s"), *Scale.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Transform %s"), *Transform.ToHumanReadableString());
	// Выводим лог в консоль
}

void ABaseGeometryActor::HandleMovement()
//Функция движения актора в мире
{
	switch (GeometryData.MoveType)
	{
	case EMovementType::Sin:
	{
		FVector CurrentLocation = GetActorLocation();
		// Записываем положение актора в сцене во временную переменную
		if (GetWorld())
		{
			float Time = GetWorld()->GetTimeSeconds();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * Time);
			SetActorLocation(CurrentLocation);
			// z = z0 + amplitude * sin(freq * t);
		}
	}
	break;

	case EMovementType::Static:
		break;
	default:break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color)
// Принимает цвет
{
	UMaterialInstanceDynamic* DynMaterial = BaseMesh->CreateAndSetMaterialInstanceDynamic(0);
	// Создаем DynMaterial в BaseMesh
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue("Color", Color);
		// Назначем входной параметр цвет в DynMaterial и соответственно в BaseMesh
	}
}

void ABaseGeometryActor::OnTimerFired()
{
	if (++TimerCount <= MaxTimerCount)
	{
		const FLinearColor NewColor = FLinearColor::MakeRandomColor();
		// Создаем временную переменную с 
		UE_LOG(LogBaseGeometry, Display, TEXT("TimerCount: %i, Color to set up: %s"), TimerCount, *NewColor.ToString());
		SetColor(NewColor);
		//Вызываем функцию NewColor и задаем рандомный цвет

		OnColorChanged.Broadcast(NewColor, GetName());
		// 2.3 Срабатывание (вызов) делегата по смене цвета
	}
	else
	{
		UE_LOG(LogBaseGeometry, Warning, TEXT("Timer has been stopped"));
		GetWorldTimerManager().ClearTimer(TimerHandle);

		OnTimerFinished.Broadcast(this);
		// 2.3 Срабатывание (вызов) делегата по окончанию работы таймера
		// Рассылает этот делегат всем привязанным объектам, за исключением тех, срок действия которых истек
	}
}

