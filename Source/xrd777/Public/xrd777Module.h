
// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

#include "EEventManagerEventRank.h"
#include "EAtlEvtEventCategoryType.h"
#include "Xrd777EditAssetListWidget.h"
#include "Xrd777EditEventWidget.h"
#include "Xrd777EditUtilities.h"

#include "AtlEvtEventManager.h"
#include "CineCameraActor.h"
#include "AtlEvtLevelSequenceActor.h"

#include "MovieSceneTracks/Public/Tracks/MovieScenePropertyTrack.h"

#if WITH_EDITORONLY_DATA
DECLARE_DELEGATE_TwoParams(
	FAssetCreatedPost,
	UObject*,
	const FXrd777EditEventParams&
)
#endif

class XRD777_API FXrd777RiriModule 
	: public IModuleInterface {
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual bool IsGameModule() const override {
		return true;
	}

private:
#if WITH_EDITORONLY_DATA
	FDelegateHandle EvtAdxSoundFadeTrackEditorHandle;
	FDelegateHandle EvtAdxSoundManageTrackEditorHandle;
	FDelegateHandle EvtAdxSoundTrackEditorHandle;
	FDelegateHandle EvtCharaAnimTrackEditorHandle;
	FDelegateHandle EvtCharaHandwritingTrackEditorHandle;
	FDelegateHandle EvtCharaOperationControllerTrackEditorHandle;
	FDelegateHandle EvtCharaPackAnimTrackEditorHandle;
	FDelegateHandle EvtCharaPackFaceAnimTrackEditorHandle;
	FDelegateHandle EvtCharaPropAttachTrackEditorHandle;
	FDelegateHandle EvtDialogueOptionsTrackEditorHandle;
	FDelegateHandle EvtDialogueTrackEditorHandle;
	FDelegateHandle EvtFadeScreenTrackEditorHandle;
	FDelegateHandle EvtFieldAnimTrackEditorHandle;
	FDelegateHandle EvtNessageSubtitleTrackEditorHandle;
	FDelegateHandle EvtMovieTrackEditorHandle;
	FDelegateHandle EvtScriptTrackEditorHandle;
	FDelegateHandle EvtSeqControlTrackEditorHandle;
	FDelegateHandle EvtSeqTimeJumpControlTrackEditorHandle;

	void RegisterMenus();
	TSharedRef<SWidget> CreateToolbarDropdown();
	TSharedRef<SWidget> EditToolsCreateCharacterData();

public:
	TArray<TSharedRef<FXrd777EditAssetListEntry>> ModelList;
	TSharedPtr<SXrd777EditAssetListWidget> ModelWidget;

	TArray<TSharedRef<FXrd777EditAssetListEntry>> AnimList;
	TSharedPtr<SXrd777EditAssetListWidget> AnimWidget;

	TSharedRef<SWidget> EditToolsGetExtractedAssetsNotSet();
	FString GetExtractedAssetsRootDirectory() const;

	int32 ActiveCharacterId;
	void CreateModelList(int32 CharaId);

	void TryGetEventData();
	FXrd777EditUtilities Utilities;
	FXrd777EditEventDataNew EventData;

	void CreateEventAssetsTest(const FXrd777EditEventParams& EvtParams);
	UObject* CreateAsset(const FXrd777EditEventParams& EvtParams, FGetFilePath GetPathCb,
		UClass* AssetType, UFactory* FactoryInstance, TOptional<FAssetCreatedPost> OnAssetCreatedCb);
	UObject* CreateAsset(const FXrd777EditEventParams& EvtParams, FString& ObjectPath, FString& AssetPath,
		UClass* AssetType, UFactory* FactoryInstance, TOptional<FAssetCreatedPost> OnAssetCreatedCb);
	void PostCreateLevel(UObject* WorldObj, const FXrd777EditEventParams& EvtParams);
	void PostCreateLevelSequence(UObject* SeqObj, const FXrd777EditEventParams& EvtParams);
	void MainSequenceAddObjectBindings(ULevelSequence* MainSeq, UWorld* World);
	void AddMainSequenceToWorld(UWorld* World, ULevelSequence* MainSeq, const FXrd777EditEventParams& EvtParams);
	void AddPropertyBinding(FMovieSceneBinding* TargetBinding, UMovieScene* Movie, UClass* TrackType, const FString& Path);
private:
	// EVENT CREATION
	AAtlEvtEventManager* AtlusEventManager;
	ACineCameraActor* CineCameraActor;
	ULevelSequence* AudioSequence;
	AAtlEvtLevelSequenceActor* LevelSequenceActor;
	bool bDoesWorldAlreadyExist;
#endif
};