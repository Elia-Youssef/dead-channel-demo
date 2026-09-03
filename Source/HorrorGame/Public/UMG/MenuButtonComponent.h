// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuButtonComponent.generated.h"

// Delegates
// DECLARE_MULTICAST_DELEGATE_OneParam()

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


protected:
	// Native Events
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	// Helpers
	void UpdateButton();

private:
	// Components
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBoxComp = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UButton> ButtonComp = nullptr;

	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UTextBlock> TextBlockComp = nullptr;
};
