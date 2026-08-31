// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudFlashLight.generated.h"

class USizeBox;
// Forward Declarations
class UImage;
class UProgressBar;

// Enum Class
UENUM()
enum class EFlashLightColor : uint8
{
	EFlashLightOff,
	EFlashLightOn,
	EFlashLightLow
};

// Main Class
UCLASS()
class HORRORGAME_API UHudFlashLight : public UUserWidget
{
	GENERATED_BODY()

public:
	// Public Events
	UFUNCTION()
	void ToggleLightIcon(bool bEnable);

	UFUNCTION()
	void UpdateLightWidget(float Progress);

	// Public Variables
	UPROPERTY(EditAnywhere)
	FVector2D LightIconSize = FVector2D(16.0f, 16.0f);

protected:
	// Native Events
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	// Private Components
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<USizeBox> LightIconBox;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> FlashLightImage = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> FlashLightScrollBar = nullptr;

	// Private Variables
	UPROPERTY(EditDefaultsOnly)
	FLinearColor LightOffColor = FLinearColor(0.f, 0.f, 0.f, 1.f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LightOnColor = FLinearColor(1.f, 0.8f, 0.f, 1.f);

	UPROPERTY(EditDefaultsOnly)
	FLinearColor LightLowColor = FLinearColor(0.2f, 0.f, 0.f, 1.f);

	bool bIsLightEnabled = false;
	float LastBatteryProgress = 100.f;

	// Private Events
	void UpdateLightScrollBar(float Progress);
	void UpdateLightIconColor(float Progress);
	void UpdateSizeBox();
};
