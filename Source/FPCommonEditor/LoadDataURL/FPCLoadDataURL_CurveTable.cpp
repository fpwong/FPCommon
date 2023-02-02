#include "FPCLoadDataURL_CurveTable.h"

#include "CurveTableEditorUtils.h"
#include "Misc/LazySingleton.h"

FFPCLoadDataURL_CurveTable& FFPCLoadDataURL_CurveTable::Get()
{
	return TLazySingleton<FFPCLoadDataURL_CurveTable>::Get();
}

void FFPCLoadDataURL_CurveTable::TearDown()
{
	return TLazySingleton<FFPCLoadDataURL_CurveTable>::TearDown();
}

void FFPCLoadDataURL_CurveTable::ReceiveCSV(FString CSV, TWeakObjectPtr<UObject> Object)
{
	if (!Object.IsValid())
	{
		return;
	}

	UCurveTable* CurveTable = Cast<UCurveTable>(Object.Get());
	if (!CurveTable)
	{
		return;
	}

	CurveTable->CreateTableFromCSVString(CSV);
	FCurveTableEditorUtils::BroadcastPostChange(CurveTable, FCurveTableEditorUtils::ECurveTableChangeInfo::RowList);
	GEditor->RedrawAllViewports();
	UE_LOG(LogTemp, Warning, TEXT("Did stuff"));
}

void FFPCLoadDataURL_CurveTable::SetValidClasses(FName& OutAssetClassName, FName& OutAssetEditorName)
{
	OutAssetClassName = UCurveTable::StaticClass()->GetFName();
	OutAssetEditorName = FName("CurveTableEditor");
}
