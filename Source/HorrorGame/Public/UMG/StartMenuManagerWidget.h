// Project By Rebel Art Studios.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "StartMenuManagerWidget.generated.h"


class UImage;

UCLASS()
class HORRORGAME_API UStartMenuManagerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
protected:
	// Native Events
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	
	
private:
	// Components
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UImage> BackgroundImage = nullptr;
	
	UPROPERTY(EditDefaultsOnly, meta=(BindWidget))
	TObjectPtr<UVerticalBox> VerticalBox = nullptr;
	
};
