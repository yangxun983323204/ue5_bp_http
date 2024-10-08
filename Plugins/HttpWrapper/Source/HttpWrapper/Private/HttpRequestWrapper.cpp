// Copyright (C) 2021-2023 GDI. All Rights Reserved.


#include "HttpRequestWrapper.h"
#include "HttpResponseWrapper.h"


UHttpRequestWrapper* UHttpRequestWrapper::CreateFromExternalPtr(FHttpRequestPtr InRequest)
{
    auto NewObj = NewObject<UHttpRequestWrapper>();
    NewObj->Request = InRequest;
    return NewObj;
}

void UHttpRequestWrapper::SetVerb(const FString& Verb)
{
    Request->SetVerb(Verb);
}

void UHttpRequestWrapper::SetURL(const FString& URL)
{
    Request->SetURL(URL);
}

void UHttpRequestWrapper::SetHeader(const FString& HeaderName, const FString& HeaderValue)
{
    Request->SetHeader(HeaderName, HeaderValue);
}

void UHttpRequestWrapper::AppendToHeader(const FString& HeaderName, const FString& AdditionalHeaderValue)
{
    Request->AppendToHeader(HeaderName, AdditionalHeaderValue);
}

void UHttpRequestWrapper::SetContent(TArray<uint8>& ContentPayload)
{
    Request->SetContent(ContentPayload);
}

void UHttpRequestWrapper::SetContentAsString(const FString& ContentString)
{
    Request->SetContentAsString(ContentString);
}

void UHttpRequestWrapper::SetTimeout(float InTimeoutSecs)
{
    Request->SetTimeout(InTimeoutSecs);
}

void UHttpRequestWrapper::ClearTimeout()
{
    Request->ClearTimeout();
}

bool UHttpRequestWrapper::ProcessRequest()
{
    AddToRoot();
    this->Request->OnProcessRequestComplete().BindLambda([this](FHttpRequestPtr req, FHttpResponsePtr rsp, bool success)
    {
        this->RemoveFromRoot();
        auto RspWrapper = UHttpResponseWrapper::CreateFromExternalPtr(rsp);
        this->ProcessRequestCompleteDelegate.ExecuteIfBound(this, RspWrapper, success);
    });

    this->Request->OnRequestProgress().BindLambda([this](FHttpRequestPtr req, int32 sent, int32 rec)
    {
        this->RequestProgressDelegate.ExecuteIfBound(this, sent, rec);
    });

    this->Request->OnRequestWillRetry().BindLambda([this](FHttpRequestPtr req, FHttpResponsePtr rsp, float sec)
    {
        auto RspWrapper = UHttpResponseWrapper::CreateFromExternalPtr(rsp);
        this->RequestWillRetryDelegate.ExecuteIfBound(this, RspWrapper, sec);
    });

    this->Request->OnHeaderReceived().BindLambda([this](FHttpRequestPtr req, const FString& name, const FString& val)
    {
        this->HeaderReceivedDelegate.ExecuteIfBound(this, name, val);
    });

    return Request->ProcessRequest();
}

FHttpRequestWrapperCompleteDelegate& UHttpRequestWrapper::OnProcessRequestComplete()
{
    return ProcessRequestCompleteDelegate;
}

FHttpRequestWrapperProgressDelegate& UHttpRequestWrapper::OnRequestProgress()
{
    return RequestProgressDelegate;
}

FHttpRequestWrapperWillRetryDelegate& UHttpRequestWrapper::OnRequestWillRetry()
{
    return RequestWillRetryDelegate;
}

FHttpRequestWrapperHeaderReceivedDelegate& UHttpRequestWrapper::OnHeaderReceived()
{
    return HeaderReceivedDelegate;
}

void UHttpRequestWrapper::CancelRequest()
{
    Request->CancelRequest();
}

int UHttpRequestWrapper::GetStatus()
{
    return Request->GetStatus();
}

UHttpResponseWrapper* UHttpRequestWrapper::GetResponse()
{
    return UHttpResponseWrapper::CreateFromExternalPtr(Request->GetResponse());
}
