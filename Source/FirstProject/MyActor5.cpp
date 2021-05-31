#include "MyActor5.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor5::AMyActor5()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh1"));
	mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh2"));
	mesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh3"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> drone(TEXT("StaticMesh'/Game/D/P4_scaled.P4_scaled'"));

	if (drone.Succeeded()) {
		UStaticMesh* m = drone.Object;
		mesh1->SetStaticMesh(m);
		mesh2->SetStaticMesh(m);
		mesh3->SetStaticMesh(m);
	}

	mesh1->AttachTo(root);
	mesh2->AttachTo(root);
	mesh3->AttachTo(root);
}

// Called when the game starts or when spawned
void AMyActor5::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;

	mesh1->SetSimulatePhysics(true);
	mesh2->SetSimulatePhysics(true);
	mesh3->SetSimulatePhysics(true);

	mesh1->SetMassOverrideInKg(NAME_None, 1.0f);
	mesh2->SetMassOverrideInKg(NAME_None, 1.0f);
	mesh3->SetMassOverrideInKg(NAME_None, 1.0f);
}

// Called every frame
void AMyActor5::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	time += DeltaTime;

	FVector f_mesh1(0.f, 0.f, 1480.0f);
	FVector f_mesh2(0.f, 0.f, 1280.0f);
	FVector f_mesh3(0.f, 0.f, 1680.0f);


	if ((int)time % 2 == 0) {
		mesh1->AddForce(f_mesh1);
		mesh2->AddForce(f_mesh2);
		mesh3->AddForce(f_mesh3);
	}


	FVector v_mesh3 = mesh3->GetComponentVelocity();

	UE_LOG(LogTemp, Warning, TEXT("%fs, vel=%s"), time, *(v_mesh3.ToString()));
}