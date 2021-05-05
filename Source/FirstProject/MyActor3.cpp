// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor3.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor3::AMyActor3()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh1"));
	inst_mesh1 = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("InstMesh1"));
	key0 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key0"));
	key1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key1"));
	key2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key2"));
	key3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("key3"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HeliAsset(TEXT("StaticMesh'/Game/H/Helecopter.Helecopter'"));

	if (HeliAsset.Succeeded()) {
		UStaticMesh* m = HeliAsset.Object;
		mesh1->SetStaticMesh(m);
		inst_mesh1->SetStaticMesh(m);
		key0->SetStaticMesh(m);
		key1->SetStaticMesh(m);
		key2->SetStaticMesh(m);
		key3->SetStaticMesh(m);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("HeliAsset Fail"));
	}

	mesh1->AttachTo(root);
	inst_mesh1->AttachTo(root);
	key0->AttachTo(root);
	key1->AttachTo(root);
	key2->AttachTo(root);
	key3->AttachTo(root);

	key0->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 100.f), FRotator(30.0f, 0.0f, 0.0f));
	key1->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 100.f), FRotator(30.0f, 0.0f, 0.0f));;
	key2->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 100.f), FRotator(30.0f, 0.0f, 0.0f));
	key3->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 100.f), FRotator(30.0f, 0.0f, 0.0f));

	t0 = 0.5f;
	t1 = 2.5f;
	t2 = 5.0f;
	t3 = 7.0f;

	for (int i = 0; i < 100; i++) {
		FTransform T;
		T.SetScale3D(FVector(0.f, 0.f, 0.f));
		inst_mesh1->AddInstance(T);
	}
}

// Called when the game starts or when spawned
void AMyActor3::BeginPlay()
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

bool AMyActor3::ShouldTickIfViewportsOnly() const
{
	return true;
}


FTransform AMyActor3::GetSplineIterp(float t)
{
	FVector p;
	FQuat q;
	FVector p0 = key0->GetRelativeLocation();
	FVector p1 = key1->GetRelativeLocation();
	FVector p2 = key2->GetRelativeLocation();
	FVector p3 = key3->GetRelativeLocation();
	FQuat q0 = FQuat(key0->GetRelativeRotation());
	FQuat q1 = FQuat(key1->GetRelativeRotation());
	FQuat q2 = FQuat(key2->GetRelativeRotation());
	FQuat q3 = FQuat(key3->GetRelativeRotation());

	if (t < t0)
	{
		p = p0;
		q = q0;
	}
	else if (t < t1)
	{
		p = FMath::CubicCRSplineInterpSafe(p0, p0, p1, p2, t0 - 1.f, t0, t1, t2, t);
		q = FMath::CubicCRSplineInterpSafe(q0, q0, q1, q2, t0 - 1.f, t0, t1, t2, t);
	}
	else if (t < t2)
	{
		p = FMath::CubicCRSplineInterpSafe(p0, p1, p2, p3, t0, t1, t2, t3, t);
		q = FMath::CubicCRSplineInterpSafe(q0, q1, q2, q3, t0, t1, t2, t3, t);
	}
	else if (t < t3)
	{
		p = FMath::CubicCRSplineInterpSafe(p1, p2, p3, p3, t1, t2, t3, t3 + 1.f, t);
		q = FMath::CubicCRSplineInterpSafe(q1, q2, q3, q3, t1, t2, t3, t3 + 1.f, t);
	}
	else
	{
		p = p3;
		q = q3;
	}

	FTransform T;

	T.SetLocation(p);
	q.Normalize();
	T.SetRotation(q);

	return T;
}



// Called every frame
void AMyActor3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasActorBegunPlay())
	{
		time += DeltaTime;


		for (int i=0; i < inst_mesh1->GetInstanceCount(); i++)
		{
			FTransform T;
			T.SetScale3D(FVector(0.f, 0.f, 0.f));
			inst_mesh1->UpdateInstanceTransform(i, T, false, true);
		}
				
		FTransform T = GetSplineIterp(time);

		mesh1->SetRelativeTransform(T);


		if (camera_actor)
		{
			FVector world_heli_p = mesh1->GetComponentLocation();
			camera_actor->SetActorLocation(world_heli_p + heli_to_cam);
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), key0->GetComponentLocation(), key1->GetComponentLocation(), FColor::Red, false, 1.0f / 30.0f);
		DrawDebugLine(GetWorld(), key1->GetComponentLocation(), key2->GetComponentLocation(), FColor::Red, false, 1.0f / 30.0f);
		DrawDebugLine(GetWorld(), key2->GetComponentLocation(), key3->GetComponentLocation(), FColor::Red, false, 1.0f / 30.0f);
		

		int i = 0; 
		for (float t = t0; t < t3; t += 0.3f)
		{
			if (i >= inst_mesh1->GetInstanceCount()) break;

			FTransform T;
			T = GetSplineIterp(t);
			inst_mesh1->UpdateInstanceTransform(i, T, false, true);
			i++;
		}
		for (; i < inst_mesh1->GetInstanceCount(); i++)
		{
			FTransform T;
			T.SetScale3D(FVector(0.f, 0.f, 0.f));
			inst_mesh1->UpdateInstanceTransform(i, T, false, true);
		}
	}
}

