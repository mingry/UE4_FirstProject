// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor2.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor2::AMyActor2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh1"));
	key0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key0"));
	key1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key1"));
	key2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key2"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeliAsset(TEXT("StaticMesh'/Game/H/Helecopter.Helecopter'"));

	if (HeliAsset.Succeeded()) {
		UStaticMesh* m = HeliAsset.Object;
		mesh1->SetStaticMesh(m);
		key0->SetStaticMesh(m);
		key1->SetStaticMesh(m);
		key2->SetStaticMesh(m);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HeliAsset Fail"));
	}

	mesh1->AttachTo(root);
	key0->AttachTo(root);
	key1->AttachTo(root);

	key0->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 100.f), FRotator(30.0f, 0.0f, 0.0f));
	key1->SetRelativeLocationAndRotation(FVector(100.0f, 100.0f, 200.f), FRotator(0.0f, 30.0f, 90.0f));
	key2->SetRelativeLocationAndRotation(FVector(100.0f, 100.0f, 200.f), FRotator(0.0f, 30.0f, 90.0f));

	t0 = 0.5f;
	t1 = 2.5f;
	t2 = 5.0f;
}

// Called when the game starts or when spawned
void AMyActor2::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	if (camera_actor)
	{
		GetWorld()->GetFirstPlayerController()->SetViewTarget(camera_actor);
		heli_to_cam = camera_actor->GetActorLocation() - key0->GetComponentLocation();
	}

	// DrawDebugBox(GetWorld(), FVector(0.0f, 0.0f, 100.0f), FVector(10.0f, 10.0f, 10.0f), FColor::Red, true, 3.0f);
	
	
}

bool AMyActor2::ShouldTickIfViewportsOnly() const
{
	return true;
}




// Called every frame
void AMyActor2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasActorBegunPlay())
	{
		time += DeltaTime;

		FVector p;
		FQuat q;

		if (time < t0)
		{
			p = key0->GetRelativeLocation();
			q = FQuat(key0->GetRelativeRotation());
		}
		else if (time < t1)
		{
			FVector p0 = key0->GetRelativeLocation();
			FQuat q0 = FQuat(key0->GetRelativeRotation());
			FVector p1 = key1->GetRelativeLocation();
			FQuat q1 = FQuat(key1->GetRelativeRotation());

			p = (time - t0) / (t1 - t0) * (p1 - p0) + p0;
			q = FQuat::Slerp(q0, q1, (time - t0) / (t1 - t0));
		}
		else if (time < t2)
		{
			FVector p0 = key1->GetRelativeLocation();
			FQuat q0 = FQuat(key1->GetRelativeRotation());
			FVector p1 = key2->GetRelativeLocation();
			FQuat q1 = FQuat(key2->GetRelativeRotation());

			p = (time - t1) / (t2 - t1) * (p1 - p0) + p0;
			q = FQuat::Slerp(q0, q1, (time - t1) / (t2 - t1));
		}
		else
		{
			p = key2->GetRelativeLocation();
			q = FQuat(key2->GetRelativeRotation());
		}

		mesh1->SetRelativeLocationAndRotation(p, q);

		if (camera_actor)
		{
			FVector world_heli_p = mesh1->GetComponentLocation();
			camera_actor->SetActorLocation(world_heli_p + heli_to_cam);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), key0->GetComponentLocation(), key1->GetComponentLocation(), FColor::Red, false, 1.0f/30.0f);
		DrawDebugLine(GetWorld(), key1->GetComponentLocation(), key2->GetComponentLocation(), FColor::Red, false, 1.0f/30.0f);
	}
}

