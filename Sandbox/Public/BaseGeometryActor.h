// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Delegates/Delegate.h"
#include "BaseGeometryActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged, const FLinearColor&, Color, const FString&, Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);
// 2.1 Объявляем делегаты для работы с параметрами 


UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Sin,
	Static
	// Enum для состояний объекта
};

USTRUCT(BlueprintType)
struct FGeometryData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement");
	EMovementType MoveType = EMovementType::Static;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement");
	float Amplitude = 50.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement");
	float Frequency = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design");
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditAnywhere, Category = "Design");
	float TimerRate = 1.0f;

	// Объявляем переменные геометрии
};

UCLASS()
class SANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ABaseGeometryActor();

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* BaseMesh;
	// Объявляем BaseMesh объект типа UStaticMeshComponent

	void SetGeometryData(const FGeometryData& Data) 
	{ GeometryData = Data; }
	// 1.8 Задаем объекту параметры фукцией внутри объекта

	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const { return GeometryData; }
	// Предоставляем доступ к стуктуре GeometryData в Blueprint через функцию GetGeometryData()

	UPROPERTY(BlueprintAssignable)
	// Предоставляем доступ к делегату в Blueprint
	FOnColorChanged OnColorChanged;
	FOnTimerFinished OnTimerFinished;
	// 2.2 Объявляем делегаты
		
protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// Переопределение функции EndPlay

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Geometry Data");
	FGeometryData GeometryData;
	// Объявляем структуру типа FGeometryData для хранения данных геометрии
	// Предоставляем доступ в Blueprint через BlueprintReadWrite

	UPROPERTY(EditAnywhere, Category = "Weapon");
	int32 WeaponsNum = 4;
	UPROPERTY(EditDefaultsOnly, Category = "Stat");
	int32 KillsNum = 7;
	UPROPERTY(EditInstanceOnly, Category = "Health");
	float Health = 34.1467;
	UPROPERTY(EditAnywhere, Category = "Health");
	bool IsDead = false;
	UPROPERTY(VisibleAnywhere, Category = "Weapon");
	bool HasWeapon = true;
	// Предоставляем доступ в Default к объявленным переменным

public:	

	virtual void Tick(float DeltaTime) override;

private:
	void PrintTypes();
	void PrintStingTypes();
	void PrintTransform();

	FVector InitialLocation;

	void HandleMovement();

	void SetColor(const FLinearColor& Color);

	FTimerHandle TimerHandle;
	void OnTimerFired();
	const int32 MaxTimerCount = 5;
	int32 TimerCount = 0;
};	