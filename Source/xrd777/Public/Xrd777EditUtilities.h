// (C)ATLUS. (C)SEGA.

#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include "EAtlEvtEventCategoryType.h"
#include "EEventManagerEventRank.h"
#include "Xrd777EditSettings.h"
#include "BfAsset.h"
#include "BmdAsset.h"
#include "LevelSequence.h"

// EVENT
struct FXrd777EditEventParams {
public:
	EAtlEvtEventCategoryType Category;
	int32 MajorId;
	int32 MinorId;
	EEventManagerEventRank Rank;

	FXrd777EditEventParams(const FXrd777EditEventParams& Other)
		: Category(Other.Category), MajorId(Other.MajorId), MinorId(Other.MinorId), Rank(Other.Rank) {}

	FXrd777EditEventParams(EAtlEvtEventCategoryType InCategory, int32 InMajorId, int32 InMinorId, EEventManagerEventRank InRank)
		: Category(InCategory), MajorId(InMajorId), MinorId(InMinorId), Rank(InRank) {}

	FXrd777EditEventParams()
		: Category(EAtlEvtEventCategoryType::MAIN), MajorId(0), MinorId(0), Rank(EEventManagerEventRank::EventRankA) {}

	FString ToString() const {
		FString PathOut = TEXT("Event_");
		switch (Category) {
		case EAtlEvtEventCategoryType::MAIN:
			PathOut += "Main";
			break;
		case EAtlEvtEventCategoryType::CMMU:
			PathOut += "Cmmu";
			break;
		case EAtlEvtEventCategoryType::QEST:
			PathOut += "Qest";
			break;
		case EAtlEvtEventCategoryType::EXTR:
			PathOut += "Extr";
			break;
		case EAtlEvtEventCategoryType::FILD:
			PathOut += "Fild";
			break;
		default:
			PathOut += "Unk";
			break;
		};
		PathOut += FString::Printf(TEXT("_%03d_%03d_"), MajorId, MinorId);
		switch (Rank) {
		case EEventManagerEventRank::EventRankA:
			PathOut += "A";
			break;
		case EEventManagerEventRank::EventRankB:
			PathOut += "B";
			break;
		case EEventManagerEventRank::EventRankC:
			PathOut += "C";
			break;
			// Default to C (TODO: confirm this in Ghidra)
			//EEventManagerEventRank::EventRankUnknown:
		default:
			PathOut += "C";
			break;
		};
		return PathOut;
	}
};

DECLARE_DELEGATE_OneParam(
	FConvertFilePath,
	FString&
)

DECLARE_DELEGATE_RetVal_TwoParams(
	FString,
	FGetFilePath,
	const FXrd777EditEventParams&,
	TOptional<FConvertFilePath>
)

class XRD777_API FXrd777EditUtilities
{
public:
	// FILE STRUCTURE
	TArray<FString> GetInternationalLanguages();
	FString GetInternationalFilePath(FString XrdPath, const FString* Culture = nullptr);
	void MakeIntoOSPath(FString& InPath, bool bIsDirectory);
	void MakeIntoOSPath(FString& InPath);
	void MakeIntoUnrealPath(FString& InPath);
	FString GetUnrealPathFromOSPath(const FString& OSPath);
	// CHARACTER
	FString GetProjectPathForCharacterId(int32 CharaId);
	FString GetCharaIdDirectoryName(int32 CharaId);
	FString GetCharaIdFileName(int32 CharaId);
	FString GetSkeletalMeshWildcard(int32 CharaId);
	FString GetAnimSequenceWildcard(int32 CharaId);
	USkeleton* GetTargetSkeleton(int32 CharaId);
	TArray<FString> GetListOfGameUnimportedSkeletalMeshes(int32 CharaId);
	TArray<FString> GetListOfGameUnimportedAnimSequences(int32 CharaId);
	// EVENT
	FString GetProjectPathForEvent(const FXrd777EditEventParams& EvtParams);
	//FString GetEventFilenameFromId(const FXrd777EditEventParams& EvtParams); // moved to FXrd777EditEventParams->ToString
	TArray<FString> GetBmdFilenamesForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb);
	TMap<FString, UBmdAsset*> GetBmdsForEvent(const FXrd777EditEventParams& EvtParams);

	template<typename TAssetType>
	TAssetType* GetAssetForEvent(const FXrd777EditEventParams& EvtParams, FGetFilePath GetFilePathCb);

	template<typename TAssetType>
	TAssetType* GetAssetForEventInner(const FXrd777EditEventParams& EvtParams, const FString& PackagePath);

	FString GetBfFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb);
	UBfAsset* GetBfAssetForEvent(const FXrd777EditEventParams& EvtParams);

	FString GetMainSequenceFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb);
	ULevelSequence* GetMainSequenceForEvent(const FXrd777EditEventParams& EvtParams);

	FString GetAudioSequenceFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb);
	ULevelSequence* GetAudioSequenceForEvent(const FXrd777EditEventParams& EvtParams);

	FString GetLevelFilenameForEvent(const FXrd777EditEventParams& EvtParams, TOptional<FConvertFilePath> ConvertFilePathCb);
	ULevel* GetLevelForEvent(const FXrd777EditEventParams& EvtParams);

	FXrd777EditUtilities() {}
};

#endif