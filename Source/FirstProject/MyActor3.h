// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor3.generated.h"

UCLASS()
class FIRSTPROJECT_API AMyActor3 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor3();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual bool ShouldTickIfViewportsOnly() const override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh1;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key0;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key1;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key2;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* key3;


	UPROPERTY(EditAnywhere)
		float t0;

	UPROPERTY(EditAnywhere)
		float t1;

	UPROPERTY(EditAnywhere)
		float t2;

	UPROPERTY(EditAnywhere)
		float t3;

	UPROPERTY(EditAnywhere)
		AActor* camera_actor;

	FVector heli_to_cam;

	float time;
};
