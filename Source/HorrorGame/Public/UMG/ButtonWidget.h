// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"

class USizeBox;
class UTextBlock;

UCLASS()
class HORRORGAME_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetLabelText(const FText& Text);

private:
	// Private Components

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> LabelSizeBox = nullptr;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> LabelText = nullptr;
};
