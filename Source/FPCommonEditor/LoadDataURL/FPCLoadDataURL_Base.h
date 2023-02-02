// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Toolkits/IToolkitHost.h"

DECLARE_DELEGATE_OneParam(FFPCOnURLEntered, FString);

struct SFPCURLEntry : SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFPCURLEntry) {}
		SLATE_ARGUMENT(FString, DefaultURL)
		SLATE_ARGUMENT(FFPCOnURLEntered, OnUrlEntered)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

private:
	FFPCOnURLEntered OnURLEntered;
	TSharedPtr<SEditableTextBox> EditableText;
};

class FFPCLoadDataURL_Base
{
public:
	void Init();
	void ImportFromGoogleSheets(TWeakObjectPtr<UObject> Object, FString GoogleSheetsId);

protected:
	~FFPCLoadDataURL_Base() = default;

	virtual void ReceiveCSV(FString String, TWeakObjectPtr<UObject> Object) = 0;
	virtual void SetValidClasses(FName& OutAssetClassName, FName& OutAssetEditorName) = 0;

private:
	FName ValidAssetName;
	FName ValidAssetEditorName;

	// make toolbar button
	void OnAssetOpenedInEditor(UObject* Asset, IAssetEditorInstance* AssetEditor);
	void ExtendToolbar(FToolBarBuilder& ToolbarBuilder, TWeakObjectPtr<UObject> Object);

	// make asset context menu item  
	TSharedRef<FExtender> MakeContextMenuExtender(const TArray<FAssetData>& AssetDataList);
	void AddMenuEntry(FMenuBuilder& MenuBuilder, TWeakObjectPtr<UObject> Object);

	void HandleURLEntered(FString URL, TWeakObjectPtr<UObject> Object);

	void OpenWindow(TWeakObjectPtr<UObject> Object);
};
