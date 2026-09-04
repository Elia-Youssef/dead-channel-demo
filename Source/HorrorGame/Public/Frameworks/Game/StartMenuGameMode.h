// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartMenuGameMode.generated.h"


UCLASS()
class HORRORGAME_API AStartMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Native Events
	virtual void BeginPlay() override;

	// Delegate Events
	void SwitchLevels(FName LevelName);
};
