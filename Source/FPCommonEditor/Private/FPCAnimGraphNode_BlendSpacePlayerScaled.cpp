#pragma once

#include "FPCAnimGraphNode_BlendSpacePlayerScaled.h"


#define LOCTEXT_NAMESPACE "BlendSpacePlayerScaledAnimNode"

FText UFPCAnimGraphNode_BlendSpacePlayerScaled::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return LOCTEXT("NodeTitle", "Blend Space Player Scaled");
}

FText UFPCAnimGraphNode_BlendSpacePlayerScaled::GetTooltipText() const
{
	return LOCTEXT("NodeTooltip", "Blend space where the anim play rate is scaled by speed");
}

FText UFPCAnimGraphNode_BlendSpacePlayerScaled::GetMenuCategory() const
{
	return LOCTEXT("NodeCategory", "Blend Space");
}

void UFPCAnimGraphNode_BlendSpacePlayerScaled::ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges)
{
	// //Find deprecated SubjectName pin and set new pin with its value
	// const FName OldPinName = TEXT("SubjectName"); //Variable now has _DEPRECATED appended so can't use GET_MEMBER_NAME_CHECKED
	// const FName NewPinName = GET_MEMBER_NAME_CHECKED(FAnimNode_BlendSpacePlayerScaledPose, BlendSpacePlayerScaledSubjectName);
	// UEdGraphPin** FoundPinPtr = Pins.FindByPredicate([OldPinName](const UEdGraphPin* Other) { return Other->PinName == OldPinName; });
	// if (FoundPinPtr != nullptr)
	// {
	// 	UEdGraphPin** FoundNewPinPtr = Pins.FindByPredicate([NewPinName](const UEdGraphPin* Other) { return Other->PinName == NewPinName; });
	// 	if (FoundNewPinPtr != nullptr)
	// 	{
	// 		UScriptStruct* StructType = FFPCAnimNode_BlendSpacePlayerScaled::StaticStruct();
	// 		UEdGraphPin* OldPin = *FoundPinPtr;
	// 		UEdGraphPin* NewPin = *FoundNewPinPtr;
	//
	// 		//Create new structure from old data
	// 		FFPCAnimNode_BlendSpacePlayerScaled NewName;
	// 		NewName.Name = *OldPin->DefaultValue;
	//
	// 		//Apply new name structure 
	// 		FString StringValue;
	// 		StructType->ExportText(StringValue, &NewName, nullptr, nullptr, EPropertyPortFlags::PPF_None, nullptr);
	// 		NewPin->GetSchema()->TrySetDefaultValue(*NewPin, StringValue);
	//
	// 		//Update node data with graph data
	// 		Node.BlendSpacePlayerScaledSubjectName = NewName;
	// 	}
	// }
}

#undef LOCTEXT_NAMESPACE