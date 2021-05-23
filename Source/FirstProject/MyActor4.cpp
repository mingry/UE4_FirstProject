// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor4.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyActor4::AMyActor4()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	root = CreateDefaultSubobject<USceneComponent>(TEXT("MyRoot"));
	RootComponent = root;

	left_shoulder = CreateDefaultSubobject<USceneComponent>(TEXT("left_shoulder"));
	left_elbow = CreateDefaultSubobject<USceneComponent>(TEXT("left_elbow"));
	left_wrist = CreateDefaultSubobject<USceneComponent>(TEXT("left_wrist"));

	torso = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("torso"));
	left_upper_arm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("left_upper_arm"));
	left_lower_arm = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("left_lower_arm"));
	left_hand = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("left_hand"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> car_11_asset(TEXT("StaticMesh'/Game/Cars/Low_Poly_City_Cars_Car_11.Low_Poly_City_Cars_Car_11'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> car_12_asset(TEXT("StaticMesh'/Game/Cars/Low_Poly_City_Cars_Car_12.Low_Poly_City_Cars_Car_12'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> car_08_asset(TEXT("StaticMesh'/Game/Cars/Low_Poly_City_Cars_Car_08.Low_Poly_City_Cars_Car_08'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> car_07_asset(TEXT("StaticMesh'/Game/Cars/Low_Poly_City_Cars_CAR_07.Low_Poly_City_Cars_CAR_07'"));


	torso->SetStaticMesh((UStaticMesh*)car_08_asset.Object);
	left_lower_arm->SetStaticMesh((UStaticMesh*)car_11_asset.Object);
	left_upper_arm->SetStaticMesh((UStaticMesh*)car_12_asset.Object);
	left_hand->SetStaticMesh((UStaticMesh*)car_07_asset.Object);

	torso->AttachTo(root);
	left_shoulder->AttachTo(torso);
	left_upper_arm->AttachTo(left_shoulder);
	left_elbow->AttachTo(left_upper_arm);
	left_lower_arm->AttachTo(left_elbow);
	left_wrist->AttachTo(left_lower_arm);
	left_hand->AttachTo(left_wrist);

}



// Called when the game starts or when spawned
void AMyActor4::BeginPlay()
{
	Super::BeginPlay();
	time = 0.f;


	
}

bool AMyActor4::ShouldTickIfViewportsOnly() const
{
	return true;
}




// Called every frame
void AMyActor4::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (HasActorBegunPlay())
	{
		time += DeltaTime;

		FRotator k0(0, 0, 0);
		FRotator k1(0, -30, 0);
		
		if (time < 1.0f) {
			left_shoulder->SetRelativeRotation(k0);
			left_elbow->SetRelativeRotation(k0);
			left_wrist->SetRelativeRotation(k0);
		}
		else if ( time < 3.0f ) {
			FQuat q = FQuat::Slerp(FQuat(k0), FQuat(k1), (time - 1.0f) / (2.0f));
			left_shoulder->SetRelativeRotation(q);
			left_elbow->SetRelativeRotation(q);
			left_wrist->SetRelativeRotation(q);
		}
		else {
			left_shoulder->SetRelativeRotation(k1);
			left_elbow->SetRelativeRotation(k1);
			left_wrist->SetRelativeRotation(k1);
		}



	}
	
}

