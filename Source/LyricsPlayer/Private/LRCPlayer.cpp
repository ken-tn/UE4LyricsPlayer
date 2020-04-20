// Fill out your copyright notice in the Description page of Project Settings.


#include "LRCPlayer.h"
#include "Sound/SoundWave.h"
#include "C:\Program Files\Epic Games\UE_4.24\Engine\Plugins\Runtime\SoundVisualizations\Source\SoundVisualizations\Private\SoundVisualizationStatics.cpp"

// Sets default values
ALRCPlayer::ALRCPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALRCPlayer::BeginPlay()
{
	USoundVisualizationStatics Visualizer = USoundVisualizationStatics();
    Visualizer.CalculateFrequencySpectrum(Sound,
        true,
        0.f,
        5.f,
        int32(5),
        Output);

	Super::BeginPlay();
}

// Called every frame
void ALRCPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

