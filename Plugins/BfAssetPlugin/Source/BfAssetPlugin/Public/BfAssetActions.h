// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include "BfAsset.h"
#include "AssetTypeActions_Base.h"


class FBfAssetTypeActions : public FAssetTypeActions_Base
{
public:
	// implemented from IAssetTypeActions
	UClass* GetSupportedClass() const override;
	FText GetName() const override;
	FColor GetTypeColor() const override;
	uint32 GetCategories() override;
};

#endif