// See https://github.com/riperjack/ue4_googledoc2datatable

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Online/HTTP/Public/Http.h"
#include "FPCGetGoogleSheet.generated.h"

DECLARE_DELEGATE_OneParam(OnResponse, FString);

UCLASS()
class FPCOMMONEDITOR_API UFPCGetGoogleSheets : public UObject
{
	GENERATED_BODY()

public:	
	OnResponse OnResponseDelegate;

	void SendRequest(FString DocId);

private:
	static const FString ApiBaseUrl;
	FHttpModule* Http;

	void ProcessResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
	void SetRequestHeaders(TSharedRef<IHttpRequest>& Request);
	bool ResponseIsValid(FHttpResponsePtr Response, bool bWasSuccessful);

	TSharedRef<IHttpRequest> GetRequest(FString Subroute);
	TSharedRef<IHttpRequest> PostRequest(FString Subroute, FString ContentJsonString);
	TSharedRef<IHttpRequest> RequestWithRoute(FString Subroute);
};