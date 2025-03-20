#pragma once
#include "CoreMinimal.h"
#include "AppMultiDataAsset.h"
#include "BustupFace.h"

#if WITH_EDITORONLY_DATA
#include "AssetRegistryModule.h"
#include "IAssetRegistry.h"
#endif

#include "BustupExistDataAsset.generated.h"

UCLASS(Blueprintable)
class XRD777_API UBustupExistDataAsset : public UAppMultiDataAsset {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TMap<int32, FBustupFace> Data;
    
    UBustupExistDataAsset();
public:
    UFUNCTION(BlueprintCallable)
    bool GetBustupParameters(int32 Character, int32 Face, int32 Clothes, FString& Pose, int32& EyePartsID, int32& MouthPartsID, FVector2D& EyePos, FVector2D& MouthPos, FVector2D& BlushPos, FVector2D& SweatPos, FVector2D& Offset, int32& ClothOut);

    UFUNCTION(BlueprintCallable)
    UTexture2D* GetPoseTexture(int32 CharacterID, int32 ClothID, const FString& PoseName);

    UFUNCTION(BlueprintCallable)
    UTexture2D* GetEyeTexture(int32 CharacterID, int32 FaceID, int32 EyePartID, int32 EyePhaseID);

    UFUNCTION(BlueprintCallable)
    UTexture2D* GetMouthTexture(int32 CharacterID, int32 FaceID, int32 MouthPartID, int32 MouthPhaseID);

    UFUNCTION(BlueprintCallable)
    UTexture2D* GetBustupTexturePart(int32 CharacterID, const FString& Filename);

    FString GetCharacterType(int32 CharacterId);
};

