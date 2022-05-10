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
	//��������� FGeometryData �� ���� ��������� ������ Hub
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
	TSubclassOf<ABaseGeometryActor> GeometryClass; // 1.4 TSubclassOf ���������� ������ ������� ABaseGeometryActor � �������
	// 1.4 ������� ������ ������ ABaseGeometryActor ������� ����� ��������
	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;
	// ��������� ������ ��������, � Editor ������� ��������� ��������� ������ �������

private:	

	ABaseGeometryActor* NonePropertyActor;
	UPROPERTY()
	ABaseGeometryActor* PropertyActor;
	// ��������� ������ ������ � uproperty � ���
	
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();
	void DoActorSpawn4();


	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	void OnTimerFinished(AActor* Actor);
	// 2.4 ��������� �������, ������������� ��� ������������ ��������� 

};
