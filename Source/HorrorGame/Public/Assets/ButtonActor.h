// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractableActor.h"
#include "Data/Utils.h"
#include "ButtonActor.generated.h"

class UButtonWidget;
class UWidgetComponent;

UCLASS()
class HORRORGAME_API AButtonActor : public ABaseInteractableActor
{
	GENERATED_BODY()

public:
	// Native Events
	AButtonActor();
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION()
	void ButtonPressed(bool bPressed);

protected:
	// Native Events
	virtual void BeginPlay() override;
	
	// Interface Events
	
	virtual void DoInteraction_Implementation() override;

private:
	// Components
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> BaseMeshComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMeshComponent> TopMeshComp = nullptr;

	UPROPERTY(EditAnywhere)
	TArray<TObjectPtr<AActor>> CalledActors;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UButtonWidget> ButtonWidgetClass;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UWidgetComponent> WidgetComp = nullptr;

	// Helper Functions
	void AssignMaterial();
	void UpdateEmissiveProp();
	void SetWidgetText();
	void ToggleWidget(bool bEnable);

	// Variables
	UPROPERTY(EditAnywhere)
	FEmissiveProperties EmissiveProp;

	UPROPERTY(EditDefaultsOnly)
	float OffMultiplier = 0.1f;
};
