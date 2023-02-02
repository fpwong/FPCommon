#pragma once

#include "FPCLoadDataURL_Base.h"

class FFPCLoadDataURL_DataTable final : public FFPCLoadDataURL_Base
{
public:
	virtual ~FFPCLoadDataURL_DataTable() = default;
	static FFPCLoadDataURL_DataTable& Get();
	static void TearDown();

protected:
	virtual void ReceiveCSV(FString CSV, TWeakObjectPtr<UObject> Object) override;
	virtual void SetValidClasses(FName& OutAssetClassName, FName& OutAssetEditorName) override;
};
