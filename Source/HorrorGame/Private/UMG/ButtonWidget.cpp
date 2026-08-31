// Project By Rebel Art Studios.


#include "UMG/ButtonWidget.h"
#include "Components/TextBlock.h"

void UButtonWidget::SetLabelText(const FText& Text)
{
	if (IsValid(LabelText))
	{
		LabelText->SetText(Text);
	}
}
