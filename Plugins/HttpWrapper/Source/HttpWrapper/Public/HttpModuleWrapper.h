// Copyright (C) 2021-2023 GDI. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HttpModule.h"
#include "UObject/Object.h"
#include "HttpModuleWrapper.generated.h"

class UHttpRequestWrapper;
/**
 *
 */
UCLASS(BlueprintType)
class HTTPWRAPPER_API UHttpModuleWrapper : public UObject
{
    GENERATED_BODY()
public:
    UHttpModuleWrapper();

    UFUNCTION(BlueprintCallable)
    UHttpRequestWrapper* CreateRequest();
private:
    FHttpModule* HttpModuel;
};
