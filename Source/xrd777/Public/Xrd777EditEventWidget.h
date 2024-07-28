// (C)ATLUS. (C)SEGA.
#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

#include "EAtlEvtEventCategoryType.h"
#include "EEventManagerEventRank.h"

#include "BfAsset.h"
#include "BmdAsset.h"
#include "LevelSequence.h"
#include "Xrd777EditUtilities.h"

struct FXrd777EditEventDataNew {
public:
	FXrd777EditEventParams* Search;
	FXrd777EditEventParams* Current;
	FString SearchLastErrorMessage;

	UBfAsset* EvtFlowscript; // BF_Scr_Event_[Cat]_[Major]_[Minor]_[Rank]
	TMap<FString, UBmdAsset*> EvtMessages; // BMD_Event_[Cat]_[Major]_[Minor]_[Rank]

	ULevel* EvtLevel; // LV_Event_[Cat]_[Major]_[Minor]_[Rank]
	ULevelSequence* EvtMainSequence; // LS_Event_[Cat]_[Major]_[Minor]_[Rank]
	ULevelSequence* EvtAudioSequence; // LS_Event_[Cat]_[Major]_[Minor]_[Rank]_Sound

	FXrd777EditEventDataNew(EAtlEvtEventCategoryType InCategory, int32 InMajorId, int32 InMinorId, EEventManagerEventRank InRank)
		//: Category(InCategory), MajorId(InMajorId), MinorId(InMinorId), Rank(InRank) {}
	{
		Search = new FXrd777EditEventParams(InCategory, InMajorId, InMinorId, InRank);
		Current = new FXrd777EditEventParams(InCategory, InMajorId, InMinorId, InRank);
	}

	FXrd777EditEventDataNew()
		//: Category(EAtlEvtEventCategoryType::MAIN), MajorId(0), MinorId(0), Rank(EEventManagerEventRank::EventRankA) {}
	{
		Search = new FXrd777EditEventParams(EAtlEvtEventCategoryType::MAIN, 0, 0, EEventManagerEventRank::EventRankA);
	}
};

DECLARE_DELEGATE(FSetEventPath)
DECLARE_DELEGATE_OneParam(FCreateDummyCharacterAsset, int32)
DECLARE_DELEGATE_OneParam(FCreateAssetsTest, const FXrd777EditEventParams&)

class SXrd777EditEventWidget : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SXrd777EditEventWidget) {}
		SLATE_ARGUMENT(FXrd777EditEventDataNew*, Data)
		SLATE_EVENT(FCreateAssetsTest, OnCreateAssetsTest)
		SLATE_EVENT(FSetEventPath, OnSetEventPath)
		SLATE_EVENT(FCreateDummyCharacterAsset, OnMakeDummyAnimTest)
	SLATE_END_ARGS()
private:
	FXrd777EditEventDataNew* Data;
	FXrd777EditUtilities Utilities;

	TArray<TSharedPtr<FString>> EventRankOptions;
	TArray<TSharedPtr<FString>> EventCategoryOptions;
	
	FSetEventPath SetEventPath;
	FCreateAssetsTest CreateAssetsTest;

	FCreateDummyCharacterAsset MakeDummyAnimTest;
public:
	void Construct(const FArguments& In);
private:
	TSharedRef<SWidget> DrawLoadedEventData();
	TSharedPtr<SBox> ContentsBox;
	TSharedRef<SWidget> DrawLoadNewEvent();
	void LoadEventDialog();
	void SearchSetCategory(EAtlEvtEventCategoryType InCategory) {
		Data->Search->Category = InCategory;
	}
	void SearchSetMajorId(int32 InMajorId) {
		Data->Search->MajorId = InMajorId;
	}
	void SearchSetMinorId(int32 InMinorId) {
		Data->Search->MinorId = InMinorId;
	}
	void SearchSetRank(EEventManagerEventRank InRank) {
		Data->Search->Rank = InRank;
	}

	int32 ApplyChunkID;

	TSharedRef<SWidget> GetObjectData(FText AssetLabel, UObject* InAsset);
public:
	FText GetCurrentEventPath();
};

#endif