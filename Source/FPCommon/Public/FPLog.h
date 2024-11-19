#pragma once

#include "Logging/StructuredLog.h"

// class FPCOMMON_API FFPLog
// {
// public:
// 	static FString GetWorldNetMode(UWorld* World)
// 	{
// 		if (World && World->WorldType == EWorldType::PIE)
// 		{
// 			switch (World->GetNetMode())
// 			{
// 			case NM_Client:
// 				return FString::Printf(TEXT("Client %d: "), static_cast<int>(GPlayInEditorID));
// 			case NM_DedicatedServer:
// 			case NM_ListenServer:
// 				return FString::Printf(TEXT("Server: "));
// 			case NM_Standalone:
// 				break;
// 			}
// 		}
// 		return "";
// 	}
// };

#define FP_STRFMT(Fmt, ...) FString::Format(TEXT(Fmt), { __VA_ARGS__ })
#define FP_IMGUILOG(Fmt, ...) IMGUI_DEBUG_LOG(TCHAR_TO_ANSI(*FP_STRFMT(Fmt, __VA_ARGS__)))
#define FP_IMGUITEXT(Fmt, ...) ImGui::Text(TCHAR_TO_ANSI(*FP_STRFMT(Fmt, __VA_ARGS__)))
#define FP_IMGUILOG_WRAPPED(Fmt, ...) const ImGui::FScopedContext ScopedContext; { if (ScopedContext) FP_IMGUILOG(Fmt, { __VA_ARGS__ }); }
// #define FP_LOGWORLD(World, CategoryName, Verbosity, Format, ...) UE_LOGFMT(CategoryName, Verbosity, TEXT(FFPLog::GetWorldNetMode(World) + Format), __VA_ARGS__)
