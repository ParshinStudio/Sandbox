
#include "GeometryHubActor.h"
#include "Engine/World.h" // 1.1 Библиотека, где объявлен UWorld

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometryHub, All, All)
// Объявление собственной лог категории для Hub

AGeometryHubActor::AGeometryHubActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();
	
	//DoActorSpawn1();
	//DoActorSpawn2();
	DoActorSpawn3();
}

void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld(); // 1.2 GetWorld получает указатель на мир, World объект класса UWorld
	if (World) // 1.3 Проверяем, что указатель имеет значение мира
	{
		for (int32 i = 0; i < 10; ++i) // Цикл создания акторов
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 330.0f * i, 300.0f));
			// 1.5 Задаем объекту GeometryTransform структуры FTransform данные для передачи их созданному объекту
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			// 1.5 Вызываем фунцию создание актора Geometry класса ABaseGeometryActor объекта GeometryClass(объявлен в h файле) в сцене функцией SpawnActor в World по шаблону ABaseGeometryActor с позицией GeometryTransform
			// <ABaseGeometryActor> возвращает указатель
			if (Geometry) // Проверяем, что объект Geometry действительно создан
			{
				FGeometryData Data; // 1.6 Создаем временную переменную типа структуры FGeometryData
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				// 1.7 Задаем значения MoveType в структуре объекта класса ABaseGeometryActor нужные параметры
				Geometry->SetGeometryData(Data);
				// 1.8 Задаем параметры Data с помощью функции внутри объекта ABaseGeometryActor созданному объекту
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < 10; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 330.0f * i, 700.0f));
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			// SpawnActorDeferred создает объект но не вызывает BeginPlay
			if (Geometry)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				// Пример передачи цвета
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
				// FinishSpawning вызывает beginplay (отложенная функция)
			}

		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (const FGeometryPayload Payload : GeometryPayloads) 
		// Бежим циклом по массиву GeometryPayloads, работаем с временными объектами Payload 
		{
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
			// Объявляем Geometry типа ABaseGeometryActor и создаем объект функцией Spawn с входыми параметрами 
			if (Geometry) // Объект создан?
			{
				Geometry->SetGeometryData(Payload.Data); // задаем данные структуры в новый объект
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				// 2.5 Делаем Bind зависимость от объекта Geometry и вызываем функции внутри этого объекта (ссылка на объект, ссылка на выполняемую функцию)
				Geometry->FinishSpawning(Payload.InitialTransform); // задаем данные структуры в новый объект

			}
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogBaseGeometryHub, Warning, TEXT("Actor name: %s Color %s"), *Name, *Color.ToString())
	// 2.6  Выполняем логику  при срабатывании делегата
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if(!Actor) return;
	UE_LOG(LogBaseGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());
	// 2.6 Выполняем логику при срабатывании делегата

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	//Явное Преобразование Actor к ABaseGeometryActor

	if (!Geometry) return;
	UE_LOG(LogBaseGeometryHub, Display, TEXT("Cast is done, amplitude %f"), Geometry->GetGeometryData().Amplitude);
	//Выводим значение амплитуды

	//Geometry->Destroy();
	Geometry->SetLifeSpan(5);
	// Уничтожает актор через 5 секунд после вызова функции
}
