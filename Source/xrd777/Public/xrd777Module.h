
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

#if WITH_EDITORONLY_DATA

#include "MovieSceneTracks/Public/Tracks/MovieScenePropertyTrack.h"
#include "ContentBrowser/Public/ContentBrowserMenuContexts.h"
#include "ContentBrowserData/Public/ContentBrowserDataMenuContexts.h"

#include <fstream>
#include "xrd777/ThirdParty/json/json.hpp"

#include "Engine/Classes/Components/SceneComponent.h"
#include "xrd777/Public/FldCameraBase.h"

#endif

#if WITH_EDITORONLY_DATA
DECLARE_DELEGATE_OneParam(
	FPostAssetCreated,
	UObject*
)
DECLARE_DELEGATE_TwoParams(
	FAssetCreatedPost,
	UObject*,
	const FXrd777EditEventParams&
)

struct FXrd777EditJsonObject {
public:
	FXrd777EditJsonObject(nlohmann::json InObjectData)
		: ObjectData(InObjectData)
	{
		ObjectType = FString(UTF8_TO_TCHAR(InObjectData["Type"].get<std::string>().c_str()));
		ObjectName = FString(UTF8_TO_TCHAR(InObjectData["Name"].get<std::string>().c_str()));
		std::string strOuter;
		if (InObjectData.contains("Outer")) {
			ObjectOuter = FString(UTF8_TO_TCHAR(InObjectData["Outer"].get<std::string>().c_str()));
		}
	}
	FString ObjectType;
	FString ObjectName;
	TOptional<FString> ObjectOuter;
	nlohmann::json ObjectData;

	bool ObjectContainsProperty(FString PropName) {
		std::string prop(TCHAR_TO_UTF8(*PropName));
		return ObjectData["Properties"].contains(prop);
	}
};

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
	// Utility fields
	FXrd777EditUtilities Utilities;
	FXrd777EditEventDataNew EventData;
	// DUMMY CHARACTER CREATION
	TArray<TSharedRef<FXrd777EditAssetListEntry>> ModelList;
	TSharedPtr<SXrd777EditAssetListWidget> ModelWidget;

	TArray<TSharedRef<FXrd777EditAssetListEntry>> AnimList;
	TSharedPtr<SXrd777EditAssetListWidget> AnimWidget;

	TSharedRef<SWidget> EditToolsGetExtractedAssetsNotSet();
	FString GetExtractedAssetsRootDirectory() const;

	int32 ActiveCharacterId;
	void CreateModelList(int32 CharaId);

	void TryGetEventData();

	void CreateDummyAnimTest(int32 CharacterId);
	// This will likely just be a matter of duplicating the existing asset.
	void DuplicateLevelActorsOnly(FString CurrPath, FString NewPath);

	UObject* CreateAsset(FString& AssetPath, UClass* AssetType, UFactory* FactoryInstance, TOptional<FPostAssetCreated> AssetCreatedCb);

	void CreateEventAssetsTest(const FXrd777EditEventParams& EvtParams);
	UObject* CreateEventAsset(const FXrd777EditEventParams& EvtParams, FGetFilePath GetPathCb,
		UClass* AssetType, UFactory* FactoryInstance, TOptional<FAssetCreatedPost> OnAssetCreatedCb);
	UObject* CreateEventAsset(const FXrd777EditEventParams& EvtParams, FString& ObjectPath, FString& AssetPath,
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
private:
	template<class T = UActorComponent>
	T* CreateActorComponent(AActor* Owner, UActorComponent* ExistComp);
private:
	void OnDuplicateLevelActorsOnly(UContentBrowserAssetContextMenuContext* InContext);
private:
	// Create Level data from JSON
	void OnImportLevelFromJson(UContentBrowserDataMenuContext_AddNewMenu* DataContextObject);
	TArray<TSharedRef<FXrd777EditJsonObject>> Objects;
	TMap<FString, TArray<FXrd777EditJsonObject*>> ObjectsByOuter;
	//TMap<FString, TArray<FXrd777EditJsonObject*>> ObjectsByType;
	TMap<FString, FXrd777EditJsonObject*> ObjectsByName;
	nlohmann::json RootNode;
	FXrd777EditJsonObject* GetObjectByName(const FString& Key) {
		FXrd777EditJsonObject** Val = ObjectsByName.Find(Key);
		return Val ? *Val : nullptr;
	}
	/*
	TArray<FXrd777EditJsonObject*>* GetObjectsByType(const FString& Key) {
		return ObjectsByType.Find(Key);
	}
	FXrd777EditJsonObject* GetObjectTypeSingle(const FString& Key) {
		TArray<FXrd777EditJsonObject*>* Objs = ObjectsByType.Find(Key);
		if (!Objs || Objs->Num() == 0) {
			return nullptr;
		}
		return Objs->GetData()[0];
	}
	*/
	TArray<FXrd777EditJsonObject*>* GetObjectsByOuter(const FString& Key) {
		return ObjectsByOuter.Find(Key);
	}
	FXrd777EditJsonObject* GetObjectByOuterSingle(const FString& Key) {
		TArray<FXrd777EditJsonObject*>* Objs = ObjectsByOuter.Find(Key);
		if (!Objs || Objs->Num() == 0) {
			return nullptr;
		}
		return Objs->GetData()[0];
	}
	static FXrd777EditJsonObject* GetObjectByTypeInOuter(TArray<FXrd777EditJsonObject*>*& InOuter, FString InTarget) {
		FXrd777EditJsonObject** GotFromInner = InOuter->FindByPredicate([InTarget](FXrd777EditJsonObject* InJson) { return InJson->ObjectType == InTarget; });
		if (GotFromInner) {
			return *GotFromInner;
		}
		else {
			return nullptr;
		}
	}
	static FXrd777EditJsonObject* GetObjectByNameInOuter(TArray<FXrd777EditJsonObject*>*& InOuter, FString InTarget) {
		FXrd777EditJsonObject** GotFromInner = InOuter->FindByPredicate([InTarget](FXrd777EditJsonObject* InJson) { return InJson->ObjectName == InTarget; });
		if (GotFromInner) {
			return *GotFromInner;
		}
		else {
			return nullptr;
		}
	}
	static FString GetJsonNodeNameFromObjectPath(nlohmann::json InJson);
	static FString GetJsonNodeNameFromObjectPathInner(FString InFullName);
	static FVector VectorFromJson(nlohmann::json InJson);
	static FRotator RotatorFromJson(nlohmann::json InJson);
	FXrd777EditJsonObject* GetJsonNodeFromObjectPath(nlohmann::json InJson);
	template<class TObjectType = UObject>
	TObjectType* GetObjectFromJsonSerializedPath(nlohmann::json InJson);
	void AddSceneComponentProperties(nlohmann::json InJson, USceneComponent* InComponent);
	void InitializePlayerStartParameters(FXrd777EditJsonObject* InJsonObject, APlayerStart* InPlayerStart);
	void InitializeFldCameraParameters(FXrd777EditJsonObject* InJsonObject, AFldCameraBase* InCamera);
#endif
};