// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class PROJECT_6TH_API AMovingActor : public AActor
{
	GENERATED_BODY()

private:
	FVector VecDirection;
	float VecSpeed;

protected:
	USceneComponent* Root;

	UStaticMeshComponent* Mesh;
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();
	UPROPERTY(EditAnywhere, Category = "MovingStat")
	TArray<FVector> MovedPostion;

	UPROPERTY(EditAnywhere, Category = "MovingStat")
	float MoveSpeed = 100.0f;

	int32 MP_CurrentIdx;
	int32 MP_NextIdx;

	bool isRunMoving = false;
	bool isAllowMoving = false;

	UPROPERTY(EditAnywhere, Category = "MovingStat")
	float MovingTime = 3.0f;

	FTimerHandle StartMoveTimer;





protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveActor(float);

	void SwitchMovingAllow();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
