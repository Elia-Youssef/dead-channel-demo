// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Data/Utils.h"
#include "StartMenuPlayerController.generated.h"

// Delegates
DECLARE_DELEGATE_OneParam(FOnLevelSwitchRequested, FName)

// Forward Declarations
class UStartMenuManagerWidget;

// Main Class
UCLASS()
class HORRORGAME_API AStartMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Public Native Events
	AStartMenuPlayerController();

	// Public Events
	UFUNCTION()
	void CallExitLoop();

	UFUNCTION()
	void CallSwitchLevel(FName LevelName);
	
	
	FOnLevelSwitchRequested OnLevelSwitchRequested;

protected:
	// Native Events
	virtual void BeginPlay() override;

	// Helpers
	void FreezePlayer();
	void SpawnMenu();
	void ToggleMenu(bool bToggleWidget);
	void ToggleCursor(bool bToggle);
	


	void CameraFadeControl(EFadeType FadeType);

private:
	// Components
	UPROPERTY(EditDefaultsOnly, Category="PC|Widgets")
	TSubclassOf<UStartMenuManagerWidget> MenuWidgetClass = nullptr;

	UPROPERTY()
	TObjectPtr<UStartMenuManagerWidget> MenuWidgetPointer = nullptr;

	// Variables
	UPROPERTY(EditDefaultsOnly, Category="PC|Widgets")
	float TimerDelay = 2.f;

	// Timer Controls
	FTimerHandle WidgetTimerHandle;

	void WidgetTimer(bool bPlayForward);
	
	FTimerHandle InputModeTimerHandle;
	void InputModeTimer();
	
	UPROPERTY(EditDefaultsOnly)
	float InputModeTimerDelay = 2.f;
	
};
