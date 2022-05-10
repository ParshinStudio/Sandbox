// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "Delegates/Delegate.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;
	//Safety object class creation of ABaseGeometryActor
	UPROPERTY(EditAnywhere)
	FGeometryData Data;
	//ќбъ€вл€ем FGeometryData из меша структуру внутри Hub
	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;
	// Rotation, Location, Scale 3d
};
// 

UCLASS()
class SANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AGeometryHubActor();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere) 
	TSubclassOf<ABaseGeometryActor> GeometryClass; // 1.4 TSubclassOf отображает только объекты ABaseGeometryActor в проекте
	// 1.4 —оздаем объект класса ABaseGeometryActor который будем спавнить
	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;
	// ќбъ€вл€ем массив структур, в Editor создаем несколько элементов такого массива

private:	

	ABaseGeometryActor* NonePropertyActor;
	UPROPERTY()
	ABaseGeometryActor* PropertyActor;
	// ќбъ€вл€ем пример класса с uproperty и без
	
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
	void DoActorSpawn4();


	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	void OnTimerFinished(AActor* Actor);
	// 2.4 ќбъ€вл€ем функции, выполн€ющиес€ при срабатывании делегатов 

};
