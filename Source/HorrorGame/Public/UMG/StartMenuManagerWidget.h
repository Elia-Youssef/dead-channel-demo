// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "StartMenuManagerWidget.generated.h"

// Forward Declarations
class UImage;
class UDataTable;
class UMenuButtonComponent;

// Delegates
// DECLARE_MULTICAST_DELEGATE_OneParam();

// Main Class
UCLASS()
class HORRORGAME_API UStartMenuManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Public Events Called From The Player Controller
	void ForceDisableOpacity();
	void ToggleWidget(bool bToggle);

	void CallExitGame();

	void CallSwitchLevel(FName LevelName);

	UFUNCTION()
	void HandleWidgetAnimationFinished();

protected:
	// Native Events
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;

private:
	// Components
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UVerticalBox> LevelsVerticalBox = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UMenuButtonComponent> ExitButton = nullptr;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> WidgetAnim = nullptr;

	// Button Variables
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataTable> LevelDataTable = nullptr;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMenuButtonComponent> ButtonClass = nullptr;

	// Helpers
	void PopulateLevelButtons();
	void PopulateActionButtons();
};
