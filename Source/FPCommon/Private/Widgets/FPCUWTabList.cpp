#include "Widgets/FPCUWTabList.h"

#include "CommonActivatableWidget.h"
#include "CommonAnimatedSwitcher.h"
#include "CommonButtonBase.h"
#include "Widgets/FPCTabNameInterface.h"
#include "Widgets/FPCUWCommonButton.h"

bool UFPCUWTabList::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (IsDesignTime())
	{
		return true;
	}

	if (!WidgetSwitcher)
	{
		return false;
	}

	SetLinkedSwitcher(WidgetSwitcher);

	const auto Children = WidgetSwitcher->GetAllChildren();
	for (int i = 0; i < Children.Num(); ++i)
	{
		UWidget* Child = Children[i];
		if (UCommonActivatableWidget* Activatable = Cast<UCommonActivatableWidget>(Child))
		{
			const FName TabId = FName(*FString::Printf(TEXT("Tab_%d"), i));

			if (RegisterTab(TabId, TabButtonWidgetType, Activatable))
			{
				UCommonButtonBase* TabButtonBase = GetTabButtonBaseByID(TabId);
				TabPanel->AddChild(TabButtonBase);

				if (Activatable->Implements<UFPCTabNameInterface>())
				{
					if (UFPCUWCommonButton* FPButton = Cast<UFPCUWCommonButton>(TabButtonBase))
					{
						FText TabName = IFPCTabNameInterface::Execute_GetTabName(Activatable);
						FPButton->SetButtonLabelText(TabName);
					}
				}
			}
		}
	}

	return true;
}

const FText UFPCUWTabList::GetPaletteCategory()
{
	return FText::FromString("FPCommon");
}
