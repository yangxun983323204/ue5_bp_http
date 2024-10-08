// Copyright (C) 2021-2023 GDI. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "UObject/Object.h"
#include "HttpResponseWrapper.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class HTTPWRAPPER_API UHttpResponseWrapper : public UObject
{
    GENERATED_BODY()
public:
    static UHttpResponseWrapper* CreateFromExternalPtr(FHttpResponsePtr InResponse);

    UFUNCTION(BlueprintCallable, BlueprintPure)
    int32 GetResponseCode();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    const TArray<uint8>& GetContent();

    UFUNCTION(BlueprintCallable, BlueprintPure)
    FString GetContentAsString();

private:
    FHttpResponsePtr Response;
};
