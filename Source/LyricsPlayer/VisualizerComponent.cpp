// Fill out your copyright notice in the Description page of Project Settings.


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
	FActorSpawnParameters SpawnInfo;

	AStaticMeshActor* NewCube = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnTransform, SpawnInfo);
	NewCube->SetMobility(EComponentMobility::Movable);

	UStaticMeshComponent* StaticMesh = NewCube->GetStaticMeshComponent();
	StaticMesh->SetStaticMesh(Mesh);
	StaticMesh->SetMaterial(0, Material);

	return NewCube;
}

bool UVisualizerComponent::CreateBars()
{
	for (int i = 0; i < NumberOfBars; i++) {
		FVector BarLocation = FVector(0.f, i * BarDistance, 0.f) + OriginalTransform.GetLocation();
		AActor* BarActor = SpawnCube(FTransform(OriginalTransform.GetRotation(), BarLocation, OriginalTransform.GetScale3D()));

		ActorFrequency.Add(BarActor, FrequencySpacing * i);
	}

	return true;
}

void UVisualizerComponent::OnBeginPlay()
{
	HasFFT = AmbientSound->GetAudioComponent()->HasCookedFFTData();
	OriginalTransform = Start->GetActorTransform();
	if (CreateBars()) {
		for (auto& Elem : ActorFrequency) {
			Transforms.Add(Elem.Key->GetActorTransform());
		}
	}
}

void UVisualizerComponent::OnTick()
{
	if (HasFFT) {
		TArray<float> FrequencyValues;
		TArray<AActor*> Actors;
		TArray<FSoundWaveSpectralData> SpectralDataArray;

		ActorFrequency.GenerateValueArray(FrequencyValues);
		ActorFrequency.GenerateKeyArray(Actors);

		if (AmbientSound->GetAudioComponent()->GetCookedFFTData(FrequencyValues, SpectralDataArray)) {
			int index = 0;
			for (auto& Elem : SpectralDataArray) {
				FTransform BaseTransform = Transforms[index];
				float shiftedZ = Elem.NormalizedMagnitude * Height;

				// Resize the bar
				FVector Scale = BaseTransform.GetScale3D();
				Scale = Scale + FVector(0.f, 0.f, shiftedZ);

				// Shift the bar up to prevent ground sinking
				FVector Location = BaseTransform.GetLocation();
				Location = FVector(Location.X, Location.Y, shiftedZ * (Scale.Y * 1000.f) + Location.Z);

				FTransform NewTransform = FTransform(BaseTransform.GetRotation(), Location, Scale);

				Actors[index]->SetActorTransform(NewTransform);
				index++;
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

