#pragma once

#include "CoreMinimal.h"
#include "AnimNodes/AnimNode_BlendSpacePlayer.h"
#include "FPCAnimNode_BlendSpacePlayerScaled.generated.h"

USTRUCT()
struct FPCOMMON_API FFPCAnimNode_BlendSpacePlayerScaled : public FAnimNode_BlendSpacePlayer
{
	GENERATED_USTRUCT_BODY()
public:
	virtual void UpdateAssetPlayer(const FAnimationUpdateContext& Context) override;
};