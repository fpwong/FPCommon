#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNodeUtils.h"
// #include "AnimGraphNode_BlendSpaceBase.h"
#include "FPCAnimNode_BlendSpacePlayerScaled.h"
#include "AnimGraphNode_Base.h"
#include "FPCAnimGraphNode_BlendSpacePlayerScaled.generated.h"

UCLASS()
class UFPCAnimGraphNode_BlendSpacePlayerScaled : public UAnimGraphNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Settings)
	FFPCAnimNode_BlendSpacePlayerScaled Node;

	//~ UEdGraphNode interface
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual FText GetMenuCategory() const override;
	//~ End of UEdGraphNode

	//~ Begin UK2Node interface
	virtual void ConvertDeprecatedNode(UEdGraph* Graph, bool bOnlySafeChanges) override;
	//~ End UK2Node interface
};


// UCLASS(MinimalAPI)
// class UAnimGraphNode_BlendSpacePlayerScaled : public UAnimGraphNode_Base
// {
// 	GENERATED_UCLASS_BODY()
//
// 	UPROPERTY(EditAnywhere, Category = Settings)
// 	FFPCAnimNode_BlendSpacePlayerScaled Node;
//
// 	// UEdGraphNode interface
// 	virtual FText GetTooltipText() const override;
// 	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
// 	// End of UEdGraphNode interface
//
// 	// UAnimGraphNode_Base interface
// 	virtual void ValidateAnimNodeDuringCompilation(class USkeleton* ForSkeleton, class FCompilerResultsLog& MessageLog) override;
// 	virtual void BakeDataDuringCompilation(class FCompilerResultsLog& MessageLog) override;
// 	virtual bool DoesSupportTimeForTransitionGetter() const override;
// 	virtual UAnimationAsset* GetAnimationAsset() const override;
// 	virtual const TCHAR* GetTimePropertyName() const override;
// 	virtual UScriptStruct* GetTimePropertyStruct() const override;
// 	virtual void GetAllAnimationSequencesReferred(TArray<UAnimationAsset*>& AnimationAssets) const override;
// 	virtual void ReplaceReferredAnimations(const TMap<UAnimationAsset*, UAnimationAsset*>& AnimAssetReplacementMap) override;
// 	virtual EAnimAssetHandlerType SupportsAssetClass(const UClass* AssetClass) const override;
// 	// End of UAnimGraphNode_Base interface
//
// 	// UK2Node interface
// 	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;
// 	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
// 	virtual FBlueprintNodeSignature GetSignature() const override;
// 	// End of UK2Node interface
//
// 	// UAnimGraphNode_AssetPlayerBase interface
// 	// virtual void SetAnimationAsset(UAnimationAsset* Asset) override;
// 	// End of UAnimGraphNode_AssetPlayerBase interface
//
// private:
// 	/** Helper function for GetNodeTitle */
// 	FText GetNodeTitleForBlendSpace(ENodeTitleType::Type TitleType, UBlendSpaceBase* InBlendSpace) const;
//
// private:
// 	/** Constructing FText strings can be costly, so we cache the node's title */
// 	FNodeTitleTextTable CachedNodeTitles;
// };