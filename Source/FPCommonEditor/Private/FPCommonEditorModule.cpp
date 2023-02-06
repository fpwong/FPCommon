// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FPCommonEditorModule.h"

#define LOCTEXT_NAMESPACE "FPCommonEditorModule"

void FFPCommonEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	UE_LOG(LogTemp, Log, TEXT("Loaded FPCommonEditor startup module"));

#if WITH_EDITOR
	FCoreDelegates::OnPostEngineInit.AddRaw(this, &FFPCommonEditorModule::OnPostEngineInit);
#endif
}

void FFPCommonEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FFPCommonEditorModule::OnPostEngineInit()
{
	UE_LOG(LogTemp, Log, TEXT("FPCommonEditor::OnPostEngineInit"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFPCommonEditorModule, FPCommonEditor)
