#pragma once

#include "FPCTabNameInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UFPCTabNameInterface : public UInterface
{
	GENERATED_BODY()
};

class IFPCTabNameInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="FPCommon")
	FText GetTabName();
};
