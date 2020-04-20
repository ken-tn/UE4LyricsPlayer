// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LRCPlayer.generated.h"

UCLASS()
class ALRCPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(EditDefaultsOnly, Category = Sound)
		USoundWave* SoundWave;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
		TArray<TArray<float>> Output;

	ALRCPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
