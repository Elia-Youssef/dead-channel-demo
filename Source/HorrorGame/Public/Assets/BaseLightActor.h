// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Frameworks/Interfaces/HorrorInterfaceInteract.h"
#include "GameFramework/Actor.h"
#include "Data/Utils.h"
#include "BaseLightActor.generated.h"

class ULocalLightComponent;
class USpotLightComponent;

UCLASS()
class HORRORGAME_API ABaseLightActor : public AActor, public IHorrorInterfaceInteract
{
	GENERATED_BODY()

public:
	// Native Events
	ABaseLightActor();
	virtual void OnConstruction(const FTransform& Transform) override;

	// LightControl
	

protected:
	// Native Events
	virtual void BeginPlay() override;
	
	virtual void CallReceivingActor_Implementation() override;

private:
	// Helper Functions
	void CacheLights();
	void UpdateLights();
	void ToggleLights();
	void ForceToggleLights(bool bForceOn);

	// Private Variables
	UPROPERTY()
	TArray<ULocalLightComponent*> LightActors;

	UPROPERTY(EditAnywhere)
	FLightProperties LightProp;
	
	bool bEnable = false;
};
