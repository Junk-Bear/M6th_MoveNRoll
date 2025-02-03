// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingActor.h"

// Sets default values
ARollingActor::ARollingActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DinnerKnifeMesh(TEXT("/Game/ModularBakeryShop/Meshes/SM_DinnerKnife.SM_DinnerKnife"));
	if (DinnerKnifeMesh.Succeeded())
	{
		Mesh->SetStaticMesh(DinnerKnifeMesh.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterial> DinnerKnifeMaterial(TEXT("/Game/ModularBakeryShop/Materials/MI_Props_04.MI_Props_04"));
	if (DinnerKnifeMaterial.Succeeded())
	{
		Mesh->SetMaterial(0, DinnerKnifeMaterial.Object);
	}
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorScale3D(FVector(20.0f));
}

// Called when the game starts or when spawned
void ARollingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARollingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.0f, 90.0f * DeltaTime, 0.0f));
}

