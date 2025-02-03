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

	PrimaryActorTick.bCanEverTick = true;


	SetActorScale3D(FVector(10.0f));
	MovedPostion.Add(FVector(0.0f, 0.0f, 0.0f));
	MovedPostion.Add(FVector(200.0f, 0.0f, 0.0f));
	MovedPostion.Add(FVector(0.0f, 200.0f, 0.0f));

	MP_CurrentIdx = 0;

}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(MovedPostion[0]);

	GetWorldTimerManager().SetTimer(StartMoveTimer, this, &AMovingActor::SwitchMovingAllow, MovingTime, true);
}

void AMovingActor::MoveActor(float DeltaTime)
{
	if(isAllowMoving != true)
	{
		return;
	}

	AddActorWorldOffset(VecDirection.GetSafeNormal() * DeltaTime * VecSpeed);
}

void AMovingActor::SwitchMovingAllow()
{
	//On or Off
	isAllowMoving = !isAllowMoving;

	if (isAllowMoving)
	{
		MP_NextIdx = (MP_CurrentIdx + 1) % MovedPostion.Num();
		isRunMoving = true;
		VecDirection = MovedPostion[MP_NextIdx] - MovedPostion[MP_CurrentIdx];
		UE_LOG(LogTemp, Log, TEXT("VecDirection : %s"), *VecDirection.ToString());
		VecSpeed = VecDirection.Size() / MovingTime; // 속력 = 거리 / 시간
		UE_LOG(LogTemp, Log, TEXT("VecSpeed : %f"), VecSpeed);

		MP_CurrentIdx = MP_NextIdx;
	}
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveActor(DeltaTime);
}

