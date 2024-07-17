// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "xrd777Module.h"
#include "Modules/ModuleManager.h"
#if WITH_EDITORONLY_DATA
#include "Logging/LogMacros.h"
#include <ISequencerModule.h>
#include <EvtAdxSoundFadeTrackEditor.h>
#include <EvtAdxSoundManageTrackEditor.h>
#include <EvtAdxSoundTrackEditor.h>
#include <EvtCharaAnimTrackEditor.h>
#include <EvtCharaHandwritingTrackEditor.h>
#include <EvtCharaOpControlTrackEditor.h>
#include <EvtCharaPackAnimTrackEditor.h>
#include <EvtCharaPackFaceAnimTrackEditor.h>
#include <EvtCharaPropAttachTrackEditor.h>
#include <EvtDialogueOptionsTrackEditor.h>
#include <EvtDialogueTrackEditor.h>
#include <EvtFadeScreenTrackEditor.h>
#include <EvtFieldAnimTrackEditor.h>
#include <EvtMessageSubtitleTrackEditor.h>
#include <EvtMovieTrackEditor.h>
#include <EvtScriptTrackEditor.h>
#include <EvtSeqControlTrackEditor.h>
#include <EvtSeqTimeJumpControlTrackEditor.h>

#include <ISettingsModule.h>
#include <DesktopPlatformModule.h>
#include "ToolMenus.h"
#include "Widgets/Input/SSpinBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/SOverlay.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Views/SListView.h"
#include "Widgets/Views/STableRow.h"
#include "Widgets/Views/STableViewBase.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Layout/SSeparator.h"
#include "Widgets/Layout/SScrollBorder.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/STextComboBox.h"
#include "PropertyEditor/Public/PropertyCustomizationHelpers.h"

#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "HAL/FileManagerGeneric.h"

#include "AssetToolsModule.h"
#include "ContentBrowserModule.h"
#include "AssetRegistryModule.h"
#include "IAssetRegistry.h"
//#include "UnrealEd/Classes/Factories/AnimSequenceFactory.h"
#include "IContentBrowserSingleton.h"
#include "ISettingsModule.h"
#include "Xrd777EditSettings.h"
#include "CoreUObject/Public/UObject/UObjectGlobals.h"
#include "UObject/ReflectedTypeAccessors.h"

#include "UnrealEd/Classes/Factories/LevelFactory.h"
#include "UnrealEd/Classes/Factories/WorldFactory.h"

#include "MovieSceneToolsProjectSettings.h"
//#include "LevelSequenceEditor"
#include "MovieScene/Public/Tracks/MovieSceneSubTrack.h"
#include "MovieSceneTracks/Public/Tracks/MovieSceneCameraCutTrack.h"
#include "MovieSceneTracks/Public/Tracks/MovieScene3DTransformTrack.h"
#include "MovieSceneTracks/Public/Tracks/MovieSceneFloatTrack.h"
#include "MovieSceneTracks/Public/Sections/MovieSceneFloatSection.h"
#include "CineCameraComponent.h"
//#include "PropertyEditor/Private/PropertyEditorHelpers.h"
#include "PropertyPath.h"

//#include "Xrd777EditAssetListWidget.h"

#define LOCTEXT_NAMESPACE "FXrd777Module"

DEFINE_LOG_CATEGORY_STATIC(LogRiriModule, Log, All);
#endif

void FXrd777RiriModule::StartupModule() {
#if WITH_EDITORONLY_DATA
	UE_LOG(LogRiriModule, Display, TEXT("haiiii!!"));
	// Custom event sequences
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");

	EvtAdxSoundFadeTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtAdxSoundFadeTrackEditor::CreateTrackEditor));
	EvtAdxSoundManageTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtAdxSoundManageTrackEditor::CreateTrackEditor));
	EvtAdxSoundTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtAdxSoundTrackEditor::CreateTrackEditor));
	EvtCharaAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaAnimTrackEditor::CreateTrackEditor));
	EvtCharaHandwritingTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaHandwritingTrackEditor::CreateTrackEditor));
	EvtCharaOperationControllerTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaOpControlTrackEditor::CreateTrackEditor));
	EvtCharaPackAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaPackAnimTrackEditor::CreateTrackEditor));
	EvtCharaPackFaceAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaPackFaceAnimTrackEditor::CreateTrackEditor));
	EvtCharaPropAttachTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtCharaPropAttachTrackEditor::CreateTrackEditor));
	EvtDialogueOptionsTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtDialogueOptionsTrackEditor::CreateTrackEditor));
	EvtDialogueTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtDialogueTrackEditor::CreateTrackEditor));
	EvtFadeScreenTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtFadeScreenTrackEditor::CreateTrackEditor));
	EvtFieldAnimTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtFieldAnimTrackEditor::CreateTrackEditor));
	EvtNessageSubtitleTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtMessageSubtitleTrackEditor::CreateTrackEditor));
	EvtMovieTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtMovieTrackEditor::CreateTrackEditor));
	EvtScriptTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtScriptTrackEditor::CreateTrackEditor));
	EvtSeqControlTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtSeqControlTrackEditor::CreateTrackEditor));
	EvtSeqTimeJumpControlTrackEditorHandle = SequencerModule.RegisterTrackEditor(FOnCreateTrackEditor::CreateStatic(&FEvtSeqTimeJumpControlTrackEditor::CreateTrackEditor));
	// Xrd777 Edit Tools
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FXrd777RiriModule::RegisterMenus));

	// Xrd777 Edit Settings
	ISettingsModule& SettingsModule = FModuleManager::Get().LoadModuleChecked<ISettingsModule>("Settings");
	SettingsModule.RegisterSettings("Project", "Project", "Xrd777EditSettings",
		LOCTEXT("Xrd777EditPreferenceName", "Xrd777 Edit"),
		LOCTEXT("Xrd777EditPreferenceDesc", "Settings for Xrd777 Edit"),
		GetMutableDefault<UXrd777EditSettings>())
	;

	// Hook on Asset Loaded
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//AssetRegistryModule.Get().OnAssetAdded().AddRaw(this, &FXrd777RiriModule::OnAddedAssetToRegistry);

#endif
}
#if WITH_EDITORONLY_DATA

void FXrd777RiriModule::RegisterMenus() {
	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* LvlEditorToolMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
	FToolMenuSection& LvlEditToolSection = LvlEditorToolMenu->FindOrAddSection("XRD777Edit");
	LvlEditToolSection.AddEntry(FToolMenuEntry::InitComboButton(
		TEXT("XRD777EditTools"),
		FUIAction(
			FExecuteAction(),
			FCanExecuteAction(),
			FGetActionCheckState()
		),
		FOnGetContent::CreateRaw(this, &FXrd777RiriModule::CreateToolbarDropdown),
		LOCTEXT("Xrd777EditDisplayName", "XRD777 Edit"),
		LOCTEXT("Xrd777EditTooltip", "Tooltip for XRD777 Edit")
	));
}

void FXrd777RiriModule::CreateModelList(int32 CharaId) {
	FString ExtractBasePath = GetExtractedAssetsRootDirectory();
	FString ExtractCharPath = FPaths::Combine(ExtractBasePath, Utilities.GetProjectPathForCharacterId(CharaId));

	//ModelList.Empty();
	//AnimList.Empty();

	/*
	if (!IFileManager::Get().DirectoryExists(*ExtractCharPath)) {
		UE_LOG(LogRiriModule, Display, TEXT("[LookForAnimationBlueprints] Missing directory error: %s"), *ExtractCharPath);
		return;
	}
	*/

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FString Wildcard = TEXT("SK_") + Utilities.GetCharaIdFileName(CharaId) + TEXT("_*.uasset"); // Skeletal meshes only
	ModelWidget.Get()->UpdateAssetList(ExtractBasePath, ExtractCharPath, Wildcard, AssetRegistry);
	FString AnimWildcard = TEXT("A_") + Utilities.GetCharaIdFileName(CharaId) + TEXT("_*.uasset"); // Anim Sequences only
	AnimWidget.Get()->UpdateAssetList(ExtractBasePath, ExtractCharPath, AnimWildcard, AssetRegistry);
}

void FXrd777RiriModule::TryGetEventData() {
	FString ExtractBasePath = GetExtractedAssetsRootDirectory();
	FString TargetEventPath = Utilities.GetProjectPathForEvent(*EventData.Search);
	FString TargetEventOSPath = FPaths::Combine(ExtractBasePath, TargetEventPath);

	if (!IFileManager::Get().DirectoryExists(*TargetEventOSPath)) {
		EventData.SearchLastErrorMessage = FString::Printf(TEXT("Missing directory error: %s"), *TargetEventOSPath);
		UE_LOG(LogRiriModule, Display, TEXT("%s"), *EventData.SearchLastErrorMessage);
		// Clear event data!
		EventData.Current = nullptr;
		EventData.EvtFlowscript = nullptr;
		EventData.EvtMessages.Empty();
		EventData.EvtLevel = nullptr;
		EventData.EvtMainSequence = nullptr;
		EventData.EvtAudioSequence = nullptr;
		return;
	}
	EventData.Current = new FXrd777EditEventParams(*EventData.Search);
	FString Wildcard = TEXT("_*.uasset"); // All assets
	// Consider an asset valid if it
	// - Has an existing entry in the extracted assets list
	// - Or has a folder for it inside the project files
	EventData.EvtFlowscript = Utilities.GetBfAssetForEvent(*EventData.Current);
	EventData.EvtMessages = Utilities.GetBmdsForEvent(*EventData.Current);
	EventData.EvtLevel = Utilities.GetLevelForEvent(*EventData.Current);
	EventData.EvtMainSequence = Utilities.GetMainSequenceForEvent(*EventData.Current);
	EventData.EvtAudioSequence = Utilities.GetAudioSequenceForEvent(*EventData.Current);
}

TSharedRef<SWidget> FXrd777RiriModule::EditToolsCreateCharacterData() {
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text(LOCTEXT("Xrd777EditCharacterAnimSelectedLabel", "Selected Character ID"))
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.Padding(FMargin(10, 0, 0, 0))
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SSpinBox<int32>)
						.MinValue(0)
						.MaxValue(9999)
						.Delta(1)
						.ToolTipText(LOCTEXT("Xrd777EditCharacterAnimSelectedTooltip", "Select a Character ID to do operations on"))
						.MinDesiredWidth(150.0f)
						.Value_Lambda([this]() {
							return ActiveCharacterId;
						})
						.OnValueChanged_Lambda([this](int32 NewValue) {
							ActiveCharacterId = NewValue;
							CreateModelList(ActiveCharacterId);
						})
				]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text_Lambda([this]() {
							return FText::FromString(FString::Printf(TEXT("Character Filepath: %s"), *Utilities.GetProjectPathForCharacterId(ActiveCharacterId)));
						})
				]
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0, 10))
		.AutoHeight()
		[
			SNew(SSeparator)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(ModelWidget, SXrd777EditAssetListWidget)
				.InList(&ModelList)
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0, 10))
		.AutoHeight()
		[
			SNew(SSeparator)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(AnimWidget, SXrd777EditAssetListWidget)
				.InList(&AnimList)
		]
		;
}

FString FXrd777RiriModule::GetExtractedAssetsRootDirectory() const {
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	return Settings->ExtractedAssetsDirectory.Path;
}

TSharedRef<SWidget> FXrd777RiriModule::EditToolsGetExtractedAssetsNotSet() {
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.MaxWidth(150.0f)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.Padding(FMargin(5, 5, 5, 5))
				[
					SNew(STextBlock)
						.Text(LOCTEXT("Xrd777EditAssetDirectoryMissing", "Please set the extracted assets directory in Editor Settings. (In Project Settings > Xrd777 Edit)"))
						.AutoWrapText(true)
				]
		];
}

UObject* FXrd777RiriModule::CreateAsset(
	const FXrd777EditEventParams& EvtParams, FGetFilePath GetPathCb, UClass* AssetType, 
	UFactory* FactoryInstance, TOptional<FAssetCreatedPost> OnAssetCreatedCb) {
	// Check if the given asset already exists
	TOptional<FConvertFilePath> BlankCb;
	FString ObjectPath = GetPathCb.Execute(EvtParams, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath));
	FString AssetPath = GetPathCb.Execute(EvtParams, BlankCb);
	return CreateAsset(EvtParams, ObjectPath, AssetPath, AssetType, FactoryInstance, OnAssetCreatedCb);
}

UObject* FXrd777RiriModule::CreateAsset(
	const FXrd777EditEventParams& EvtParams, FString& ObjectPath, FString& AssetPath, 
	UClass* AssetType, UFactory* FactoryInstance, TOptional<FAssetCreatedPost> OnAssetCreatedCb) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(*ObjectPath);
	if (ExistingAsset.IsValid()) {
		UE_LOG(LogRiriModule, Display, TEXT("Asset at %s already exists"), *ObjectPath);
		return ExistingAsset.GetAsset();
	}
	UE_LOG(LogRiriModule, Display, TEXT("Creating asset at %s"), *ObjectPath);

	FString AssetName = FPaths::GetBaseFilename(AssetPath);
	FString PackagePath = FPaths::GetPath(AssetPath);

	UPackage* Package = CreatePackage(*AssetPath);

	/*
	UObject* NewAsset = AssetToolsModule.Get().CreateAsset(AssetName, PackagePath, AssetType, FactoryInstance);
	*/
	UObject* NewAsset;
	EObjectFlags NewAssetFlags = RF_Public | RF_Standalone | RF_Transactional;
	if (FactoryInstance != nullptr) {
		NewAsset = FactoryInstance->FactoryCreateNew(AssetType, Package, FName(*AssetName), NewAssetFlags, nullptr, GWarn, NAME_None);
	}
	else {
		NewAsset = NewObject<UObject>(Package, AssetType, FName(*AssetName), NewAssetFlags);
	}
	NewAsset->MarkPackageDirty();

	if (OnAssetCreatedCb.IsSet()) {
		OnAssetCreatedCb.GetValue().Execute(NewAsset, EvtParams);
	}
	UPackage::Save(Package, NewAsset, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(AssetPath, FPackageName::GetAssetPackageExtension()));

	AssetRegistryModule.Get().AssetCreated(NewAsset);
	TArray<UObject*> ContentBrowserAssetSyncLocal;
	ContentBrowserAssetSyncLocal.Add(NewAsset);
	ContentBrowserModule.Get().SyncBrowserToAssets(ContentBrowserAssetSyncLocal);
	return NewAsset;
}

void FXrd777RiriModule::PostCreateLevel(UObject* WorldObj, const FXrd777EditEventParams& EvtParams) {
	UWorld* World = CastChecked<UWorld>(WorldObj);
	// ATLUS Event Manager
	UBlueprint* AtlEvtManagerBf = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), nullptr, TEXT("/Game/Xrd777/Blueprints/Events/BP_AtlEvtEventManager.BP_AtlEvtEventManager")));
	// do stuff to event manager if we need to
	AtlusEventManager = Cast<AAtlEvtEventManager>(World->SpawnActor(AtlEvtManagerBf->GeneratedClass));
	// Cine Camera Actor
	CineCameraActor = Cast<ACineCameraActor>(World->SpawnActor(ACineCameraActor::StaticClass()));
	// define defaults for camera (Event_Cmmu_002_100_C)
	CineCameraActor->SetActorTransform(FTransform(FVector(-57.0f, 60.0f, 150.0f)));
	bDoesWorldAlreadyExist = false;
}

void FXrd777RiriModule::PostCreateLevelSequence(UObject* SeqObj, const FXrd777EditEventParams& EvtParams) {
	ULevelSequence* LevelSequence = CastChecked<ULevelSequence>(SeqObj);
	// LevelSequenceFactoryNew
	LevelSequence->Initialize();
	const UMovieSceneToolsProjectSettings* ProjectSettings = GetDefault<UMovieSceneToolsProjectSettings>();
	FFrameRate TickResolution = LevelSequence->GetMovieScene()->GetTickResolution();
	LevelSequence->GetMovieScene()->SetPlaybackRange((ProjectSettings->DefaultStartTime * TickResolution).FloorToFrame(), (ProjectSettings->DefaultDuration * TickResolution).FloorToFrame().Value);
}

void FXrd777RiriModule::AddPropertyBinding(FMovieSceneBinding* TargetBinding, UMovieScene* Movie, UClass* TrackType, const FString& Path) {
	int32 IndexOfInnermostStruct;
	Path.FindLastChar(L'.', IndexOfInnermostStruct);
	FName PropName;
	if (IndexOfInnermostStruct != INDEX_NONE) {
		PropName = FName(*Path.Right(IndexOfInnermostStruct), EFindName::FNAME_Find);
	}
	else {
		PropName = FName(*Path, EFindName::FNAME_Find);
	}
	UMovieScenePropertyTrack* NewPropTrack = NewObject<UMovieScenePropertyTrack>(Movie, TrackType, NAME_None, RF_Transactional);
	UMovieSceneSection* NewPropSection = NewPropTrack->CreateNewSection();
	NewPropTrack->AddSection(*NewPropSection);
	NewPropTrack->SetPropertyNameAndPath(PropName, Path);
	TargetBinding->AddTrack(*NewPropTrack);
}

void FXrd777RiriModule::MainSequenceAddObjectBindings(ULevelSequence* MainSeq, UWorld* World) {
	if (AtlusEventManager == nullptr || CineCameraActor == nullptr) {
		UE_LOG(LogRiriModule, Error, TEXT("Some actors are missing from the sequence's level. Bug!"));
		return;
	}
	UMovieScene* SeqMovie = MainSeq->GetMovieScene();
	
	if (!MainSeq->FindPossessableObjectId(*AtlusEventManager, nullptr).IsValid()) {
		FGuid AtlusEventManagerTrack = SeqMovie->AddPossessable(TEXT("ATLUS_EventManager"), AtlusEventManager->GetClass());
		MainSeq->BindPossessableObject(AtlusEventManagerTrack, (UObject&)*AtlusEventManager, (UObject*)AtlusEventManager);
	}
	if (!MainSeq->FindPossessableObjectId(*CineCameraActor, nullptr).IsValid()) {
		// Add Atlus Camera
		FGuid AtlusCameraBindingGuid = SeqMovie->AddPossessable(TEXT("ATLUS_Camera"), CineCameraActor->GetClass());
		MainSeq->BindPossessableObject(AtlusCameraBindingGuid, (UObject&)*CineCameraActor, (UObject*)CineCameraActor);
		// [Atlus Event] Add CameraComponent child binding
		// See FSequencer::CreateBinding
		UCineCameraComponent* CineCameraComp = CineCameraActor->GetCineCameraComponent();
		FGuid CineCameraCompGuid = SeqMovie->AddPossessable(TEXT("CameraComponent"), CineCameraComp->GetClass());
		FMovieScenePossessable* CineCameraCompPossessable = SeqMovie->FindPossessable(CineCameraCompGuid);
		CineCameraCompPossessable->SetParent(AtlusCameraBindingGuid);
		MainSeq->BindPossessableObject(CineCameraCompGuid, (UObject&)*CineCameraComp, (UObject*)CineCameraActor);
		FMovieSceneBinding* CineCameraBinding = SeqMovie->FindBinding(CineCameraCompGuid);

		AddPropertyBinding(CineCameraBinding, SeqMovie, UMovieSceneFloatTrack::StaticClass(), TEXT("CurrentAperture"));
		AddPropertyBinding(CineCameraBinding, SeqMovie, UMovieSceneFloatTrack::StaticClass(), TEXT("CurrentFocalLength"));
		AddPropertyBinding(CineCameraBinding, SeqMovie, UMovieSceneFloatTrack::StaticClass(), TEXT("FocusSettings.ManualFocusDistance"));

		// [Atlus Event] Add Transform property
		// See UMovieScene::AddTrack
		FMovieSceneBinding* AtlusCameraBinding = SeqMovie->FindBinding(AtlusCameraBindingGuid);
		UMovieScene3DTransformTrack* AtlCamTrans = NewObject<UMovieScene3DTransformTrack>(SeqMovie, UMovieScene3DTransformTrack::StaticClass(), NAME_None, RF_Transactional);
		UMovieSceneSection* AtlCamTSec = AtlCamTrans->CreateNewSection();
		AtlCamTSec->SetFlags(RF_Transactional);
		AtlCamTSec->SetRange(SeqMovie->GetPlaybackRange());
		AtlCamTrans->AddSection(*AtlCamTSec);
		AtlusCameraBinding->AddTrack(*AtlCamTrans);
	}
	if (!SeqMovie->FindMasterTrack<UMovieSceneSubTrack>()) {
		// Add sound as subtrack
		UMovieSceneSubTrack* Subtracks = MainSeq->GetMovieScene()->AddMasterTrack<UMovieSceneSubTrack>();
		Subtracks->AddSequence((UMovieSceneSequence*)AudioSequence,
			SeqMovie->GetPlaybackRange().GetLowerBound().GetValue(),
			SeqMovie->GetPlaybackRange().GetUpperBound().GetValue().Value);
	}
	UPackage::Save(MainSeq->GetPackage(), MainSeq, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(MainSeq->GetPackage()->GetPathName(nullptr), FPackageName::GetAssetPackageExtension()));
}

void FXrd777RiriModule::AddMainSequenceToWorld(UWorld* World, ULevelSequence* MainSeq, const FXrd777EditEventParams& EvtParams) {
	AAtlEvtLevelSequenceActor* LevelSequenceActor = Cast<AAtlEvtLevelSequenceActor>(World->SpawnActor(AAtlEvtLevelSequenceActor::StaticClass()));
	LevelSequenceActor->LevelSequence = FSoftObjectPath(Utilities.GetMainSequenceFilenameForEvent(EvtParams, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath)));
	LevelSequenceActor->AtlSequenceType = EAtlLevelSequenceActorType::AtlusEvent;
}

void FXrd777RiriModule::CreateEventAssetsTest(const FXrd777EditEventParams& EvtParams) {
	FString TestEventPath = Utilities.GetProjectPathForEvent(EvtParams);
	UE_LOG(LogRiriModule, Display, TEXT("TODO: Create Event Assets: %s"), *TestEventPath);
	bDoesWorldAlreadyExist = true;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString TestEventPathPS5 = TestEventPath.RightChop(FString::Printf(TEXT("/Game/")).Len());
	// Create the base folder
	FString TestEventPathAbs = FPaths::Combine(FPaths::ProjectContentDir(), TestEventPathPS5);
	if (!PlatformFile.DirectoryExists(*TestEventPathAbs)) {
		PlatformFile.CreateDirectoryTree(*TestEventPathAbs);
	}
	// [Optional] Create an inner script folder
	FString TestEventPathScript = FPaths::Combine(TestEventPathAbs, TEXT("Script"));
	if (!PlatformFile.DirectoryExists(*TestEventPathScript)) {
		PlatformFile.CreateDirectoryTree(*TestEventPathScript);
	}
	

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	TOptional<FAssetCreatedPost> BlankCb;
	TOptional<FConvertFilePath> BlankPath;
	UWorldFactory* LevelFactory = NewObject<UWorldFactory>(UWorldFactory::StaticClass());

	// Create flowscript
	CreateAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetBfFilenameForEvent), UBfAsset::StaticClass(), nullptr, BlankCb);
	// Create BMDs
	TArray<FString> BmdsPath = Utilities.GetBmdFilenamesForEvent(EvtParams, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath));
	TArray<FString> BmdPathsUncnv = Utilities.GetBmdFilenamesForEvent(EvtParams, BlankPath);
	for (int i = 0; i < BmdsPath.Num(); i++) {
		CreateAsset(EvtParams, BmdsPath[i], BmdPathsUncnv[i], UBmdAsset::StaticClass(), nullptr, BlankCb);
	}
	// Get level sequences + world
	UWorld* World = Cast<UWorld>(CreateAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetLevelFilenameForEvent), UWorld::StaticClass(), LevelFactory, FAssetCreatedPost::CreateRaw(this, &FXrd777RiriModule::PostCreateLevel)));
	ULevelSequence* MainSeq = Cast<ULevelSequence>(CreateAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetMainSequenceFilenameForEvent), ULevelSequence::StaticClass(), nullptr, FAssetCreatedPost::CreateRaw(this, &FXrd777RiriModule::PostCreateLevelSequence)));
	AudioSequence = Cast<ULevelSequence>(CreateAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetAudioSequenceFilenameForEvent), ULevelSequence::StaticClass(), nullptr, FAssetCreatedPost::CreateRaw(this, &FXrd777RiriModule::PostCreateLevelSequence)));;
	if (!bDoesWorldAlreadyExist) {
		MainSequenceAddObjectBindings(MainSeq, World);
		AddMainSequenceToWorld(World, MainSeq, EvtParams);
	}

	AtlusEventManager = nullptr;
	CineCameraActor = nullptr;
	AudioSequence = nullptr;
}

TSharedRef<SWidget> FXrd777RiriModule::CreateToolbarDropdown() {
	FMenuBuilder MenuBuilder(false, nullptr);
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	if (Settings->ExtractedAssetsDirectory.Path.IsEmpty()) {
		MenuBuilder.AddWidget(EditToolsGetExtractedAssetsNotSet(), FText());
		return MenuBuilder.MakeWidget();
	}
	MenuBuilder.BeginSection("Xrd777EditCharacterCreate", FText::FromString("Create Character Data"));
	MenuBuilder.AddWidget(EditToolsCreateCharacterData(), FText());
	MenuBuilder.EndSection();
	MenuBuilder.BeginSection("Xrd777EditEventData", FText::FromString("Event Data"));
	MenuBuilder.AddWidget(
		SNew(SXrd777EditEventWidget)
			.Data(&EventData)
			.OnSetEventPath_Raw(this, &FXrd777RiriModule::TryGetEventData)
			.OnCreateAssetsTest_Raw(this, &FXrd777RiriModule::CreateEventAssetsTest)
		, FText());
	MenuBuilder.EndSection();
	return MenuBuilder.MakeWidget();
}

#endif

void FXrd777RiriModule::ShutdownModule() {
#if WITH_EDITORONLY_DATA
	ISequencerModule& SequencerModule = FModuleManager::Get().LoadModuleChecked<ISequencerModule>("Sequencer");
	SequencerModule.UnRegisterTrackEditor(EvtAdxSoundFadeTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtAdxSoundManageTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtAdxSoundTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaHandwritingTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaOperationControllerTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaPackAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaPackFaceAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtCharaPropAttachTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtDialogueOptionsTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtDialogueTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtFadeScreenTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtFieldAnimTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtNessageSubtitleTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtMovieTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtScriptTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtSeqControlTrackEditorHandle);
	SequencerModule.UnRegisterTrackEditor(EvtSeqTimeJumpControlTrackEditorHandle);

	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);

	ISettingsModule& SettingsModule = FModuleManager::Get().LoadModuleChecked<ISettingsModule>("Settings");
	SettingsModule.UnregisterSettings("Project", "Project", "Xrd777EditSettings");

	//FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	//AssetRegistryModule.Get().OnAssetAdded().RemoveAll(this);
#endif
}

IMPLEMENT_PRIMARY_GAME_MODULE(FXrd777RiriModule, xrd777, "xrd777" );