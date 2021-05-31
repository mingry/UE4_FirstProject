// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor7.h"
#include "DrawDebugHelpers.h"


// Sets default values
AMyActor7::AMyActor7()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	physics_drone = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Physics Drone"));
	goal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Goal"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> drone(TEXT("StaticMesh'/Game/D/P4_scaled.P4_scaled'"));

	if (drone.Succeeded()) {
		UStaticMesh* m = drone.Object;
		physics_drone->SetStaticMesh(m);
		goal->SetStaticMesh(m);
	}

	physics_drone->AttachTo(root);
	goal->AttachTo(root);

	kp = 20.f;
	kd = 2.f;
	ki = 0.1f;
}

// Called when the game starts or when spawned
void AMyActor7::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	physics_drone->SetSimulatePhysics(true);
	//physics_drone->SetMassOverrideInKg(NAME_None, 1.0f);


	physics_drone->GetBodyInstance()->bLockXRotation = true;
	physics_drone->GetBodyInstance()->bLockYRotation = true;
	physics_drone->GetBodyInstance()->bLockZRotation = true;
	physics_drone->GetBodyInstance()->SetDOFLock(EDOFMode::SixDOF);


	goal->GetBodyInstance()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	goal->SetVisibility(false);

	last_error = goal->GetComponentLocation() - physics_drone->GetComponentLocation();
	acc_error = FVector(0.f, 0.f, 0.f);
}

// Called every frame
void AMyActor7::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;


	FVector com = physics_drone->GetCenterOfMass();
	FVector error = goal->GetComponentLocation() - physics_drone->GetComponentLocation();
	FVector d_error = (error - last_error)/DeltaTime;

	// Èû °è»ê 
	FVector F(0.f, 0.f, 0.f);

	// PID controller 
	
	// Proportional gain
	F += kp*error;

	// Derivative
	F += kd*d_error;

	// Integral 
	F += ki*acc_error;


	// Èû Àû¿ë
	FRotator cur_R = physics_drone->GetComponentRotation();
	F = cur_R.RotateVector(F);
	physics_drone->AddForce(F);

	// Èû Ç¥½Ã
	DrawDebugDirectionalArrow(GetWorld(), com, com + F * DeltaTime,
		10, FColor::Red, false, DeltaTime + 0.0001, 9, 3);
	UE_LOG(LogTemp, Warning, TEXT("F=%s"), *(F.ToString()));

	acc_error += error;
	last_error = error;
}

