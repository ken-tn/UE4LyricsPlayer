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
	UPROPERTY()
		AActor* Start = GetOwner();

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		UStaticMesh* Mesh;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		UMaterialInstanceConstant* Material;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		AAmbientSound* AmbientSound;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		int NumberOfBars = 300;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		float BarDistance = 15.f;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		float MinFrequency = 500.f;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		float MaxFrequency = 10000.f;

	UPROPERTY(EditAnywhere, Category = "VisualizerSettings")
		float Height = 1.f;

	UPROPERTY(VisibleAnywhere, Category = "VisualizerStats")
		TMap<AActor*, float> ActorFrequency;

	UPROPERTY()
		bool HasFFT;

	UPROPERTY()
		TArray<FTransform> Transforms;

	UPROPERTY()
		FTransform OriginalTransform;

	/*
	* FUNCTIONS
	*/
	UFUNCTION()
		AActor* SpawnCube(FTransform SpawnTransform);

	UFUNCTION()
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
