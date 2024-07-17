// (C)ATLUS. (C)SEGA.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Xrd777EditSettings.generated.h"

UCLASS(config = Xrd777EditConf)
class XRD777_API UXrd777EditSettings : public UObject
{
	GENERATED_BODY()
public:
	UXrd777EditSettings(const FObjectInitializer& obj);

	UPROPERTY(Config, EditAnywhere, Category = "Assets")
	FDirectoryPath ExtractedAssetsDirectory;

	UPROPERTY(Config, EditAnywhere, Category = "Assets")
	FDirectoryPath AtlusScriptToolsDirectory;
};
