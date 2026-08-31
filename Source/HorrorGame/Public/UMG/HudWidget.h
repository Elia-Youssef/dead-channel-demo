// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

// Forward Declarations

class UMyClass;
class UHudFlashLight;
class UTextBlock;
class UImage;
class UWidgetAnimation;

// Enum Class

UENUM()
enum class EHudActions : uint8
{
	Move, Restart, Quit, Sprint, Jump, ChangeView, Flashlight, Interact, Drone
};

// Main Class

UCLASS()
class HORRORGAME_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Public Events
	UFUNCTION()
	void ToggleCrosshair(const bool bEnable);
	
	UFUNCTION()
	void ToggleInteractionText(const bool bEnable, const FText NewText);

	UFUNCTION()
	void SwitchColor(EHudActions Action, bool bOn);
	
	UFUNCTION()
	void ToggleHudWidget(bool bEnable);

	UFUNCTION()
	void UpdateFlashlightBattery(float CurrentBattery, float MaxBattery);

	UFUNCTION()
	void UpdateFlashlightState(bool bIsOn);


protected:
	// Native Events
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	//
	void InitialTextColors();

private:
	// Helper Function
	UTextBlock* GetActionText(EHudActions Action) const;

	//// Private Components
	///
	// Child Components
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHudFlashLight> HudFlashLightComp;

	// Crosshair
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CrosshairImage = nullptr;
	
	// Interaction
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionText = nullptr;

	// Upper Panel

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GeneralText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> RestartText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuitText = nullptr;

	// Lower Panel

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> PanelText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText1Text = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText2Text = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText3Text = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText4Text = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText5Text = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText6Text = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText7Text = nullptr;
	
	// Animation
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> CrosshairAnimation = nullptr;

	// Internal Array
	UPROPERTY(EditDefaultsOnly)
	FSlateColor StartColor = FLinearColor(0.85f, 0.85f, 0.85f, 1.f);

	UPROPERTY(EditDefaultsOnly)
	FSlateColor EndColor = FLinearColor(0.8f, 0.f, 0.f, 1.f);
	
	UPROPERTY()
	TArray<TObjectPtr<UTextBlock>> TextBlocks;
};
