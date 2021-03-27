// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh1"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/H/Helecopter.Helecopter'"));
	if (MeshAsset.Succeeded()) {
		UStaticMesh* Asset = MeshAsset.Object;
		mesh1->SetStaticMesh(Asset);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Fail"));
	}

	mesh1->AttachTo(root);


	time = 0.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;

	mesh1->SetRelativeLocation({ 0.f, 0.f, FMath::Sin(time) * 100 });
}

