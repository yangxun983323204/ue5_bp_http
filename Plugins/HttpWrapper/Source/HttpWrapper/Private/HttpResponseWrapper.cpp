// Copyright (C) 2021-2023 GDI. All Rights Reserved.


#include "HttpResponseWrapper.h"

#include "Interfaces/IHttpResponse.h"

UHttpResponseWrapper* UHttpResponseWrapper::CreateFromExternalPtr(FHttpResponsePtr InResponse)
{
    auto NewObj = NewObject<UHttpResponseWrapper>();
    NewObj->Response = InResponse;
    NewObj->SetDebugInfo();
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

void UHttpResponseWrapper::SetDebugInfo()
{
    if(Response.IsValid())
    {
#if UE_EDITOR
        Debug_ResponseCode = Response->GetResponseCode();
        Debug_ContentAsString = Response->GetContentAsString();
        if(Debug_ResponseCode != 200)
        {
            auto ErrorMsg = FString::Printf(TEXT("%d,%s,%s"), Debug_ResponseCode, *Response->GetURL(), *Debug_ContentAsString);
            UE_LOG(LogTemp, Error, TEXT("%s"), *ErrorMsg)
            if(GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, *ErrorMsg);
        }
#endif
    }
}
