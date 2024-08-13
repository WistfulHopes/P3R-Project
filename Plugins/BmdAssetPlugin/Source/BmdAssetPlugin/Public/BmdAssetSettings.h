// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BmdAssetSettings.generated.h"

UCLASS(config = BmdAssetPlugin)
class BMDASSETPLUGIN_API UBmdAssetSettings : public UObject
{
public:
	GENERATED_BODY()

	UBmdAssetSettings(const FObjectInitializer& obj);

	/**
	* [REQUIRES RESTART] If an Unreal BMD asset has a path to a BMD file, the asset will automatically update
	* whenever the BMD file is saved.
	*/
	UPROPERTY(Config, EditAnywhere, Category = "Auto Update")
	bool bUpdateFilesOnFileChanged;
};

#endif