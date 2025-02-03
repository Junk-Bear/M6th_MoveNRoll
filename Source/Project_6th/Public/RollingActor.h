// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingActor.generated.h"

UCLASS()
class PROJECT_6TH_API ARollingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARollingActor();

protected:
	USceneComponent* Root;

	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere , Category = "RollingStat")
	float RotationSpeed = 10.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
