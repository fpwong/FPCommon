// See https://github.com/riperjack/ue4_googledoc2datatable

#include "FPCGetGoogleSheet.h"

#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

const FString UFPCGetGoogleSheets::ApiBaseUrl = "https://docs.google.com/spreadsheets/d/";

TSharedRef<IHttpRequest> UFPCGetGoogleSheets::RequestWithRoute(FString Subroute)
{
	Http = &FHttpModule::Get();
	TSharedRef<IHttpRequest> Request = Http->CreateRequest();
	Request->SetURL(UFPCGetGoogleSheets::ApiBaseUrl + Subroute);
	SetRequestHeaders(Request);
	return Request;
}

void UFPCGetGoogleSheets::SetRequestHeaders(TSharedRef<IHttpRequest>& Request)
{
	Request->SetHeader(TEXT("User-Agent"), TEXT("X-UnrealEngine-Agent"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("text/csv"));
	Request->SetHeader(TEXT("Accepts"), TEXT("text/csv"));
}

TSharedRef<IHttpRequest> UFPCGetGoogleSheets::GetRequest(FString Subroute)
{
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("GET");
	return Request;
}

TSharedRef<IHttpRequest> UFPCGetGoogleSheets::PostRequest(FString Subroute, FString ContentJsonString)
{
	TSharedRef<IHttpRequest> Request = RequestWithRoute(Subroute);
	Request->SetVerb("POST");
	Request->SetContentAsString(ContentJsonString);
	return Request;
}

bool UFPCGetGoogleSheets::ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid()) return false;
	if (EHttpResponseCodes::IsOk(Response->GetResponseCode())) return true;
	else
	{
		FSlateNotificationManager::Get().AddNotification(FNotificationInfo(INVTEXT("Failed to load URL")));
		UE_LOG(LogTemp, Error, TEXT("Http Response returned error code: %d"), Response->GetResponseCode());
		return false;
	}
}

void UFPCGetGoogleSheets::ProcessResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!ResponseIsValid(Response, bWasSuccessful)) return;

	OnResponseDelegate.ExecuteIfBound(Response->GetContentAsString());
}

void UFPCGetGoogleSheets::SendRequest(FString DocId)
{
	TSharedRef<IHttpRequest> Request = GetRequest(FString::Printf(TEXT("%s/export?format=csv"), *DocId));
	Request->OnProcessRequestComplete().BindUObject(this, &UFPCGetGoogleSheets::ProcessResponse);
	Request->ProcessRequest();
}
