// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudPlayerMain.generated.h"

class UHudFlashLight;
class UImage;
class UTextBlock;
class UWidgetAnimation;

UENUM()
enum class EHudActions : uint8
{
	Move, Restart, Quit, Sprint, Jump, ChangeView, PlayerCamView, Flashlight, Interact, Drone
};

UCLASS()
class HORRORGAME_API UHudPlayerMain : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void ToggleCrosshair(bool bEnable);

	UFUNCTION()
	void ToggleInteractionText(bool bEnable, FText NewText);

	UFUNCTION()
	void SwitchColor(EHudActions Action, bool bOn);

	UFUNCTION()
	void ToggleHudWidget(bool bEnable);

	UFUNCTION()
	void UpdateFlashlightBattery(float CurrentBattery, float MaxBattery);

	UFUNCTION()
	void UpdateFlashlightState(bool bIsOn);

protected:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	void InitialTextColors();

private:
	UTextBlock* GetActionText(EHudActions Action) const;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHudFlashLight> HudFlashLightComp = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CrosshairImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractionText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GeneralText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> RestartText = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> QuitText = nullptr;

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
	
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> LPText8Text = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FSlateColor StartColor = FLinearColor(0.85f, 0.85f, 0.85f, 1.f);

	UPROPERTY(EditDefaultsOnly)
	FSlateColor EndColor = FLinearColor(0.8f, 0.f, 0.f, 1.f);

	UPROPERTY()
	TArray<TObjectPtr<UTextBlock>> TextBlocks;
};
