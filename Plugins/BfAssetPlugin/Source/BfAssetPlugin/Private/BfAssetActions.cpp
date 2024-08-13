// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "BfAssetActions.h"

UClass* FBfAssetTypeActions::GetSupportedClass() const {
	return UBfAsset::StaticClass();
}

FText FBfAssetTypeActions::GetName() const {
	return FText::FromString("BF (Atlus Flowscript)");
}

FColor FBfAssetTypeActions::GetTypeColor() const {
	return FColor(0x85, 0xef, 0xff, 0xff);
}

uint32 FBfAssetTypeActions::GetCategories() {
	return EAssetTypeCategories::Misc;
}

#endif