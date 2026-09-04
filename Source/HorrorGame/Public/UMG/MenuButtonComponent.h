// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuButtonComponent.generated.h"

// Delegates
DECLARE_MULTICAST_DELEGATE(FButtonAction);
DECLARE_DELEGATE_OneParam(FButtonLevel, FName);

// Forward Declarations
class UTextBlock;
class USizeBox;
class UButton;

// Main Class
UCLASS()
class HORRORGAME_API UMenuButtonComponent : public UUserWidget
{
	GENERATED_BODY()

public:
	// DELEGATE STRUCTS
	FButtonAction ButtonAction;
	FButtonLevel ButtonLevel;

	UPROPERTY()
	FName LevelReceivedName = NAME_None;

	UPROPERTY(EditAnywhere)
	FVector2D ButtonSize = FVector2D(100.f, 40.f);

	UPROPERTY(EditAnywhere)
	FText ButtonName = FText::FromString("ButtonName");

	UPROPERTY(EditAnywhere)
	bool bOverrideName = false;

protected:
	// Native Events
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// Helpers
	void BindActions();
	void UpdateButton();

	// Delegate Calls
	void HandleAction();
	void HandleLevel(FName LevelName);

private:
	// Components
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBoxComp = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UButton> ButtonComp = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlockComp = nullptr;
};
