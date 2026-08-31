// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Frameworks/HorrorInterfaceInteract.h"
#include "BaseInteractableActor.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class HORRORGAME_API ABaseInteractableActor : public AActor, public IHorrorInterfaceInteract
{
	GENERATED_BODY()

public:
	// Public Native Events
	ABaseInteractableActor();

	UPROPERTY(EditAnywhere)
	FText MyActorLabel = FText::FromString("");

protected:
	// Protected Native Events

	virtual void BeginPlay() override;

	// Collision Events

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	// Interface Events
	UFUNCTION()
	virtual void DoInteraction_Implementation() override;

private:
	// Private Components

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UArrowComponent> ArrowComp = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UBoxComponent> BoxComp = nullptr;
};
