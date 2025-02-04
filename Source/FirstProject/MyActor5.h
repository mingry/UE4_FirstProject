// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor5.generated.h"

UCLASS()
class FIRSTPROJECT_API AMyActor5 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor5();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		USceneComponent* root;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh1;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh2;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh3;

	float time;

};
