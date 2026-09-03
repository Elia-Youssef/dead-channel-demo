// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCamComponent.generated.h"


class UPostProcessComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORGAME_API UPlayerCamComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Native Events
	UPlayerCamComponent();
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform);
	
protected:
	// Helpers
	void AdjustPostProcessSettings();
	


private:
	// Components
	UPROPERTY(EditAnywhere)
	TObjectPtr<UPostProcessComponent> PlayerCamPostProcess = nullptr;
	
	// UPROPERTY(EditDefaultsOnly)
	



};
