// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/AmbientSound.h"
#include "Materials/MaterialInstanceConstant.h"
#include "VisualizerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LYRICSPLAYER_API UVisualizerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVisualizerComponent();

	/*
	* PROPERTIES
	*/
	TMap<AActor*, float> ActorFrequency;
	bool HasFFT;
	TArray<FTransform> Transforms;
	FTransform OriginalTransform;
	AActor* Start = GetOwner();

	UPROPERTY(EditAnywhere, Category = "Appearance")
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, Category = "Appearance")
		UMaterialInstanceConstant* Material;

	UPROPERTY(EditAnywhere, Category = "Appearance")
		FLinearColor ColorTop = FLinearColor(1.f, 1.f, 1.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Appearance")
		FLinearColor ColorBottom = FLinearColor(1.f, 0.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Audio")
		AAmbientSound* AmbientSound;

	UPROPERTY(EditAnywhere, Category = "Visual Settings")
		int NumberOfBars = 300;

	UPROPERTY(EditAnywhere, Category = "Visual Settings")
		float BarDistance = 15.f;

	UPROPERTY(EditAnywhere, Category = "Visual Settings")
		float Height = 1.f;

	UPROPERTY(EditAnywhere, Category = "Smoothing")
		float MaxDistance = 5000.f;

	UPROPERTY(EditAnywhere, Category = "Smoothing")
		float MinWeight = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Smoothing")
		float MaxWeight = 0.6f;

	UPROPERTY(EditAnywhere, Category = "Frequencies")
		float MinFrequency = 20.f;

	UPROPERTY(EditAnywhere, Category = "Frequencies")
		float MaxFrequency = 20000.f;

	/*
	* FUNCTIONS
	*/
	AActor* SpawnCube(FTransform SpawnTransform);
	bool CreateBars();

	UFUNCTION(BlueprintCallable, Category = "VisualizerSupport")
		void OnBeginPlay();

	UFUNCTION(BlueprintCallable, Category = "VisualizerSupport")
		void OnTick();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
