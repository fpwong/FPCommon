#pragma once

#include "FPCLoadDataURL_Base.h"

class FFPCLoadDataURL_CurveTable final : public FFPCLoadDataURL_Base
{
public:
	virtual ~FFPCLoadDataURL_CurveTable() = default;
	static FFPCLoadDataURL_CurveTable& Get();
	static void TearDown();

protected:
	virtual void ReceiveCSV(FString CSV, TWeakObjectPtr<UObject> Object) override;
	virtual void SetValidClasses(FName& OutAssetClassName, FName& OutAssetEditorName) override;
};
