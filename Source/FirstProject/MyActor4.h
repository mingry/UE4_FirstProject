// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor4.generated.h"

UCLASS()
class FIRSTPROJECT_API AMyActor4 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor4();

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
		USceneComponent* left_shoulder;

	UPROPERTY(EditAnywhere)
		USceneComponent* left_elbow;

	UPROPERTY(EditAnywhere)
		USceneComponent* left_wrist;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* torso;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* left_upper_arm;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* left_lower_arm;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* left_hand;


	float time;

};
