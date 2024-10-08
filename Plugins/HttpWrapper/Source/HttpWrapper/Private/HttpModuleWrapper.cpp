// Copyright (C) 2021-2023 GDI. All Rights Reserved.


#include "HttpModuleWrapper.h"

#include "HttpRequestWrapper.h"

UHttpModuleWrapper::UHttpModuleWrapper()
{
    HttpModuel = &FHttpModule::Get();
}

UHttpRequestWrapper* UHttpModuleWrapper::CreateRequest()
{
    return UHttpRequestWrapper::CreateFromExternalPtr(HttpModuel->CreateRequest());
}
