#pragma once

#include "FPCAnimNode_BlendSpacePlayerScaled.h"
#include "Animation/BlendSpaceBase.h"

void FFPCAnimNode_BlendSpacePlayerScaled::UpdateAssetPlayer(const FAnimationUpdateContext& Context)
{
#if WITH_EDITORONLY_DATA
	const UBlendSpace* CurrBlendSpace = GetBlendSpace();
	float CurrPlayRate = GetPlayRate();
	const FVector CurrPosition = GetPosition();

	// TODO: make this actually set the play rate realtime? (currently unused?)
	if (CurrBlendSpace != nullptr && CurrPosition.X > CurrBlendSpace->GetBlendParameter(0).Max)
	{
		// PlayRate = Position.X / BlendSpace->GetBlendParameter(0).Max;
	}
	else
	{
		// PlayRate = 1.0f;
	}
#endif

	Super::UpdateAssetPlayer(Context);
}
