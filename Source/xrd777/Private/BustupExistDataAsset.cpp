#include "BustupExistDataAsset.h"

UBustupExistDataAsset::UBustupExistDataAsset() {
}

bool UBustupExistDataAsset::GetBustupParameters(int32 Character, int32 Face, int32 Clothes, FString& Pose, int32& EyePartsID, int32& MouthPartsID, FVector2D& EyePos, FVector2D& MouthPos, FVector2D& BlushPos, FVector2D& SweatPos, FVector2D& Offset) {
	FBustupFace* TargetFace = Data.Find(Character);
	if (!TargetFace) {
		return false;
	}
	FBustupCloth* Cloth = TargetFace->Faces.Find(Face);
	if (!Cloth) {
		return false;
	}
	FBustupParts* Parts = Cloth->Clothes.Find(Clothes);
	if (!Parts) {
		return false;
	}
	Pose = Parts->Pose;
	EyePartsID = (int32)Parts->EyePartsID;
	MouthPartsID = (int32)Parts->MouthPartsID;
	EyePos = FVector2D(Parts->EyeX, Parts->EyeY);
	MouthPos = FVector2D(Parts->MouthX, Parts->MouthY);
	BlushPos = FVector2D(Parts->BlushX, Parts->BlushY);
	SweatPos = FVector2D(Parts->SweatX, Parts->SweatY);
	Offset = FVector2D(Parts->OffsetX, Parts->OffsetY);
	return true;
}

UTexture2D* UBustupExistDataAsset::GetPoseTexture(int32 CharacterID, int32 ClothID, const FString& PoseName) {
	return GetBustupTexturePart(CharacterID, FString::Printf(TEXT("T_BU_PC%04d_%s_C%03d"), CharacterID, *PoseName, ClothID));
}

UTexture2D* UBustupExistDataAsset::GetEyeTexture(int32 CharacterID, int32 FaceID, int32 EyePartID, int32 EyePhaseID) {
	return GetBustupTexturePart(CharacterID, FString::Printf(TEXT("T_BU_PC%04d_F%02d_C%03d_E%d"), CharacterID, FaceID, EyePartID, EyePhaseID));
}

UTexture2D* UBustupExistDataAsset::GetMouthTexture(int32 CharacterID, int32 FaceID, int32 MouthPartID, int32 MouthPhaseID) {
	return GetBustupTexturePart(CharacterID, FString::Printf(TEXT("T_BU_PC%04d_F%02d_C%03d_M%d"), CharacterID, FaceID, MouthPartID, MouthPhaseID));
}

UTexture2D* UBustupExistDataAsset::GetBustupTexturePart(int32 CharacterID, const FString& Filename) {
#if WITH_EDITORONLY_DATA
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FString Filepath = FString::Printf(TEXT("/Game/Xrd777/UI/Bustup/Textures/PC%04d"), CharacterID);
	Filepath = FPaths::Combine(Filepath, Filename);
	Filepath += "." + Filename;
	FAssetData PoseAsset = AssetRegistryModule.Get().GetAssetByObjectPath(FName(Filepath));
	if (PoseAsset.IsValid()) {
		return Cast<UTexture2D>(PoseAsset.GetAsset());
	}
	else {
		return nullptr;
	}
#else
	return nullptr;
#endif
}