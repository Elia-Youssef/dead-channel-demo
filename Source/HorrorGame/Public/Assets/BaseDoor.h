// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "BaseInteractableActor.h"
#include "BaseDoor.generated.h"

UCLASS()
class HORRORGAME_API ABaseDoor : public ABaseInteractableActor
{
	GENERATED_BODY()

public:
	ABaseDoor();

protected:
	// Native Events
	virtual void BeginPlay() override;

private:
	
	// Private Compontns
	

};
