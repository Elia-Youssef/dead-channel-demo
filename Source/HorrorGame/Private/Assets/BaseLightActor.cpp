// Project By Rebel Art Studios.

#include "Assets/BaseLightActor.h"
#include "Components/LocalLightComponent.h"
#include "Components/SpotLightComponent.h"


ABaseLightActor::ABaseLightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->SetMobility(EComponentMobility::Static);
}

void ABaseLightActor::ToggleLights()
{
	if (LightActors.Num() == 0) return;

	bEnable = !bEnable;

	for (ULocalLightComponent* Light : LightActors)
	{
		if (!IsValid(Light)) return;
		Light->SetVisibility(bEnable);
	}
}

void ABaseLightActor::ForceToggleLights(bool bForceOn)
{
	if (LightActors.Num() == 0) return;

	bEnable = bForceOn;

	for (ULocalLightComponent* Light : LightActors)
	{
		if (!IsValid(Light)) return;
		Light->SetVisibility(bForceOn);
	}
}

// Called when the game starts or when spawned
void ABaseLightActor::BeginPlay()
{
	Super::BeginPlay();

	CacheLights();
	UpdateLights();
	ForceToggleLights(false);
}

void ABaseLightActor::CallReceivingActor_Implementation()
{
	IHorrorInterfaceInteract::CallReceivingActor_Implementation();
	ToggleLights();
}

void ABaseLightActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CacheLights();
	UpdateLights();
}

void ABaseLightActor::CacheLights()
{
	LightActors.Empty();
	TArray<USceneComponent*> ChildActors;
	RootComponent->GetChildrenComponents(true, ChildActors);
	for (USceneComponent* Child : ChildActors)
	{
		if (!IsValid(Child)) continue;
		ULocalLightComponent* ChildLight = Cast<ULocalLightComponent>(Child);
		LightActors.AddUnique(ChildLight);
	}
}

void ABaseLightActor::UpdateLights()
{
	for (ULocalLightComponent* Light : LightActors)
	{
		if (!IsValid(Light)) continue;
		Light->SetIntensityUnits(ELightUnits::Candelas);
		Light->SetVisibility(LightProp.bToggleLight);
		Light->SetCastShadows(LightProp.bToggleShadows);
		Light->SetUseTemperature(LightProp.bUseTemperature);
		Light->SetIntensity(LightProp.LightIntensity);
		Light->SetAttenuationRadius(LightProp.LightAttenuation);
		Light->SetCastShadows(LightProp.bToggleShadows);
		Light->SetSpecularScale(LightProp.SpecIntensity);
		Light->SetTemperature(LightProp.bUseTemperature ? LightProp.LightTemp : 6500.f);
		Light->SetLightColor(LightProp.bUseTemperature ? FLinearColor::White : LightProp.LightColor);

		if (USpotLightComponent* SpoLight = Cast<USpotLightComponent>(Light))
		{
			SpoLight->SetInnerConeAngle(LightProp.InnerCone);
			SpoLight->SetOuterConeAngle(LightProp.OuterCone);
		}
	}
}
