// Copyright (C) 2021-2023 GDI. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/Object.h"
#include "HttpRequestWrapper.generated.h"

class UHttpResponseWrapper;

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHttpRequestWrapperCompleteDelegate, UHttpRequestWrapper* ,Request, UHttpResponseWrapper*, Response, bool, bConnectedSuccessfully);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHttpRequestWrapperHeaderReceivedDelegate, UHttpRequestWrapper*, Request, const FString&, HeaderName, const FString&, NewHeaderValue);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHttpRequestWrapperProgressDelegate, UHttpRequestWrapper*, Request, int32, BytesSent, int32, BytesReceived);

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FHttpRequestWrapperWillRetryDelegate, UHttpRequestWrapper*, Request, UHttpResponseWrapper*, Response, float ,SecondsToRetry);

/**
 *
 */
UCLASS(BlueprintType)
class HTTPWRAPPER_API UHttpRequestWrapper : public UObject
{
    GENERATED_BODY()
public:
    static UHttpRequestWrapper* CreateFromExternalPtr(FHttpRequestPtr InRequest);

    UFUNCTION(BlueprintCallable)
    void SetVerb(const FString& Verb);

    UFUNCTION(BlueprintCallable)
    void SetURL(const FString& URL);

    UFUNCTION(BlueprintCallable)
    void SetHeader(const FString& HeaderName, const FString& HeaderValue);

    UFUNCTION(BlueprintCallable)
    void AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue);

    UFUNCTION(BlueprintCallable)
    void SetContent(TArray<uint8>& ContentPayload);

    UFUNCTION(BlueprintCallable)
    void SetContentAsString(const FString& ContentString);

    UFUNCTION(BlueprintCallable)
    void SetTimeout(float InTimeoutSecs);

    UFUNCTION(BlueprintCallable)
    void ClearTimeout();

    /** 调用此方法会使对象本身固定，不被垃圾回收，直到OnProcessRequestComplete触发时移除固定。OnProcessRequestComplete无论成功与否总是会触发 */
    UFUNCTION(BlueprintCallable)
    bool ProcessRequest();

    UFUNCTION(BlueprintCallable)
    FHttpRequestWrapperCompleteDelegate& OnProcessRequestComplete();

    UFUNCTION(BlueprintCallable)
    FHttpRequestWrapperProgressDelegate& OnRequestProgress();

    UFUNCTION(BlueprintCallable)
    FHttpRequestWrapperWillRetryDelegate& OnRequestWillRetry();

    UFUNCTION(BlueprintCallable)
    FHttpRequestWrapperHeaderReceivedDelegate& OnHeaderReceived();

    UFUNCTION(BlueprintCallable)
    void CancelRequest();

    /** EHttpRequestStatus::Type GetStatus() */
    UFUNCTION(BlueprintCallable)
    int GetStatus();

    UFUNCTION(BlueprintCallable)
    UHttpResponseWrapper* GetResponse();

private:
    FHttpRequestPtr Request;

    FHttpRequestWrapperCompleteDelegate ProcessRequestCompleteDelegate;
    FHttpRequestWrapperProgressDelegate RequestProgressDelegate;
    FHttpRequestWrapperWillRetryDelegate RequestWillRetryDelegate;
    FHttpRequestWrapperHeaderReceivedDelegate HeaderReceivedDelegate;
};
