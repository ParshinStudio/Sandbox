
#include "GeometryHubActor.h"
#include "Engine/World.h" // 1.1 ����������, ��� �������� UWorld

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometryHub, All, All)
// ���������� ����������� ��� ��������� ��� Hub

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
	UWorld* World = GetWorld(); // 1.2 GetWorld �������� ��������� �� ���, World ������ ������ UWorld
	if (World) // 1.3 ���������, ��� ��������� ����� �������� ����
	{
		for (int32 i = 0; i < 10; ++i) // ���� �������� �������
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator, FVector(0.0f, 330.0f * i, 300.0f));
			// 1.5 ������ ������� GeometryTransform ��������� FTransform ������ ��� �������� �� ���������� �������
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>(GeometryClass, GeometryTransform);
			// 1.5 �������� ������ �������� ������ Geometry ������ ABaseGeometryActor ������� GeometryClass(�������� � h �����) � ����� �������� SpawnActor � World �� ������� ABaseGeometryActor � �������� GeometryTransform
			// <ABaseGeometryActor> ���������� ���������
			if (Geometry) // ���������, ��� ������ Geometry ������������� ������
			{
				FGeometryData Data; // 1.6 ������� ��������� ���������� ���� ��������� FGeometryData
				Data.MoveType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				// 1.7 ������ �������� MoveType � ��������� ������� ������ ABaseGeometryActor ������ ���������
				Geometry->SetGeometryData(Data);
				// 1.8 ������ ��������� Data � ������� ������� ������ ������� ABaseGeometryActor ���������� �������
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
			// SpawnActorDeferred ������� ������ �� �� �������� BeginPlay
			if (Geometry)
			{
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				// ������ �������� �����
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
				// FinishSpawning �������� beginplay (���������� �������)
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
		// ����� ������ �� ������� GeometryPayloads, �������� � ���������� ��������� Payload 
		{
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass, Payload.InitialTransform);
			// ��������� Geometry ���� ABaseGeometryActor � ������� ������ �������� Spawn � ������� ����������� 
			if (Geometry) // ������ ������?
			{
				Geometry->SetGeometryData(Payload.Data); // ������ ������ ��������� � ����� ������
				Geometry->OnColorChanged.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				Geometry->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				// 2.5 ������ Bind ����������� �� ������� Geometry � �������� ������� ������ ����� ������� (������ �� ������, ������ �� ����������� �������)
				Geometry->FinishSpawning(Payload.InitialTransform); // ������ ������ ��������� � ����� ������

			}
		}
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogBaseGeometryHub, Warning, TEXT("Actor name: %s Color %s"), *Name, *Color.ToString())
	// 2.6  ��������� ������  ��� ������������ ��������
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if(!Actor) return;
	UE_LOG(LogBaseGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());
	// 2.6 ��������� ������ ��� ������������ ��������

	ABaseGeometryActor* Geometry = Cast<ABaseGeometryActor>(Actor);
	//����� �������������� Actor � ABaseGeometryActor

	if (!Geometry) return;
	UE_LOG(LogBaseGeometryHub, Display, TEXT("Cast is done, amplitude %f"), Geometry->GetGeometryData().Amplitude);
	//������� �������� ���������

	//Geometry->Destroy();
	Geometry->SetLifeSpan(5);
	// ���������� ����� ����� 5 ������ ����� ������ �������
}
