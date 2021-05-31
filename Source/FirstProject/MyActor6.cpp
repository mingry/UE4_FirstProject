// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor6.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMyActor6::AMyActor6()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	physics_drone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Physics Drone"));
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> drone(TEXT("StaticMesh'/Game/D/P4_scaled.P4_scaled'"));

	if (drone.Succeeded()) {
		UStaticMesh* m = drone.Object;
		physics_drone->SetStaticMesh(m);
	}

	physics_drone->AttachTo(root);
	
}

// Called when the game starts or when spawned
void AMyActor6::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	physics_drone->SetSimulatePhysics(true);
	physics_drone->SetMassOverrideInKg(NAME_None, 1.0f);


	// Torque at the begining
	/*
	FVector torque;
	FVector axis(0.f, 1.f, 1.f);
	axis.Normalize();
	float magnitude = 15000.f;
	torque = axis * magnitude;
	physics_drone->AddTorque(torque);
	*/

	physics_drone->GetBodyInstance()->bLockXRotation = true;
	physics_drone->GetBodyInstance()->bLockYRotation = true;
	physics_drone->GetBodyInstance()->bLockZRotation = true;
	physics_drone->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);

}

// Called every frame
void AMyActor6::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;


	FVector com = physics_drone->GetCenterOfMass();

	FVector F(0.f, 0.f, 980.f);

	FRotator cur_R = physics_drone->GetComponentRotation();
	F = cur_R.RotateVector(F);

	physics_drone->AddForce(F);
	
	DrawDebugDirectionalArrow(GetWorld(), com, com + F * DeltaTime,
		10, FColor::Red, false, DeltaTime + 0.0001, 9, 3);

	UE_LOG(LogTemp, Warning, TEXT("F=%s"), *(F.ToString()));
}

