// Project By Rebel Art Studios.


#include "Frameworks/Players/PlayerCamComponent.h"


UPlayerCamComponent::UPlayerCamComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}


void UPlayerCamComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerCamComponent::OnConstruction(const FTransform& Transform)
{
	AdjustPostProcessSettings();
}

void UPlayerCamComponent::AdjustPostProcessSettings()
{
	
}

