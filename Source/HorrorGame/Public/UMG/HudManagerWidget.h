// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HudManagerWidget.generated.h"

// Forward Declarations
class UHudPlayerCamera;
class UHudPlayerMain;
class UWidgetSwitcher;

// Switcher Enum
UENUM()
enum class ESwitchMenus : uint8
{
	MainHud, CameraHud
};

// Main Class
UCLASS()
class HORRORGAME_API UHudManagerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SwitchMenus(ESwitchMenus Menu);

	UHudPlayerMain* GetPlayerMainHud() const;
	UHudPlayerCamera* GetPlayerCam() const;

protected:
	// Native Events
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UWidgetSwitcher> HudSwitcher = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UHudPlayerMain> HudPlayerMain = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	TObjectPtr<UHudPlayerCamera> HudPlayerCam = nullptr;
};
