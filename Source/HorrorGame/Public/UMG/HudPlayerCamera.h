// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudPlayerCamera.generated.h"


class UImage;
class UHorizontalBox;
class UTextBlock;

UCLASS()
class HORRORGAME_API UHudPlayerCamera : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Native Events
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	// Helpers 
	void ToggleAnimation(bool bToggle);

private:
	// Components
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> CamName = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> IconBox = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> CamIcon = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> Rec = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UImage> FocusZone = nullptr;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> RecAnim = nullptr;
};
