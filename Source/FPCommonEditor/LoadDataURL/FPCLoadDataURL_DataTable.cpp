#include "FPCLoadDataURL_DataTable.h"

#include "DataTableEditorUtils.h"
#include "Misc/LazySingleton.h"

FFPCLoadDataURL_DataTable& FFPCLoadDataURL_DataTable::Get()
{
	return TLazySingleton<FFPCLoadDataURL_DataTable>::Get();
}

void FFPCLoadDataURL_DataTable::TearDown()
{
	return TLazySingleton<FFPCLoadDataURL_DataTable>::TearDown();
}

void FFPCLoadDataURL_DataTable::ReceiveCSV(FString CSV, TWeakObjectPtr<UObject> Object)
{
	if (!Object.IsValid())
	{
		return;
	}

	UDataTable* DataTable = Cast<UDataTable>(Object.Get());
	if (!DataTable)
	{
		return;
	}

	DataTable->CreateTableFromCSVString(CSV);
	FDataTableEditorUtils::BroadcastPostChange(DataTable, FDataTableEditorUtils::EDataTableChangeInfo::RowList);
	GEditor->RedrawAllViewports();
}

void FFPCLoadDataURL_DataTable::SetValidClasses(FName& OutAssetClassName, FName& OutAssetEditorName)
{
	OutAssetClassName = UDataTable::StaticClass()->GetFName();
	OutAssetEditorName = FName("DataTableEditor");
}
