// (C)ATLUS. (C)SEGA. :3
#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "BmdAsset.h"
#include "BmdAssetFactory.generated.h"

UCLASS()
class UBmdAssetFactory : public UFactory
{
public:
	GENERATED_BODY()
public:
	UBmdAssetFactory();
	UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);
};