// (C)ATLUS. (C)SEGA.

#if WITH_EDITORONLY_DATA


#include "Xrd777EditUtilities.h"

#include "AssetRegistryModule.h"
#include "IAssetRegistry.h"

DEFINE_LOG_CATEGORY_STATIC(LogXrd777EditUtils, Log, All);


// FILE STRUCTURE
// ================================================

FString FXrd777EditUtilities::GetInternationalFilePath(FString XrdPath, const FString* Culture) {
	FString PathOut = TEXT("/Game/");
	if (Culture != nullptr) {
		PathOut += "L10N/" + *Culture + "/";
	}
	PathOut += "Xrd777/" + XrdPath;
	return PathOut;
}

TArray<FString> FXrd777EditUtilities::GetInternationalLanguages() {
	TArray<FString> LanguagesOut;
	GConfig->GetArray(L"/Script/UnrealEd.ProjectPackagingSettings", L"CulturesToStage", LanguagesOut, GGameIni);
	LanguagesOut.Remove(TEXT("ja")); // Japanese specific assets go into the main Xrd777 folder - caller should take account of this
	return LanguagesOut;
}

void FXrd777EditUtilities::MakeIntoOSPath(FString& InPath) {
	MakeIntoOSPath(InPath, false);
}

void FXrd777EditUtilities::MakeIntoOSPath(FString& InPath, bool bIsDirectory) {
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	InPath = Settings->ExtractedAssetsDirectory.Path + InPath;
	if (!bIsDirectory) {
		InPath += FPackageName::GetAssetPackageExtension();
		//InPath += ".uasset";
	}

}
void FXrd777EditUtilities::MakeIntoUnrealPath(FString& InPath) {
	InPath += "." + FPaths::GetBaseFilename(InPath);
}

FString FXrd777EditUtilities::GetUnrealPathFromOSPath(const FString& OSPath) {
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	FString PathOut = OSPath.RightChop(Settings->ExtractedAssetsDirectory.Path.Len());
	return FPaths::ChangeExtension(PathOut, FPaths::GetBaseFilename(PathOut));
}

// CHARACTER
// ================================================

FString FXrd777EditUtilities::GetProjectPathForCharacterId(int32 CharaId) {
	FString PathOut = GetInternationalFilePath(TEXT("Characters"));
	if (CharaId < 100) {
		PathOut += "/Player/";
	}
	else if (CharaId < 1000) {
		PathOut += "/Sub/";
	}
	else {
		PathOut += "/NPC/";
	}
	PathOut += GetCharaIdDirectoryName(CharaId);
	return PathOut;
}

FString FXrd777EditUtilities::GetCharaIdDirectoryName(int32 CharaId) {
	if (CharaId < 100) {
		return TEXT("PC") + FString::Printf(TEXT("%04d"), CharaId);
	}
	else if (CharaId < 1000) {
		return TEXT("SC") + FString::Printf(TEXT("%04d"), CharaId);
	}
	else {
		return TEXT("NC") + FString::Printf(TEXT("%04d"), CharaId - (CharaId % 100));
	}
}

FString FXrd777EditUtilities::GetCharaIdFileName(int32 CharaId) {
	if (CharaId < 100) {
		return TEXT("PC") + FString::Printf(TEXT("%04d"), CharaId);
	}
	else if (CharaId < 1000) {
		return TEXT("SC") + FString::Printf(TEXT("%04d"), CharaId);
	}
	else {
		return TEXT("NC") + FString::Printf(TEXT("%04d"), CharaId);
	}
}

FString FXrd777EditUtilities::GetSkeletalMeshWildcard(int32 CharaId) {
	return TEXT("SK_") + GetCharaIdFileName(CharaId) + TEXT("_*.uasset");
}

FString FXrd777EditUtilities::GetAnimSequenceWildcard(int32 CharaId) {
	return TEXT("A_") + GetCharaIdFileName(CharaId) + TEXT("_*.uasset");
}

USkeleton* FXrd777EditUtilities::GetTargetSkeleton(int32 CharaId) {
	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FString SkelPath;
	if (CharaId == 9) { // Koromaru
		SkelPath = TEXT("/CharacterBase/Animal/Blueprints/Animation/SKEL_Animal.SKEL_Animal");
	}
	else { // Everyone else is human
		SkelPath = TEXT("/CharacterBase/Human/Blueprints/Animation/SKEL_Human.SKEL_Human");
	}
	return Cast<USkeleton>(StaticFindObject(USkeleton::StaticClass(), nullptr, *SkelPath));
	/*
	FAssetData TargetSkeleton = AssetRegistryModule.Get().GetAssetByObjectPath(*SkelPath);
	if (!TargetSkeleton.IsValid()) {
		return nullptr;
	}
	return Cast<USkeleton>(TargetSkeleton.GetAsset());
	*/
}

TArray<FString> FXrd777EditUtilities::GetListOfGameUnimportedSkeletalMeshes(int32 CharaId) {
	TArray<FString> FilenamesOut;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FString OSPathName = GetProjectPathForCharacterId(CharaId);
	MakeIntoOSPath(OSPathName, true);
	IFileManager::Get().FindFilesRecursive(FilenamesOut, *OSPathName, *GetSkeletalMeshWildcard(CharaId), true, false);
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	TArray<FString> UnimportedFilenamesOut;
	for (const FString& SKFile : FilenamesOut) {
		FString ObjectPath = GetUnrealPathFromOSPath(SKFile);
		FAssetData SKAsset = AssetRegistryModule.Get().GetAssetByObjectPath(*ObjectPath);
		if (!SKAsset.IsValid()) {
			UnimportedFilenamesOut.Add(ObjectPath);
		}
	}
	return UnimportedFilenamesOut;
}

TArray<FString> FXrd777EditUtilities::GetListOfGameUnimportedAnimSequences(int32 CharaId) {
	TArray<FString> FilenamesOut;
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FString OSPathName = GetProjectPathForCharacterId(CharaId);
	MakeIntoOSPath(OSPathName, true);
	IFileManager::Get().FindFilesRecursive(FilenamesOut, *OSPathName, *GetAnimSequenceWildcard(CharaId), true, false);
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	TArray<FString> UnimportedFilenamesOut;
	for (const FString& AFile : FilenamesOut) {
		FString ObjectPath = GetUnrealPathFromOSPath(AFile);
		FAssetData AAsset = AssetRegistryModule.Get().GetAssetByObjectPath(*ObjectPath);
		if (!AAsset.IsValid()) {
			UnimportedFilenamesOut.Add(ObjectPath);
		}
	}
	return UnimportedFilenamesOut;
}

// EVENT
// ================================================

FString FXrd777EditUtilities::GetProjectPathForEvent(const FXrd777EditEventParams& EvtParams) {
	//FString PathOut = TEXT("/Game/Xrd777/Events/Cinema/");
	FString PathOut = GetInternationalFilePath(TEXT("Events/Cinema/"));
	PathOut += EvtParams.ToString();
	return PathOut;
}

template<typename TAssetType>
TAssetType* FXrd777EditUtilities::GetAssetForEvent(const FXrd777EditEventParams& EvtParams, FGetFilePath GetFilePathCb) {
	FString PackagePath = GetFilePathCb.Execute(EvtParams, FConvertFilePath::CreateRaw(this, &FXrd777EditUtilities::MakeIntoUnrealPath));
	return GetAssetForEventInner<TAssetType>(EvtParams, PackagePath);
}

template<typename TAssetType>
TAssetType* FXrd777EditUtilities::GetAssetForEventInner(const FXrd777EditEventParams& EvtParams, const FString& PackagePath) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	FAssetData TargetAssetData = AssetRegistry.GetAssetByObjectPath(*PackagePath);
	if (!TargetAssetData.IsValid()) {
		UE_LOG(LogXrd777EditUtils, Display, TEXT("No asset exists at %s"), *PackagePath);
		return nullptr;
	}
	UE_LOG(LogXrd777EditUtils, Display, TEXT("Got asset at %s"), *PackagePath);
	TAssetType* AssetOut = Cast<TAssetType>(TargetAssetData.GetAsset());
	return AssetOut;
}

// BMD_Event_[Cat]_[Major]_[Minor]_[Rank]

TArray<FString> FXrd777EditUtilities::GetBmdFilenamesForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb) {
	TArray<FString> FilenamesOut;
	TArray<FString> Languages = GetInternationalLanguages();
	// japanese
	FString JpBmdPath = GetInternationalFilePath(FString::Printf(TEXT("Events/Cinema/%s/BMD_%s")
		, *EvtParams.ToString(), *EvtParams.ToString(), *EvtParams.ToString()));
	if (ConvertFilePathCb.IsSet()) {
		ConvertFilePathCb.GetValue().Execute(JpBmdPath);
	}
	FilenamesOut.Add(JpBmdPath);
	// other languages
	for (const FString& Language : Languages) {
		FString IntBmdPath = GetInternationalFilePath(FString::Printf(TEXT("Events/Cinema/%s/BMD_%s")
			, *EvtParams.ToString(), *EvtParams.ToString(), *EvtParams.ToString()), &Language);
		if (ConvertFilePathCb.IsSet()) {
			ConvertFilePathCb.GetValue().Execute(IntBmdPath);
		}
		FilenamesOut.Add(IntBmdPath);
	}
	return FilenamesOut;
}

TMap<FString, UBmdAsset*> FXrd777EditUtilities::GetBmdsForEvent(const FXrd777EditEventParams& EvtParams) {
	TMap<FString, UBmdAsset*> BmdMap;
	TArray<FString> BmdFilenames = GetBmdFilenamesForEvent(EvtParams, FConvertFilePath::CreateRaw(this, &FXrd777EditUtilities::MakeIntoUnrealPath));
	for (const FString& BmdFilename : BmdFilenames) {
		UBmdAsset* CurrBmd = GetAssetForEventInner<UBmdAsset>(EvtParams, BmdFilename);
		BmdMap.Emplace(BmdFilename, CurrBmd);
	}
	return BmdMap;
}

// BF_Scr_Event_[Cat]_[Major]_[Minor]_[Rank]

FString FXrd777EditUtilities::GetBfFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb) {
	FString PathNormal = GetInternationalFilePath(FString::Printf(TEXT("Events/Cinema/%s/Script/BF_Scr_%s")
		, *EvtParams.ToString(), *EvtParams.ToString()));
	if (ConvertFilePathCb.IsSet()) {
		ConvertFilePathCb.GetValue().Execute(PathNormal);
	}
	return PathNormal;
}

UBfAsset* FXrd777EditUtilities::GetBfAssetForEvent(const FXrd777EditEventParams& EvtParams) {
	return GetAssetForEvent<UBfAsset>(EvtParams, FGetFilePath::CreateRaw(this, &FXrd777EditUtilities::GetBfFilenameForEvent));
}

// LV_Event_[Cat]_[Major]_[Minor]_[Rank]

FString FXrd777EditUtilities::GetLevelFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb) {
	FString PathNormal = GetInternationalFilePath(FString::Printf(TEXT("Events/Cinema/%s/LV_%s")
		, *EvtParams.ToString(), *EvtParams.ToString()));
	if (ConvertFilePathCb.IsSet()) {
		ConvertFilePathCb.GetValue().Execute(PathNormal);
	}
	return PathNormal;
}

ULevel* FXrd777EditUtilities::GetLevelForEvent(const FXrd777EditEventParams& EvtParams) {
	return GetAssetForEvent<ULevel>(EvtParams, FGetFilePath::CreateRaw(this, &FXrd777EditUtilities::GetLevelFilenameForEvent));
}


// LS_Event_[Cat]_[Major]_[Minor]_[Rank]

FString FXrd777EditUtilities::GetMainSequenceFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb) {
	FString PathNormal = GetInternationalFilePath(FString::Printf(TEXT("Events/Cinema/%s/LS_%s")
		, *EvtParams.ToString(), *EvtParams.ToString()));
	if (ConvertFilePathCb.IsSet()) {
		ConvertFilePathCb.GetValue().Execute(PathNormal);
	}
	return PathNormal;
}

ULevelSequence* FXrd777EditUtilities::GetMainSequenceForEvent(const FXrd777EditEventParams& EvtParams) {
	return GetAssetForEvent<ULevelSequence>(EvtParams, FGetFilePath::CreateRaw(this, &FXrd777EditUtilities::GetMainSequenceFilenameForEvent));
}

// LS_Event_[Cat]_[Major]_[Minor]_[Rank]_Sound

FString FXrd777EditUtilities::GetAudioSequenceFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb) {
	FString PathNormal = GetInternationalFilePath(FString::Printf(TEXT("Events/Cinema/%s/LS_%s_Sound")
		, *EvtParams.ToString(), *EvtParams.ToString()));
	if (ConvertFilePathCb.IsSet()) {
		ConvertFilePathCb.GetValue().Execute(PathNormal);
	}
	return PathNormal;
}

ULevelSequence* FXrd777EditUtilities::GetAudioSequenceForEvent(const FXrd777EditEventParams& EvtParams) {
	return GetAssetForEvent<ULevelSequence>(EvtParams, FGetFilePath::CreateRaw(this, &FXrd777EditUtilities::GetAudioSequenceFilenameForEvent));
}

#endif