// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class PROJECT_6TH_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();
	UPROPERTY(EditAnywhere, Category = "MovingStat")
	TArray<FVector> MovedPostion;
	float RestTime = 3.0f;
	float CheckTime = 0.0f;
	int32 MP_Idx;

	UPROPERTY(EditAnywhere, Category = "MovingStat")
	float MoveSpeed = 100.0f;
	bool isRunMoving = false;

protected:
	USceneComponent* Root;

	UStaticMeshComponent* Mesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveActor(float);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
