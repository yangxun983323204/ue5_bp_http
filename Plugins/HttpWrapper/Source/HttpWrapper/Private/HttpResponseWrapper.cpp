// Copyright (C) 2021-2023 GDI. All Rights Reserved.


#include "HttpResponseWrapper.h"

#include "Interfaces/IHttpResponse.h"

UHttpResponseWrapper* UHttpResponseWrapper::CreateFromExternalPtr(FHttpResponsePtr InResponse)
{
    auto NewObj = NewObject<UHttpResponseWrapper>();
    NewObj->Response = InResponse;
    return NewObj;
}

int32 UHttpResponseWrapper::GetResponseCode()
{
    return Response->GetResponseCode();
}

const TArray<uint8>& UHttpResponseWrapper::GetContent()
{
    return Response->GetContent();
}

FString UHttpResponseWrapper::GetContentAsString()
{
    return Response->GetContentAsString();
}
