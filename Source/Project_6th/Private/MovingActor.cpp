// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CroissantMesh(TEXT("/Game/ModularBakeryShop/Meshes/SM_Croissant.SM_Croissant"));
	if (CroissantMesh.Succeeded())
	{
		Mesh->SetStaticMesh(CroissantMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> CroissantMaterial(TEXT("/Game/ModularBakeryShop/Materials/MI_Pastry_A.MI_Pastry_A"));
	if (CroissantMaterial.Succeeded())
	{
		Mesh->SetMaterial(0, CroissantMaterial.Object);
	}
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetActorScale3D(FVector(10.0f));


	MovedPostion.Add(FVector(0.0f, 0.0f, 0.0f));
	MovedPostion.Add(FVector(200.0f, 0.0f, 0.0f));
	MP_Idx = 0;
}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorLocation(MovedPostion[0]);
}

void AMovingActor::MoveActor(float DeltaTime)
{
	if (isRunMoving == false)
	{
		MP_Idx = (MP_Idx + 1) % MovedPostion.Num();
		isRunMoving = true;
	}

	FVector vec = MovedPostion[MP_Idx] - GetActorLocation();

	AddActorWorldOffset(vec.GetSafeNormal() * DeltaTime * MoveSpeed);

	UE_LOG(LogTemp, Log, TEXT("%f"), FVector::Dist(GetActorLocation(), MovedPostion[MP_Idx]));
	if (FVector::Dist(GetActorLocation(), MovedPostion[MP_Idx]) <= 1.0f)
	{
		isRunMoving = false;
	}
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isRunMoving == false && CheckTime < RestTime)
	{
		CheckTime += DeltaTime;
	}
	else
	{
		CheckTime = 0.0f;
		MoveActor(DeltaTime);
	}
}

