// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/KismetMathLibrary.h"
#include "VisualizerComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Components/AudioComponent.h"
#include "Engine/EngineTypes.h"

// Sets default values for this component's properties
UVisualizerComponent::UVisualizerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UVisualizerComponent::SpawnCube(FTransform SpawnTransform)
{
	FActorSpawnParameters SpawnInfo; // Placeholder
	
	AStaticMeshActor* NewCube = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnTransform, SpawnInfo);
	NewCube->SetMobility(EComponentMobility::Movable);

	UStaticMeshComponent* StaticMesh = NewCube->GetStaticMeshComponent();
	StaticMesh->SetStaticMesh(Mesh);

	UMaterialInstanceDynamic* DynamicMaterial = StaticMesh->CreateDynamicMaterialInstance(0, Material, FName("MaterialInstanceDynamic"));
	DynamicMaterial->SetVectorParameterValue(FName("ColorTop"), ColorTop);
	DynamicMaterial->SetVectorParameterValue(FName("ColorBottom"), ColorBottom);

	return NewCube;
}

bool UVisualizerComponent::CreateBars()
{
	for (int i = 0; i < NumberOfBars; i++) {
		FVector BarLocation = FVector(0.f, i * BarDistance, 0.f) + OriginalTransform.GetLocation();
		AActor* BarActor = SpawnCube(FTransform(OriginalTransform.GetRotation(), BarLocation, OriginalTransform.GetScale3D()));

		ActorFrequency.Add(BarActor, ((MaxFrequency - MinFrequency) / NumberOfBars) * i + MinFrequency);
	}

	return true;
}

void UVisualizerComponent::OnBeginPlay()
{
	if (IsValid(AmbientSound) && IsValid(Mesh) && IsValid(Material))
	{
		// Set default properties
		HasFFT = AmbientSound->GetAudioComponent()->HasCookedFFTData();
		OriginalTransform = Start->GetActorTransform();

		// Set default transforms
		if (ActorFrequency.Num() == 0 && CreateBars())
		{
			for (auto& Elem : ActorFrequency)
			{
				Transforms.Add(Elem.Key->GetActorTransform());
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("VISUALIZER HAS INVALID SETTINGS"));
	}
}

void UVisualizerComponent::OnTick()
{
	if (HasFFT) {
		TArray<AActor*> Actors;
		TArray<float> FrequenciesToGet;
		TArray<FSoundWaveSpectralData> SpectralDataArray;

		ActorFrequency.GenerateKeyArray(Actors);
		ActorFrequency.GenerateValueArray(FrequenciesToGet);

		if (AmbientSound->GetAudioComponent()->GetCookedFFTData(FrequenciesToGet, SpectralDataArray))
		{
			// Apply smoothing
			float previousValue = SpectralDataArray[0].NormalizedMagnitude;
			for (FSoundWaveSpectralData& elem : SpectralDataArray)
			{
				previousValue = UKismetMathLibrary::DynamicWeightedMovingAverage_Float(elem.NormalizedMagnitude, previousValue, MaxDistance, MinWeight, MaxWeight);
				elem.NormalizedMagnitude = previousValue;
			}

			for (int i = 0; i < SpectralDataArray.Num(); i++)
			{
				FTransform DefaultTransform = Transforms[i];
				float shiftedZ = SpectralDataArray[i].NormalizedMagnitude * Height;

				// Get new size
				FVector NewScale = DefaultTransform.GetScale3D();
				NewScale = NewScale + FVector(0.f, 0.f, shiftedZ);

				Actors[i]->SetActorTransform(FTransform(DefaultTransform.GetRotation(), DefaultTransform.GetLocation(), NewScale));
			}
		}
	}

	return;
}

// Called when the game starts
void UVisualizerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	OnBeginPlay();

}


// Called every frame
void UVisualizerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	OnTick();

}

