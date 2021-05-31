// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor7.generated.h"

UCLASS()
class FIRSTPROJECT_API AMyActor7 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor7();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* root;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* physics_drone;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* goal;

	UPROPERTY(EditAnywhere)
		float kp;

	UPROPERTY(EditAnywhere)
		float kd;

	UPROPERTY(EditAnywhere)
		float ki;

	float time;
	FVector last_error;
	FVector acc_error;
};
