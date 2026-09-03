// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HorrorInterfaceInteract.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHorrorInterfaceInteract : public UInterface
{
	GENERATED_BODY()
};

class HORRORGAME_API IHorrorInterfaceInteract
{
	GENERATED_BODY()

public:
	/// Interface Events

	// Controller To Characters Calls
	// Not Used For Now
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CallCharacter_FireInteraction();


	// Character To Actors Calls

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StoreActor(AActor* StoredActor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ShowLabel(const FText& ActorLabelText);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DoInteraction();

	// Actor To Actor
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CallReceivingActor();
};
