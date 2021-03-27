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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeliAsset(TEXT("StaticMesh'/Game/H/Helecopter.Helecopter'"));

	if (HeliAsset.Succeeded()) {
		UStaticMesh* m = HeliAsset.Object;
		mesh1->SetStaticMesh(m);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HeliAsset Fail"));
	}

	mesh1->AttachTo(root);

	speed = 1.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();


	time = 0.0f;
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;

	FVector p(0.f, 0.f, FMath::Sin(speed*time)*100.0f);

	mesh1->SetRelativeLocation(p);
}

