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
#include <MovieSceneEvtAdxSoundFadeSection.h>
#include <MovieSceneEvtAdxSoundManageSection.h>
#include <MovieSceneEvtFadeScreenSection.h>
#include <MovieSceneEvtScriptSection.h>
#include <MovieSceneEvtSeqControllerSection.h>
#include <MovieSceneEvtSeqTimeJumpControllerSection.h>

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
#include "UnrealEd/Classes/Factories/AnimSequenceFactory.h"

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

#include "Engine/StaticMeshActor.h"
#include "UnrealEd/Public/Toolkits/AssetEditorManager.h"
#include "Kismet/Public/BlueprintEditor.h"
#include "Kismet/Public/BlueprintEditorContext.h"
#include "UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "BlueprintGraph/Classes/EdGraphSchema_K2.h"

#include "Engine/Classes/Components/BoxComponent.h"
#include "Engine/Classes/Components/CapsuleComponent.h"
#include "xrd777/Public/FldCameraHitBox.h"
#include "xrd777/Public/FldCameraFixed.h"
#include "xrd777/Public/FldCameraHitBase.h"
#include "xrd777/Public/FldCameraFixed.h"
#include "xrd777/Public/FldCameraFree.h"
#include "Engine/Classes/GameFramework/PlayerStart.h"
#include "xrd777/Public/FldCameraBehaviorBase.h"
#include "xrd777/Public/FldCameraBehaviorFixed.h"
#include "xrd777/Public/FldCameraBehaviorFree.h"
#include "Engine/Classes/Engine/SkyLight.h"

#include "UnrealEd/Public/EditorDirectories.h"
#include "xrd777/Public/FldPlayerStart.h"
#include "Engine/Classes/Components/SkyLightComponent.h"
#include "xrd777/Public/FldCameraSpline.h"
#include "xrd777/Public/FldCameraHitSpline.h"

#include "UnrealEd/Public/ObjectTools.h"
#include "Misc/MessageDialog.h"
#include "ContentBrowser/Public/ContentBrowserMenuContexts.h"
#include "Xrd777EditImportFbn.h"
#include "Xrd777EditImportFtd.h"

#include "Xrd777/Public/FldHitActor.h"
#include "Xrd777/Public/FldHitActorBOX.h"
#include "Xrd777/Public/FldHitNameTableRow.h"
#include "Xrd777/Public/FldNpcNameTableRow.h"
#include "Xrd777EditImportFntBin.h"	
#include "FldNpcActor.h"
#include "Xrd777EditImportClt.h"
#include "FldCrowdWalkManager.h"
#include "FldCrowdTarget.h"
#include "MobWalkCharaBaseCore.h"

#include "ISequencerChannelInterface.h"
#include "SequencerChannelInterface.h"

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

	SequencerModule.RegisterChannelInterface<FMovieSceneEvtAdxSoundFadeSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtAdxSoundManageSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtAdxSoundSectionData>();

	SequencerModule.RegisterChannelInterface<FMovieSceneEvtCharaAnimationSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtCharaHandwritingSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtCharaOperationControllerSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtCharaPropAttachSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtDialogueSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtFadeScreenSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtFieldAnimationSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtMessageSubtitleSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtMovieSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtScriptSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtSeqControllerSectionData>();
	SequencerModule.RegisterChannelInterface<FMovieSceneEvtSeqTimeJumpControllerSectionData>();
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

	RemoveNameByRegexOptions.Empty();
	RemoveNameByRegexOptions.Add(MakeShareable(new FString("Prefix")));
	RemoveNameByRegexOptions.Add(MakeShareable(new FString("Suffix")));
	RemoveNameByRegexOptionsSelectedId = 0;

#endif
}
#if WITH_EDITORONLY_DATA

void FXrd777RiriModule::RegisterMenus() {
	FToolMenuOwnerScoped OwnerScoped(this);
	// Main Xrd777 Edit
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
	/*
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	//TSharedPtr<FExtender> LevelUtilsExtension = MakeShareable(new FExtender);
	ContentBrowserModule.GetAll
	TArray<FContentBrowserMenuExtender_SelectedPaths>& MenuExtensionDelegates = ContentBrowserModule.GetAllPathViewContextMenuExtenders();
	MenuExtensionDelegates.Add(FContentBrowserMenuExtender_SelectedPaths::CreateLambda([this](const TArray<FString>& Path) {

	}));
	*/
	// Duplicate actors only for an already existing level asset
	
	UToolMenu* GetAssetAction = UToolMenus::Get()->ExtendMenu("ContentBrowser.AssetContextMenu.AssetActionsSubMenu");
	FToolMenuSection& EditSection = GetAssetAction->FindOrAddSection("Xrd777EditMenuLevel");
	EditSection.AddDynamicEntry("Xrd777EditMenuLevelActors", FNewToolMenuSectionDelegate::CreateLambda([this](FToolMenuSection& InSection) {
		UContentBrowserAssetContextMenuContext* Context = InSection.FindContext<UContentBrowserAssetContextMenuContext>();
		if (Context && Context->AssetContextMenu.IsValid() && Context->CommonClass == UWorld::StaticClass()) {
			InSection.AddEntry(FToolMenuEntry::InitMenuEntry(
				TEXT("LevelUtilsCopyActors"),
				LOCTEXT("LevelUtilsCopyActorText", "[P3RE] Duplicate Actors Only"),
				LOCTEXT("LevelUtilsCopyActorTooltip", "Creates a copy of the asset with only it's actors."),
				FSlateIcon(),
				FToolUIActionChoice(FExecuteAction::CreateLambda([this, Context]() { OnDuplicateLevelActorsOnly(Context); }))
			));
		}
	}));

	// Duplicate actors only for an asset that can't be imported into the Unreal editor without crashing (levels that contain blueprints)
	// We'll have to use the JSON here as reference
	UToolMenu* LevelFromJson = UToolMenus::Get()->ExtendMenu("ContentBrowser.AddNewContextMenu");
	LevelFromJson->AddDynamicSection("Xrd777EditDynamicSectionLevel", FNewToolMenuDelegate::CreateLambda([this](UToolMenu* InMenu) {
		UContentBrowserMenuContext* MenuContextObject = InMenu->FindContext<UContentBrowserMenuContext>();
		UContentBrowserDataMenuContext_AddNewMenu* DataContextObject = InMenu->FindContext<UContentBrowserDataMenuContext_AddNewMenu>();
		if (MenuContextObject && DataContextObject) {
			FToolMenuSection& LevelSection = InMenu->AddSection("Xrd777EditLevelFromJson", LOCTEXT("Xrd777EditLevelFromJson", "XRD777"));
			LevelSection.AddMenuEntry(
				"AddLevelFromJson",
				LOCTEXT("Xrd777EditAddLevelFromJson", "Add Level from JSON"),
				LOCTEXT("Xrd777EditAddLevelFromJsonTooltip", "Add a level into the project from an FModel JSON"),
				//FSlateIcon(FEditorStyle::GetStyleSetName(), ),
				FSlateIcon(),
				FUIAction(
					FExecuteAction::CreateLambda([this, DataContextObject]() { OnImportLevelFromJson(DataContextObject); })
				)
			);
			LevelSection.AddMenuEntry(
				"RemoveMeshNameFromAnim",
				LOCTEXT("Xrd777EditAnimRenameLabel", "Remove prefix/suffix by regex"),
				LOCTEXT("Xrd777EditAnimRenameTooltip", "If importing a BaseSkelton with several anims, remove the mesh name prefixed to each sequence"),
				//FSlateIcon(FEditorStyle::GetStyleSetName(), ),
				FSlateIcon(),
				FUIAction(
					FExecuteAction::CreateLambda([this, DataContextObject]() { OnRemoveMeshNamePrefix(DataContextObject); })
				)
			);
			LevelSection.AddMenuEntry(
				"P5ImportFbn",
				LOCTEXT("Xrd777EditImportFbn", "[Persona 5] Make level from FBN"),
				LOCTEXT("Xrd777EditImportFbnTooltip", "Import FBN"),
				FSlateIcon(),
				FUIAction(
					FExecuteAction::CreateLambda([this, DataContextObject]() { OnImportFbn(DataContextObject); })
				)
			);
		}
	}));
}

FString FXrd777RiriModule::GetJsonNodeNameFromObjectPath(nlohmann::json InJson) {
	FString LocalFullName = FString(UTF8_TO_TCHAR(InJson["ObjectName"].get<std::string>().c_str()));
	return FXrd777RiriModule::GetJsonNodeNameFromObjectPathInner(LocalFullName);
}

FString FXrd777RiriModule::GetJsonNodeNameFromObjectPathInner(FString InFullName) {
	//FString LocalFullName = FString(UTF8_TO_TCHAR(InJson["ObjectName"].get<std::string>().c_str()));
	int32 FullNamePeriodIndex, FullNameColonIndex;
	InFullName.FindLastChar('.', FullNamePeriodIndex); // Leaf name is separated by period (see SCSNode->ChildNodes)
	InFullName.FindLastChar(':', FullNameColonIndex); // Leaf name is separated by colon (see SCSNode->ObjectTemplate)
	int32 LeafNodeIndex = INDEX_NONE;
	if (FullNamePeriodIndex != INDEX_NONE) {
		LeafNodeIndex = FullNamePeriodIndex;
	}
	else if (FullNameColonIndex != INDEX_NONE) {
		LeafNodeIndex = FullNameColonIndex;
	}
	else {
		return FString();
	}
	return InFullName.RightChop(LeafNodeIndex + 1).LeftChop(1); // [SCS_Node'BP_FLDSky_C:SimpleConstructionScript_0.]SCS_Node_2['], [] : to remove
}

FXrd777EditJsonObject* FXrd777RiriModule::GetJsonNodeFromObjectPath(nlohmann::json InJson) {
	FString LocalFullName = FString(UTF8_TO_TCHAR(InJson["ObjectName"].get<std::string>().c_str()));
	FString LocalName = FXrd777RiriModule::GetJsonNodeNameFromObjectPathInner(LocalFullName);
	if (LocalName.IsEmpty()) {
		UE_LOG(LogRiriModule, Error, TEXT("No leaf node character found for object name : %s"), *LocalFullName);
		return nullptr;
	}
	if (FXrd777EditJsonObject* Obj = GetObjectByName(LocalName)) {
		return Obj;
	}
	else {
		UE_LOG(LogRiriModule, Warning, TEXT("Node with name %s doesn't exist locally"), *LocalFullName);
		return nullptr;
	}
}

void FXrd777RiriModule::OnDuplicateLevelActorsOnly(UContentBrowserAssetContextMenuContext* InContext) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	for (TWeakObjectPtr<UObject> SelectedObject : InContext->SelectedObjects) {
		if (SelectedObject != nullptr && SelectedObject->GetClass() == UWorld::StaticClass()) {
			FAssetData ObjectData = AssetRegistryModule.Get().GetAssetByObjectPath(FName(SelectedObject->GetPathName()));
			FString CopyPackageName;
			FString CopyAssetName;
			AssetToolsModule.Get().CreateUniqueAssetName(SelectedObject->GetPackage()->GetPathName(), TEXT(""), CopyPackageName, CopyAssetName);
			Utilities.MakeIntoUnrealPath(CopyPackageName);
			DuplicateLevelActorsOnly(SelectedObject->GetPathName(), CopyPackageName);
		}
	}
}

void FXrd777RiriModule::CreateModelList(int32 CharaId) {
	FString ExtractBasePath = GetExtractedAssetsRootDirectory();
	FString ExtractCharPath = FPaths::Combine(ExtractBasePath, Utilities.GetProjectPathForCharacterId(CharaId));
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
		/*
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
		*/
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

UObject* FXrd777RiriModule::CreateAsset(FString& AssetPath, UClass* AssetType, UFactory* FactoryInstance, TOptional<FPostAssetCreated> AssetCreatedCb) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	// check if the asset already exists
	FAssetData ExistingAsset = AssetRegistryModule.Get().GetAssetByObjectPath(*AssetPath);
	if (ExistingAsset.IsValid()) {
		UE_LOG(LogRiriModule, Display, TEXT("Asset at %s already exists"), *AssetPath);
		return ExistingAsset.GetAsset();
	}
	UE_LOG(LogRiriModule, Display, TEXT("Creating asset at %s"), *AssetPath);

	FString AssetName = FPaths::GetBaseFilename(AssetPath);
	FString PackagePath = FPaths::GetPath(AssetPath);
	FString PackageName = FPaths::Combine(PackagePath, AssetName);
	// make it!!!!
	UPackage* Package = CreatePackage(*PackageName);
	UObject* NewAsset;
	EObjectFlags NewAssetFlags = RF_Public | RF_Standalone | RF_Transactional;
	if (FactoryInstance != nullptr) {
		NewAsset = FactoryInstance->FactoryCreateNew(AssetType, Package, FName(*AssetName), NewAssetFlags, nullptr, GWarn, NAME_None);
	}
	else {
		NewAsset = NewObject<UObject>(Package, AssetType, FName(*AssetName), NewAssetFlags);
	}
	NewAsset->MarkPackageDirty();
	if (AssetCreatedCb.IsSet()) {
		AssetCreatedCb.GetValue().Execute(NewAsset);
	}
	// save to OS
	UPackage::Save(Package, NewAsset, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(PackageName, FPackageName::GetAssetPackageExtension()));
	// sync with asset browser
	AssetRegistryModule.Get().AssetCreated(NewAsset);
	TArray<UObject*> ContentBrowserAssetSyncLocal;
	ContentBrowserAssetSyncLocal.Add(NewAsset);
	ContentBrowserModule.Get().SyncBrowserToAssets(ContentBrowserAssetSyncLocal);
	return NewAsset;
}

// EVENT

UObject* FXrd777RiriModule::CreateEventAsset(
	const FXrd777EditEventParams& EvtParams, FGetFilePath GetPathCb, UClass* AssetType, 
	UFactory* FactoryInstance, TOptional<FAssetCreatedPost> OnAssetCreatedCb) {
	// Check if the given asset already exists
	TOptional<FConvertFilePath> BlankCb;
	FString ObjectPath = GetPathCb.Execute(EvtParams, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath));
	FString AssetPath = GetPathCb.Execute(EvtParams, BlankCb);
	return CreateEventAsset(EvtParams, ObjectPath, AssetPath, AssetType, FactoryInstance, OnAssetCreatedCb);
}

UObject* FXrd777RiriModule::CreateEventAsset(
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
	CreateEventAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetBfFilenameForEvent), UBfAsset::StaticClass(), nullptr, BlankCb);
	// Create BMDs
	TArray<FString> BmdsPath = Utilities.GetBmdFilenamesForEvent(EvtParams, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath));
	TArray<FString> BmdPathsUncnv = Utilities.GetBmdFilenamesForEvent(EvtParams, BlankPath);
	for (int i = 0; i < BmdsPath.Num(); i++) {
		CreateEventAsset(EvtParams, BmdsPath[i], BmdPathsUncnv[i], UBmdAsset::StaticClass(), nullptr, BlankCb);
	}
	// Get level sequences + world
	UWorld* World = Cast<UWorld>(CreateEventAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetLevelFilenameForEvent), UWorld::StaticClass(), LevelFactory, FAssetCreatedPost::CreateRaw(this, &FXrd777RiriModule::PostCreateLevel)));
	ULevelSequence* MainSeq = Cast<ULevelSequence>(CreateEventAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetMainSequenceFilenameForEvent), ULevelSequence::StaticClass(), nullptr, FAssetCreatedPost::CreateRaw(this, &FXrd777RiriModule::PostCreateLevelSequence)));
	AudioSequence = Cast<ULevelSequence>(CreateEventAsset(EvtParams, FGetFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::GetAudioSequenceFilenameForEvent), ULevelSequence::StaticClass(), nullptr, FAssetCreatedPost::CreateRaw(this, &FXrd777RiriModule::PostCreateLevelSequence)));;
	if (!bDoesWorldAlreadyExist) {
		MainSequenceAddObjectBindings(MainSeq, World);
		AddMainSequenceToWorld(World, MainSeq, EvtParams);
	}

	AtlusEventManager = nullptr;
	CineCameraActor = nullptr;
	AudioSequence = nullptr;
}

void FXrd777RiriModule::CreateDummyAnimTest(int32 CharacterId) {
	TArray<FString> DummyAnims = Utilities.GetListOfGameUnimportedAnimSequences(CharacterId);
	UAnimSequenceFactory* AnimSequenceFactory = NewObject<UAnimSequenceFactory>(UAnimSequenceFactory::StaticClass());
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AnimSequenceFactory->TargetSkeleton = Utilities.GetTargetSkeleton(CharacterId); // SKEL_Human (or SKEL_Animal if Koromaru)
	AnimSequenceFactory->PreviewSkeletalMesh = Cast<USkeletalMesh>(AssetRegistryModule.Get().GetAssetByObjectPath(*FString::Printf(TEXT("%s/Models/SK_PC0001_C002.SK_PC0001_C002"), *Utilities.GetProjectPathForCharacterId(1))).GetAsset());
	FPostAssetCreated PostAnimSequenceCreated = FPostAssetCreated::CreateLambda([this](UObject* InObject) {
		UAnimSequence* AnimSequence = CastChecked<UAnimSequence>(InObject);
		// Set Retarget Source Asset
		//AnimSequence->SequenceLength = 
	});
	for (FString& DummyAnim : DummyAnims) {
		CreateAsset(DummyAnim, UAnimSequence::StaticClass(), AnimSequenceFactory, PostAnimSequenceCreated);
	}
}

template<class TComponent>
TComponent* FXrd777RiriModule::CreateActorComponent(AActor* Owner, UActorComponent* ExistComp) {
	TComponent* NewComp = NewObject<TComponent>(Owner, ExistComp->GetFName(), Owner->GetMaskedFlags(RF_PropagateToSubObjects) | RF_DefaultSubObject);
	if (Owner->HasAnyFlags(RF_ClassDefaultObject)) {
		NewComp->SetFlags(RF_Transactional);
		NewComp->GetClass()->AddDefaultSubobject(NewComp, TComponent::StaticClass());
	}
	NewComp->ClearInternalFlags(EInternalObjectFlags::PendingKill);
	//T::StaticClass()
	return NewComp;
}

void FXrd777RiriModule::DuplicateLevelActorsOnly(FString CurrPath, FString NewPath) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TOptional<FPostAssetCreated> BlankCb;
	UWorld* World = Cast<UWorld>(StaticLoadObject(UWorld::StaticClass(), nullptr, *CurrPath));
	UWorldFactory* LevelFactory = NewObject<UWorldFactory>(UWorldFactory::StaticClass());
	UWorld* CopyWorld = Cast<UWorld>(CreateAsset(NewPath, UWorld::StaticClass(), LevelFactory, BlankCb));
	
	for (AActor* CurrActor : World->GetCurrentLevel()->Actors) { // World->GetCurrentLevel() -> PersistentLevel
		FString ActorName = CurrActor->GetName();
		if (CurrActor->GetClass() == AStaticMeshActor::StaticClass()) { // Most level geometry
			UStaticMeshComponent* MeshComp = Cast<AStaticMeshActor>(CurrActor)->GetStaticMeshComponent();
			FString StaticMeshName = MeshComp->GetStaticMesh()->GetPathName();
			//MeshComp->GetStaticMesh()->GetMaterial
			UE_LOG(LogRiriModule, Display, TEXT("Add Static Mesh @ %s, Actor name %s"), *StaticMeshName, *ActorName);
			AStaticMeshActor* NewStaticMesh = Cast<AStaticMeshActor>(CopyWorld->SpawnActor(AStaticMeshActor::StaticClass()));
			NewStaticMesh->Rename(*ActorName);
			NewStaticMesh->SetActorLabel(ActorName);
			NewStaticMesh->GetStaticMeshComponent()->SetStaticMesh(MeshComp->GetStaticMesh());
			GEngine->CopyPropertiesForUnrelatedObjects((UObject*)MeshComp, (UObject*)NewStaticMesh->GetStaticMeshComponent());
		}
		else if (CurrActor->GetClass() == APlayerStart::StaticClass()) { // Player spawn point
			APlayerStart* PlayerStart = Cast<APlayerStart>(CurrActor);
			APlayerStart* NewPlayerStart = Cast<APlayerStart>(CopyWorld->SpawnActor(APlayerStart::StaticClass()));
			NewPlayerStart->Rename(*ActorName);
			NewPlayerStart->SetActorLabel(ActorName);
			GEngine->CopyPropertiesForUnrelatedObjects((UObject*)PlayerStart->GetCapsuleComponent(), (UObject*)NewPlayerStart->GetCapsuleComponent());
		}
		else if (CurrActor->GetClass() == ASkyLight::StaticClass()) {
			ASkyLight* SkyLight = Cast<ASkyLight>(CurrActor);
			ASkyLight* NewSkyLight = Cast<ASkyLight>(CopyWorld->SpawnActor(ASkyLight::StaticClass()));
			GEngine->CopyPropertiesForUnrelatedObjects((UObject*)SkyLight->GetLightComponent(), (UObject*)NewSkyLight->GetLightComponent());
		}
		else if (CurrActor->GetClass() == AFldCameraHitBox::StaticClass()) { // P3RE Specific (Camera hitbox, like PCD in GFD)
			AFldCameraHitBox* CamHitbox = Cast<AFldCameraHitBox>(CurrActor);
			AFldCameraHitBox* NewCamHitbox = Cast<AFldCameraHitBox>(CopyWorld->SpawnActor(AFldCameraHitBox::StaticClass()));
			NewCamHitbox->Rename(*ActorName);
			NewCamHitbox->SetActorLabel(ActorName);
			// Check for box component
			if (CamHitbox->Box) {
				NewCamHitbox->Box = CreateActorComponent<UBoxComponent>(NewCamHitbox, CamHitbox->Box);
				GEngine->CopyPropertiesForUnrelatedObjects(CamHitbox->Box, NewCamHitbox->Box);
			}
		}
		else if (CurrActor->GetClass() == AFldCameraFixed::StaticClass()) { // P3RE Specific (Fields that use fixed camera fields)
			AFldCameraFixed* FldCam = Cast<AFldCameraFixed>(CurrActor);
			AFldCameraFixed* NewFldCam = Cast<AFldCameraFixed>(CopyWorld->SpawnActor(AFldCameraFixed::StaticClass()));
			if (FldCam->Behavior) {
				//NewFldCam->Behavior = DuplicateObject(FldCam->Behavior, NewFldCam, FldCam->Behavior->GetFName());
				NewFldCam->Behavior = CreateActorComponent<UFldCameraBehaviorFixed>(NewFldCam, FldCam->Behavior);
				GEngine->CopyPropertiesForUnrelatedObjects(FldCam->Behavior, NewFldCam->Behavior);
			}
			
			if (FldCam->YawSceneComp) {
				NewFldCam->YawSceneComp = CreateActorComponent<USceneComponent>(NewFldCam, FldCam->YawSceneComp);
				NewFldCam->YawSceneComp->Rename(*FldCam->YawSceneComp->GetName());
				GEngine->CopyPropertiesForUnrelatedObjects(FldCam->YawSceneComp, NewFldCam->YawSceneComp);
				NewFldCam->SetRootComponent(NewFldCam->YawSceneComp);
			}
			
			if (FldCam->PitchSceneComp) {
				NewFldCam->PitchSceneComp = CreateActorComponent<USceneComponent>(NewFldCam, FldCam->PitchSceneComp);
				NewFldCam->PitchSceneComp->Rename(*FldCam->PitchSceneComp->GetName());
				GEngine->CopyPropertiesForUnrelatedObjects(FldCam->PitchSceneComp, NewFldCam->PitchSceneComp);
			}
			if (FldCam->CameraComp) {
				NewFldCam->CameraComp = CreateActorComponent<UCameraComponent>(NewFldCam, FldCam->CameraComp);
				NewFldCam->CameraComp->Rename(*FldCam->CameraComp->GetName());
				GEngine->CopyPropertiesForUnrelatedObjects(FldCam->CameraComp, NewFldCam->CameraComp);
			}
		}
		else {
			UE_LOG(LogRiriModule, Display, TEXT("TODO: Add type %s for %s"), *CurrActor->GetClass()->GetName(), *CurrActor->GetPathName());
		}
	}
	FString CopyWorldPackagePath;
	CopyWorld->GetPackage()->GetPathName(nullptr, CopyWorldPackagePath);
	UPackage::Save(CopyWorld->GetPackage(), CopyWorld, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(CopyWorldPackagePath, FPackageName::GetAssetPackageExtension()));
}

template<class TObjectType>
TObjectType* FXrd777RiriModule::GetObjectFromJsonSerializedPath(nlohmann::json InJson) {
	/*
	FString ObjectName = FString(UTF8_TO_TCHAR(InJson["ObjectName"].get<std::string>().c_str()));
	int32 ObjectTypeCharIdx;
	ObjectName.FindChar('\'', ObjectTypeCharIdx); // Get class name
	FString ObjectClassName = ObjectTypeCharIdx != INDEX_NONE ? ObjectName.Left(ObjectTypeCharIdx) : ObjectName;
	//UClass* ObjectClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), nullptr, *FString::Printf(TEXT("%s.%s"), *ObjectClassName, *ObjectClassName)));
	UClass* ObjectClass = Cast<UClass>(StaticFindObject(UClass::StaticClass(), nullptr, *ObjectClassName));
	*/
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FString ObjectPath = FString(UTF8_TO_TCHAR(InJson["ObjectPath"].get<std::string>().c_str()));
	int32 ObjectPathPeriodIdx; // Get package path (remove anything after the period)
	ObjectPath.FindLastChar('.', ObjectPathPeriodIdx);
	FString ObjectPathPackage = ObjectPathPeriodIdx != INDEX_NONE ? ObjectPath.Left(ObjectPathPeriodIdx) : ObjectPath;
	FString ObjectPathFull = FString::Printf(TEXT("%s.%s"), *ObjectPathPackage, *FPaths::GetBaseFilename(ObjectPathPackage));
	FAssetData AssetData = AssetRegistryModule.Get().GetAssetByObjectPath(*ObjectPathFull);
	return AssetData.IsValid() ? Cast<TObjectType>(AssetData.GetAsset()) : nullptr;
}

FVector FXrd777RiriModule::VectorFromJson(nlohmann::json InJson) {
	return FVector(
		(float)InJson["X"].get<double>(),
		(float)InJson["Y"].get<double>(),
		(float)InJson["Z"].get<double>()
	);
}

FRotator FXrd777RiriModule::RotatorFromJson(nlohmann::json InJson) {
	return FRotator(
		(float)InJson["Pitch"].get<double>(),
		(float)InJson["Yaw"].get<double>(),
		(float)InJson["Roll"].get<double>()
	);
}

void FXrd777RiriModule::AddSceneComponentProperties(nlohmann::json InJson, USceneComponent* InComponent) {
	std::string strRelativeLocation("RelativeLocation");
	if (InJson["Properties"].contains(strRelativeLocation)) {
		InComponent->SetRelativeLocation(FXrd777RiriModule::VectorFromJson(InJson["Properties"]["RelativeLocation"]));
	}
	std::string strRelativeRotation("RelativeRotation");
	if (InJson["Properties"].contains(strRelativeRotation)) {
		InComponent->SetRelativeRotation(FXrd777RiriModule::RotatorFromJson(InJson["Properties"]["RelativeRotation"]));
	}
	std::string strRelativeScale("RelativeScale3D");
	if (InJson["Properties"].contains(strRelativeScale)) {
		InComponent->SetRelativeScale3D(FXrd777RiriModule::VectorFromJson(InJson["Properties"]["RelativeScale3D"]));
	}
}

void FXrd777RiriModule::InitializePlayerStartParameters(FXrd777EditJsonObject* InJsonObject, APlayerStart* InPlayerStart) {
	TArray<FXrd777EditJsonObject*>* PlayerComponents = GetObjectsByOuter(InJsonObject->ObjectName);
	FXrd777EditJsonObject* PlayerCollisionCapsule = FXrd777RiriModule::GetObjectByTypeInOuter(PlayerComponents, TEXT("CapsuleComponent"));
	if (PlayerCollisionCapsule) {
		AddSceneComponentProperties(PlayerCollisionCapsule->ObjectData, InPlayerStart->GetCapsuleComponent());
	}
}

void FXrd777RiriModule::InitializeFldCameraParameters(FXrd777EditJsonObject* InJsonObject, AFldCameraBase* InCamera) {
}

void FXrd777RiriModule::OnRemoveMeshNamePrefix(UContentBrowserDataMenuContext_AddNewMenu* DataContextObject) {
	// TODO: Define a custom regex for this by opening a dialog box after selection (similar to chunk ID dialog)
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	if (DataContextObject->SelectedPaths.Num() > 0) {
		TSharedPtr<SWindow> RootWindow = FGlobalTabmanager::Get()->GetRootWindow();
		bool bGotAssetsSuccess = AssetRegistryModule.Get().GetAssetsByPath(FName(DataContextObject->SelectedPaths[0]), RemmoveNameByRegexAssetData);
		TSharedPtr<SWindow> RemoveMeshWindow = SNew(SWindow)
			.SupportsMaximize(false)
			.SupportsMinimize(false)
			.SizingRule(ESizingRule::Autosized)
			.Title(LOCTEXT("Xrd777EditMeshPrefixTitle", "Remove name part by regex"));
		;
		RemoveMeshWindow->SetContent(
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
							.Text(FText::FromString("Remove: "))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SNew(STextComboBox)
							.OptionsSource(&RemoveNameByRegexOptions)
							.InitiallySelectedItem(RemoveNameByRegexOptions[RemoveNameByRegexOptionsSelectedId])
							.OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo) {
								int32 SelectIndex = RemoveNameByRegexOptions.IndexOfByKey(NewSelection);
								if (SelectIndex != INDEX_NONE) {
									RemoveNameByRegexOptionsSelectedId = SelectIndex;
								}
							})
					]
			]
			+SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock)
							.Text(FText::FromString("Regex to match: "))
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SNew(SEditableTextBox)
							.MinDesiredWidth(100.0f)
							.Text_Lambda([this]() {
								return FText::FromString(RemoveNameByRegexContent);
							})
							.OnTextChanged_Lambda([this](const FText& NewText) {
								RemoveNameByRegexContent = NewText.ToString();
							})
					]
			]
			+ SVerticalBox::Slot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
			[
				SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(10, 0)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SNew(SButton)
							.Text(FText::FromString("OK"))
							.OnClicked_Lambda([this, RemoveMeshWindow]() {

								FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
								FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

								//const FRegexPattern AnimSequencePattern = FRegexPattern(TEXT("A_\\w{2}\\d{4}"));
								//const FRegexPattern AnimSequencePattern = FRegexPattern(TEXT("A_CH_"));
								const FRegexPattern AnimSequencePattern = FRegexPattern(RemoveNameByRegexContent);
								TArray<FAssetRenameData> AssetsToRename;
								for (FAssetData& Asset : RemmoveNameByRegexAssetData) {
									FString AssetFilename = FPaths::GetBaseFilename(Asset.GetPackage()->GetPathName());
									FRegexMatcher MatchString = FRegexMatcher(AnimSequencePattern, AssetFilename);
									if (MatchString.FindNext()) {
										FString NewFilename = (RemoveNameByRegexOptionsSelectedId == 0)
											? AssetFilename.RightChop(MatchString.GetMatchBeginning()) // Prefix
											: AssetFilename.LeftChop(AssetFilename.Len() - MatchString.GetMatchBeginning()); // Suffix
										AssetsToRename.Add(FAssetRenameData(Asset.GetAsset(), FPaths::GetPath(Asset.GetPackage()->GetPathName()), NewFilename));
									}
								}
								AssetToolsModule.Get().RenameAssets(AssetsToRename);
								ContentBrowserModule.Get().SyncBrowserToAssets(RemmoveNameByRegexAssetData);

								RemoveMeshWindow->RequestDestroyWindow();
								return FReply::Handled();
							})
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(10, 0)
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Center)
					[
						SNew(SButton)
							.Text(FText::FromString("Cancel"))
							.OnClicked_Lambda([RemoveMeshWindow]() {
								RemoveMeshWindow->RequestDestroyWindow();
								return FReply::Handled();
							})
					]
			]
		);
		FSlateApplication::Get().AddModalWindow(RemoveMeshWindow.ToSharedRef(), RootWindow);
	}
	else {
		FText FolderEmptyError = LOCTEXT("Xrd777EditFolderEmpty", "Folder is empty");
		FMessageDialog::Open(EAppMsgType::Ok, FolderEmptyError);
	}
}

void FXrd777RiriModule::UncookAssetsInFolder(UContentBrowserDataMenuContext_AddNewMenu* DataContextObject) {
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	if (DataContextObject->SelectedPaths.Num() > 0) {
		TArray<FAssetData> AssetsList;
		TArray<UObject*> OldAssets;
		TArray<TTuple<FString, UObject*>> NewAssets;
		bool bGotAssetsSuccess = AssetRegistryModule.Get().GetAssetsByPath(FName(DataContextObject->SelectedPaths[0]), AssetsList);
		for (FAssetData& Asset : AssetsList) {
			if (Asset.GetAsset()->GetPackage()->bIsCookedForEditor) {
				FString OriginalAssetPath = Asset.GetAsset()->GetPackage()->GetPathName();
				FString DuplicateNameTemp = OriginalAssetPath + "1";
				UObject* NewAsset = AssetToolsModule.Get().DuplicateAsset(FPaths::GetBaseFilename(DuplicateNameTemp), FPaths::GetPath(DuplicateNameTemp), Asset.GetAsset());
				OldAssets.Add(Asset.GetAsset());
				NewAssets.Emplace(OriginalAssetPath, NewAsset);
			}
		}
		ObjectTools::ForceDeleteObjects(OldAssets, false);
		for (TTuple<FString, UObject*>& NewAsset : NewAssets) {
			NewAsset.Value->Rename(*FPaths::GetBaseFilename(NewAsset.Key));
			UPackage::Save(NewAsset.Value->GetPackage(), NewAsset.Value, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(NewAsset.Key, FPackageName::GetAssetPackageExtension()));
		}
		ContentBrowserModule.Get().SyncBrowserToAssets(AssetsList);
	}
}


void FXrd777RiriModule::OnImportLevelFromJson(UContentBrowserDataMenuContext_AddNewMenu* DataContextObject) {
	IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
	TArray<FString> OpenedFiles;
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	FString LastDirectory;
	if (!Settings->ExtractedAssetsDirectory.Path.IsEmpty()) {
		LastDirectory = Settings->FModelExportDirectory.Path + "/P3R/Content";
		if (DataContextObject->SelectedPaths.Num() > 0 &&
			IFileManager::Get().DirectoryExists(*FString::Printf(TEXT("%s%s"), *LastDirectory, *DataContextObject->SelectedPaths[0].ToString().RightChop(5)))) {
			LastDirectory += DataContextObject->SelectedPaths[0].ToString().RightChop(5); // remove "/Game" from path
		}
	}
	else {
		UE_LOG(LogRiriModule, Warning, TEXT("Extracted Assets Directory was not set, defaulting to last directory used to import an asset"));
		LastDirectory = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);
	}
	bool bSelected = false;
	if (Platform) {
		const void* ParentHWND = FSlateApplication::Get().FindBestParentWindowForDialogs(nullptr).Get()->GetNativeWindow().Get()->GetOSWindowHandle();
		bSelected = Platform->OpenFileDialog(
			ParentHWND,
			TEXT("Import Level from JSON"),
			LastDirectory,
			TEXT(""),
			TEXT("*"),
			EFileDialogFlags::None,
			OpenedFiles
		);
	}
	if (OpenedFiles.Num() == 0) {
		return;
	}
	std::ifstream FModelJsonFile(*OpenedFiles[0]);
	RootNode = nlohmann::json::parse(FModelJsonFile);
	for (nlohmann::json::iterator JIt = RootNode.begin(); JIt != RootNode.end(); JIt++) {
		TSharedRef<FXrd777EditJsonObject> Obj(new FXrd777EditJsonObject(*JIt));
		int32 AddedIndex = Objects.Add(Obj);
		if (Obj.Get().ObjectOuter.IsSet()) {
			if (TArray<FXrd777EditJsonObject*>* ObjectsByOuterTarget = ObjectsByOuter.Find(Obj.Get().ObjectOuter.GetValue())) {
				ObjectsByOuterTarget->Add(&Obj.Get());
			}
			else {
				ObjectsByOuter.Add(Obj.Get().ObjectOuter.GetValue(), TArray<FXrd777EditJsonObject*>()).Add(&Obj.Get());
			}
		}
		ObjectsByName.Add(Obj.Get().ObjectName, &Obj.Get());
	}
	if (FXrd777EditJsonObject** pPersistentLevel = ObjectsByName.Find(TEXT("PersistentLevel"))) {
		TOptional<FPostAssetCreated> BlankCb;
		UWorldFactory* LevelFactory = NewObject<UWorldFactory>(UWorldFactory::StaticClass());
		FString AssetPath = DataContextObject->SelectedPaths[0].ToString() + "/" + FPaths::GetBaseFilename(OpenedFiles[0]);
		Utilities.MakeIntoUnrealPath(AssetPath);
		UWorld* CopyWorld = Cast<UWorld>(CreateAsset(AssetPath, UWorld::StaticClass(), LevelFactory, BlankCb));
		nlohmann::json PersistentLevelData = (*pPersistentLevel)->ObjectData;

		AFldCameraFixed* NewFldCam = nullptr;
		AFldCameraHitBox* NewCamHitbox = nullptr;
		for (auto& LevelActor : PersistentLevelData["Actors"].items()) {
			if (LevelActor.value().is_null()) {
				continue;
			}
			FXrd777EditJsonObject* ActorObject = GetJsonNodeFromObjectPath(LevelActor.value());
			if (!ActorObject) {
				continue;
			}
			if (ActorObject->ObjectType == TEXT("StaticMeshActor")) {
				FXrd777EditJsonObject* StaticMeshComp = GetObjectByOuterSingle(ActorObject->ObjectName);
				//FXrd777EditJsonObject* StaticMeshComp = GetJsonNodeFromObjectPath(ActorObject->ObjectData["Properties"]["StaticMeshComponent"]);
				if (StaticMeshComp) {
					AStaticMeshActor* NewStaticMesh = Cast<AStaticMeshActor>(CopyWorld->SpawnActor(AStaticMeshActor::StaticClass()));
					NewStaticMesh->Rename(*ActorObject->ObjectName);
					NewStaticMesh->SetActorLabel(ActorObject->ObjectName);
					// get static mesh
					UStaticMesh* StaticMesh = GetObjectFromJsonSerializedPath<UStaticMesh>(StaticMeshComp->ObjectData["Properties"]["StaticMesh"]);
					if (StaticMesh) {
						NewStaticMesh->GetStaticMeshComponent()->SetStaticMesh(StaticMesh);
					}
					else {
						UE_LOG(LogRiriModule, Error, TEXT("Static mesh for level actor %s doesn't exist."), *ActorObject->ObjectName);
					}
					AddSceneComponentProperties(StaticMeshComp->ObjectData, (USceneComponent*)NewStaticMesh->GetStaticMeshComponent());
				}
			}
			else if (ActorObject->ObjectType == TEXT("SkyLight")) {
				FXrd777EditJsonObject* LightComponent = GetJsonNodeFromObjectPath(ActorObject->ObjectData["Properties"]["LightComponent"]);
				ASkyLight* NewSkyLight = Cast<ASkyLight>(CopyWorld->SpawnActor(ASkyLight::StaticClass()));
				NewSkyLight->Rename(*ActorObject->ObjectName);
				NewSkyLight->SetActorLabel(ActorObject->ObjectName);
			}
			else if (ActorObject->ObjectType == TEXT("FldPlayerStart")) {
				AFldPlayerStart* NewFldPlayerStart = Cast<AFldPlayerStart>(CopyWorld->SpawnActor(AFldPlayerStart::StaticClass()));
				FXrd777RiriModule::InitializePlayerStartParameters(ActorObject, NewFldPlayerStart);
				//FXrd777EditJsonObject* FldPlayerCameraDir = FXrd777RiriModule::GetObjectByNameInOuter(FldPlayerComponents, FXrd777RiriModule::GetJsonNodeNameFromObjectPath(ActorObject->ObjectData["Properties"]["CameraDir"]));
			}
			else if (ActorObject->ObjectType == TEXT("PlayerStart")) {
				APlayerStart* NewPlayerStart = Cast<APlayerStart>(CopyWorld->SpawnActor(APlayerStart::StaticClass()));
				FXrd777RiriModule::InitializePlayerStartParameters(ActorObject, NewPlayerStart);
			}
			else if (ActorObject->ObjectType == TEXT("FldCameraHitBox")) {
				NewCamHitbox = Cast<AFldCameraHitBox>(CopyWorld->SpawnActor(AFldCameraHitBox::StaticClass()));
				NewCamHitbox->Rename(*ActorObject->ObjectName);
				NewCamHitbox->SetActorLabel(ActorObject->ObjectName);
				FXrd777EditJsonObject* ShapeBoxComponent = GetObjectByOuterSingle(ActorObject->ObjectName);
				if (ShapeBoxComponent) {
					NewCamHitbox->Box->SetBoxExtent(FXrd777RiriModule::VectorFromJson(ShapeBoxComponent->ObjectData["Properties"]["BoxExtent"]));
					NewCamHitbox->Box->SetRelativeLocation(FXrd777RiriModule::VectorFromJson(ShapeBoxComponent->ObjectData["Properties"]["RelativeLocation"]));
				}
			}
			else if (ActorObject->ObjectType == TEXT("FldCameraFixed")) {
				NewFldCam = Cast<AFldCameraFixed>(CopyWorld->SpawnActor(AFldCameraFixed::StaticClass()));
				NewFldCam->Rename(*ActorObject->ObjectName);
				NewFldCam->SetActorLabel(ActorObject->ObjectName);
				FXrd777EditJsonObject* CamBehavior = GetJsonNodeFromObjectPath(ActorObject->ObjectData["Properties"]["Behavior"]);
				if (CamBehavior) {
					if (GetJsonNodeFromObjectPath(CamBehavior->ObjectData["Properties"]["BaseOwner"])) {
						NewFldCam->Behavior->BaseOwner = (AFldCameraBase*)NewFldCam;
					}
					if (CamBehavior->ObjectContainsProperty(TEXT("FixedYaw"))) {
						NewFldCam->Behavior->FixedYaw = (float)CamBehavior->ObjectData["Properties"]["FixedYaw"].get<double>();
					}
					if (CamBehavior->ObjectContainsProperty(TEXT("FixedPitch"))) {
						NewFldCam->Behavior->FixedPitch = (float)CamBehavior->ObjectData["Properties"]["FixedPitch"].get<double>();
					}
				}
				FXrd777EditJsonObject* CamYawSceneComponent = GetJsonNodeFromObjectPath(ActorObject->ObjectData["Properties"]["YawSceneComp"]);
				AddSceneComponentProperties(CamYawSceneComponent->ObjectData, NewFldCam->YawSceneComp);
				NewFldCam->SetRootComponent(NewFldCam->YawSceneComp);
				FXrd777EditJsonObject* CamPitchSceneComponent = GetJsonNodeFromObjectPath(ActorObject->ObjectData["Properties"]["PitchSceneComp"]);
				AddSceneComponentProperties(CamPitchSceneComponent->ObjectData, NewFldCam->PitchSceneComp);
				NewFldCam->PitchSceneComp->AttachTo(NewFldCam->YawSceneComp);
				FXrd777EditJsonObject* CamCameraComponent = GetJsonNodeFromObjectPath(ActorObject->ObjectData["Properties"]["CameraComp"]);
				AddSceneComponentProperties(CamCameraComponent->ObjectData, NewFldCam->CameraComp);
				if (CamCameraComponent->ObjectContainsProperty(TEXT("FieldOfView"))) {
					NewFldCam->CameraComp->FieldOfView = (float)CamCameraComponent->ObjectData["Properties"]["FieldOfView"].get<double>();
				}
				NewFldCam->CameraComp->AttachTo(NewFldCam->PitchSceneComp);
			}
			/*
			else if (ActorObject->ObjectType == TEXT("FldCameraHitSpline")) {
				//AFldCameraHitSpline* NewHitCamSpline = Cast<AFldCameraHitSpline>(CopyWorld->SpawnActor(AFldCameraHitSpline::StaticClass()));
				// BoxComp, SplineComp, CameraSplineComp, CameraList, TrackingDistance, LockAtYaw, LockAtPitch, InstanceComponents
			}
			else if (ActorObject->ObjectType == TEXT("FldCameraSpline")) {
				//AFldCameraSpline* NewCamSpline = Cast<AFldCameraSpline>(CopyWorld->SpawnActor(AFldCameraSpline::StaticClass()));
				// YawSceneComp
				// PitchSceneComp
				// CameraComp
			}
			*/
			else {
				UE_LOG(LogRiriModule, Display, TEXT("TODO Persistent level: Got actor %s, type %s"), *ActorObject->ObjectName, *ActorObject->ObjectType);
			}
			//UE_LOG(LogRiriModule, Display, TEXT("TODO Persistent level: Got actor %s"), *ActorObject->ObjectName);
		}
		if (NewFldCam && NewCamHitbox) {
			UE_LOG(LogRiriModule, Display, TEXT("Parenting Field Camera Yaw Component to Camera Hitbox"));
			NewFldCam->YawSceneComp->AttachTo(NewCamHitbox->Box);
		}
		UPackage::Save(CopyWorld->GetPackage(), CopyWorld, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(CopyWorld->GetPackage()->GetPathName(), FPackageName::GetAssetPackageExtension()));
	}

	Objects.Empty();
	//ObjectsByType.Empty();
	ObjectsByOuter.Empty();
	ObjectsByName.Empty();
	RootNode.clear();
}

TSharedRef<SWidget> FXrd777RiriModule::CreateToolbarDropdown() {
	FMenuBuilder MenuBuilder(false, nullptr);
	const UXrd777EditSettings* Settings = GetDefault<UXrd777EditSettings>();
	if (Settings->ExtractedAssetsDirectory.Path.IsEmpty()) {
		MenuBuilder.AddWidget(EditToolsGetExtractedAssetsNotSet(), FText());
		return MenuBuilder.MakeWidget();
	}
	// Not needed
	/*
	MenuBuilder.BeginSection("Xrd777EditCharacterCreate", FText::FromString("Create Character Data"));
	MenuBuilder.AddWidget(EditToolsCreateCharacterData(), FText());
	MenuBuilder.EndSection();
	MenuBuilder.BeginSection("Xrd777EditEventData", FText::FromString("Event Data"));
	MenuBuilder.AddWidget(
		SNew(SXrd777EditEventWidget)
			.Data(&EventData)
			.OnSetEventPath_Raw(this, &FXrd777RiriModule::TryGetEventData)
			.OnCreateAssetsTest_Raw(this, &FXrd777RiriModule::CreateEventAssetsTest)
			.OnMakeDummyAnimTest_Raw(this, &FXrd777RiriModule::CreateDummyAnimTest)
		, FText());
	MenuBuilder.EndSection();
	*/
	return MenuBuilder.MakeWidget();
}

void FXrd777RiriModule::OnImportFbn(UContentBrowserDataMenuContext_AddNewMenu* DataContextObject) {

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	FContentBrowserModule& ContentBrowserModule = FModuleManager::Get().LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	// Find DT_FldDungeonHitName (FLDPLACENAME.FTD)

	IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();
	FString L10NLocale = TEXT("en");
	FString FldDungeonHitNamePath = Utilities.GetInternationalFilePath(TEXT("Field/Data/DataTable/Texts/DT_FldDungeonHitName"), &L10NLocale);
	Utilities.MakeIntoUnrealPath(FldDungeonHitNamePath);
	FAssetData FldDungeonHitName = AssetRegistry.GetAssetByObjectPath(FName(FldDungeonHitNamePath));
	if (!FldDungeonHitName.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoFldDungeonHitName", "DT_FldDungeonHitName is missing"));
		return;
	}
	UDataTable* FldDngHitName = (UDataTable*)FldDungeonHitName.GetAsset();
	int32 CurrentHighestKinId = 0;
	TMap<FString, FName> FldDngHitNameToKin;
	for (FName DngHitKin : FldDngHitName->GetRowNames()) {
		int32 CurrentKinId = FCString::Atoi(*DngHitKin.ToString().RightChop(4));
		if (CurrentHighestKinId < CurrentKinId) CurrentHighestKinId = CurrentKinId;
		FldDngHitNameToKin.Add(FldDngHitName->FindRow<FFldHitNameTableRow>(DngHitKin, TEXT(""))->Name, DngHitKin);
	}
	// Find DT_FldDailyHitName (FLDCHECKNAME.FTD)
	FString FldDailyHitNamePath = Utilities.GetInternationalFilePath(TEXT("Field/Data/DataTable/Texts/DT_FldDailyHitName"), &L10NLocale);
	Utilities.MakeIntoUnrealPath(FldDailyHitNamePath);
	FAssetData FldDailyHitName = AssetRegistry.GetAssetByObjectPath(FName(FldDailyHitNamePath));
	if (!FldDailyHitName.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoFldDailyHitName", "DT_FldDailyHitName is missing"));
		return;
	}

	// Find DT_FldNpcName (FLDNPCNAME.FTD)
	FString FldNpcNameAssetPath = Utilities.GetInternationalFilePath(TEXT("Field/Data/DataTable/Texts/DT_FldNpcName"), &L10NLocale);
	Utilities.MakeIntoUnrealPath(FldNpcNameAssetPath);
	FAssetData FldNpcNameAsset = AssetRegistry.GetAssetByObjectPath(FName(FldNpcNameAssetPath));
	if (!FldNpcNameAsset.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoFldPlaceName", "DT_FldNpcName is missing"));
		return;
	}
	UDataTable* FldNpcNametable = (UDataTable*)FldNpcNameAsset.GetAsset();
	int32 CurrentHighestNpcKinId = 0;
	TMap<FString, FName> FldNpcNameToKinId;
	for (FName NpcHitKin : FldNpcNametable->GetRowNames()) {
		int32 CurrentKinId = FCString::Atoi(*NpcHitKin.ToString().RightChop(4));
		if (CurrentHighestNpcKinId < CurrentKinId) CurrentHighestNpcKinId = CurrentKinId;
		FldNpcNameToKinId.Add(FldNpcNametable->FindRow<FFldNpcNameTableRow>(NpcHitKin, TEXT(""))->Name, NpcHitKin);
	}

	// Find BP_FldCrowdWalkManager
	FString FldCrowdWalkManagerPath = Utilities.GetInternationalFilePath(TEXT("Blueprints/Field/Crowd/BP_FldCrowdWalkManager"), nullptr);
	Utilities.MakeIntoUnrealPath(FldCrowdWalkManagerPath);
	FAssetData FldCrowdWalkManagerAsset = AssetRegistry.GetAssetByObjectPath(FName(FldCrowdWalkManagerPath));
	if (!FldCrowdWalkManagerAsset.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoFldCrowdWalkManager", "BP_FldCrowdWalkManager is missing"));
		return;
	}

	// Find BP_FldNpcMain and BP_FldNpcMob
	FString FldNpcMainPath = Utilities.GetInternationalFilePath(TEXT("Blueprints/Field/Character/BP_FldNpcMain"), nullptr);
	Utilities.MakeIntoUnrealPath(FldNpcMainPath);
	FAssetData FldNpcMainAsset = AssetRegistry.GetAssetByObjectPath(FName(FldNpcMainPath));
	if (!FldNpcMainAsset.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoFldNpcMain", "BP_FldNpcMain is missing"));
		return;
	}
	FString FldNpcMobPath = Utilities.GetInternationalFilePath(TEXT("Blueprints/Field/Character/BP_FldNpcMob"), nullptr);
	Utilities.MakeIntoUnrealPath(FldNpcMobPath);
	FAssetData FldNpcMobAsset = AssetRegistry.GetAssetByObjectPath(FName(FldNpcMobPath));
	if (!FldNpcMobAsset.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoFldNpcMob", "BP_FldNpcMob is missing"));
		return;
	}

	// Use Saori Rankup as placeholder for interact
	FString BpInteractPlayPath = Utilities.GetInternationalFilePath(TEXT("Blueprints/Field/CmmNpc/BP_NPC_Saori_Rank1_Play"), nullptr);
	Utilities.MakeIntoUnrealPath(BpInteractPlayPath);
	FAssetData BpInteractPlayAsset = AssetRegistry.GetAssetByObjectPath(FName(BpInteractPlayPath));
	if (!BpInteractPlayAsset.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoBpInteractPlay", "BP_NPC_Saori_Rank1_Play is missing"));
		return;
	}
	// Use placeholder MC Walk
	FString McWalkPath = Utilities.GetInternationalFilePath(TEXT("Blueprints/Characters/Mob/Walk/BP_MCWalk0012_100"), nullptr);
	Utilities.MakeIntoUnrealPath(McWalkPath);
	FAssetData McWalkAsset = AssetRegistry.GetAssetByObjectPath(FName(McWalkPath));
	if (!McWalkAsset.IsValid()) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoBpInteractPlay", "MC Walk is missing"));
		return;
	}

	// Open dialog

	IDesktopPlatform* Platform = FDesktopPlatformModule::Get();
	TArray<FString> OpenedFiles;
	FString LastDirectory = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);
	bool bSelected = false;

	if (Platform) {
		const void* ParentHWND = FSlateApplication::Get().FindBestParentWindowForDialogs(nullptr).Get()->GetNativeWindow().Get()->GetOSWindowHandle();
		bSelected = Platform->OpenFileDialog(
			ParentHWND,
			TEXT("Select Persona 5 FBN"),
			LastDirectory,
			TEXT(""),
			TEXT("*"),
			EFileDialogFlags::None,
			OpenedFiles
		);
	}
	if (OpenedFiles.Num() == 0) {
		return;
	}
	// We need to check that the files we'll reference exist as well, those being
	// - the HTB file in FIELD/HIT
	// - FLDPLACENAME.FTD
	// - FLDCHECKNAME.FTD

	FString FBNPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*OpenedFiles[0]);
	FString FBNParentDir = TEXT("DATA/");
	FString FBNBaseName = FPaths::GetBaseFilename(FBNPath);
	FString HTBPath = FPaths::Combine(FBNPath.Left(FBNPath.Find(FBNParentDir)), TEXT("HIT"), FString::Printf(TEXT("%s.HTB"), *FBNBaseName));
	FString BaseCpkDir = TEXT("BASE.CPK/");
	FString FldPlaceNamePath = FPaths::Combine(FBNPath.Left(FBNPath.Find(BaseCpkDir)), TEXT("EN.CPK"), TEXT("FIELD"), TEXT("FTD"), TEXT("FLDPLACENAME.FTD"));
	FString FldCheckNamePath = FPaths::Combine(FBNPath.Left(FBNPath.Find(BaseCpkDir)), TEXT("EN.CPK"), TEXT("FIELD"), TEXT("FTD"), TEXT("FLDCHECKNAME.FTD"));
	FString FldNpcNamePath = FPaths::Combine(FBNPath.Left(FBNPath.Find(BaseCpkDir)), TEXT("EN.CPK"), TEXT("FIELD"), TEXT("FTD"), TEXT("FLDNPCNAME.FTD"));
	FString FldNpcTablePath = FPaths::Combine(FBNPath.Left(FBNPath.Find(FBNParentDir)), TEXT("NPC"), FString::Printf(TEXT("FNT%s.BIN"), *FBNBaseName.RightChop(1)));
	FString CltPath = FPaths::Combine(FBNPath.Left(FBNPath.Find(FBNParentDir)), TEXT("NPC"), FString::Printf(TEXT("%s.CLT"), *FBNBaseName.LeftChop(3)));

	if (!IFileManager::Get().FileExists(*FBNPath)) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5FBN", "Persona 5 Royal FBN file is missing"));
		return;
	}
	if (!IFileManager::Get().FileExists(*HTBPath)) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5HTB", "Persona 5 Royal HTB file is missing"));
		return;
	}
	if (!IFileManager::Get().FileExists(*FldPlaceNamePath)) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5FldPlace", "Persona 5 Royal FLDPLACENAME.FTD is missing"));
		return;
	}
	if (!IFileManager::Get().FileExists(*FldCheckNamePath)) {;
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5FldCheck", "Persona 5 Royal FLDCHECKNAME.FTD is missing"));
		return;
	}
	if (!IFileManager::Get().FileExists(*FldNpcNamePath)) {;
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5FldNpc", "Persona 5 Royal FLDNPCNAME.FTD is missing"));
		return;
	}
	if (!IFileManager::Get().FileExists(*FldNpcTablePath)) {;
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5Fnt", "Persona 5 Royal FNT file is missing"));
		return;
	}
	/*
	// Not all fields have crowd data (Leblanc is a good example!)
	if (!IFileManager::Get().FileExists(*CltPath)) {
		FMessageDialog::Open(EAppMsgType::Ok, LOCTEXT("Xrd777EditFbnErrorNoP5Clt", "Persona 5 Royal CLT is missing"));
		return;
	}
	*/

	// Open the FBN file
	Xrd777EditImportFbn FbnData = Xrd777EditImportFbn();
	FbnData.ImportFbn(FBNPath);
	// Open the HTB file
	Xrd777EditImportFbn HtbData = Xrd777EditImportFbn();
	HtbData.ImportFbn(HTBPath);
	// Open FTD name files
	Xrd777EditImportFtd FldPlaceName = Xrd777EditImportFtd();
	FldPlaceName.ImportFtd(FldPlaceNamePath);
	Xrd777EditImportFtd FldCheckName = Xrd777EditImportFtd();
	FldCheckName.ImportFtd(FldCheckNamePath);
	Xrd777EditImportFtd FldNpcName = Xrd777EditImportFtd();
	FldNpcName.ImportFtd(FldNpcNamePath);
	// Create hit map
	Xrd777EditImportFntBin FldFntBin = Xrd777EditImportFntBin();
	FldFntBin.ImportFnt(FldNpcTablePath);
	// Create crowd layout table
	Xrd777EditImportClt FldClt = Xrd777EditImportClt();
	if (!IFileManager::Get().FileExists(*CltPath)) {
		FldClt.ImportClt(CltPath);
	}
	
	UWorldFactory* LevelFactory = NewObject<UWorldFactory>(UWorldFactory::StaticClass());
	FString AssetPath = FPaths::Combine(DataContextObject->SelectedPaths[0].ToString(), TEXT("LV_F120_101_HitFbn"));
	Utilities.MakeIntoUnrealPath(AssetPath);
	TOptional<FPostAssetCreated> BlankCb;
	UWorld* HitWorld = Cast<UWorld>(CreateAsset(AssetPath, UWorld::StaticClass(), LevelFactory, BlankCb));

	// Add triggers
	FFbnBlock* TriggerBlock = FbnData.FbnBlocks.FindByPredicate([](FFbnBlock& CurrBlock) { return CurrBlock.Type == EFbnListType::FBN_Trigger; });
	FFbnBlock* HitBlock = HtbData.FbnBlocks.FindByPredicate([](FFbnBlock& CurrBlock) { return CurrBlock.Type == EFbnListType::FBN_Hit; });
	if (TriggerBlock && HitBlock && TriggerBlock->BlockEntries.Num() == HitBlock->BlockEntries.Num()) {
		int32 TriggerIndex = 0;
		for (int i = 0; i < TriggerBlock->BlockEntries.Num(); i++) {
			FFbnTriggerVolume* TriggerVolume = (FFbnTriggerVolume*)TriggerBlock->BlockEntries[i];
			FFbnHitDefinition* HitEntry = (FFbnHitDefinition*)HitBlock->BlockEntries[i];
			if (TriggerVolume->Shape != ETriggerShape::Cube) {
				UE_LOG(LogRiriModule, Display, TEXT("TODO: Hit types that aren't boxes lol"));
				continue;
			}

			FString TriggerPromptName;
			switch (HitEntry->PromptType) {
			case EXAMINE_fldCheckName0:
			case EXAMINE_fldCheckName1:
			case EXAMINE_fldCheckName2:
			case EXAMINE_fldCheckName3:
			case EXAMINE_fldCheckName4:
			case STEAL_fldCheckName:
			case SHOP_fldCheckName:
				TriggerPromptName = FldCheckName.Table.Data[HitEntry->NameID];
				UE_LOG(LogRiriModule, Display, TEXT("%s"), *FldCheckName.Table.Data[HitEntry->NameID]);
				break;
			case GO_fldPlaceName:
				TriggerPromptName = FldPlaceName.Table.Data[HitEntry->NameID];
				UE_LOG(LogRiriModule, Display, TEXT("%s"), *FldPlaceName.Table.Data[HitEntry->NameID]);
				break;
			}
			if (TriggerPromptName.Len() == 0 || TriggerPromptName == TEXT("NULL")) {
				UE_LOG(LogRiriModule, Display, TEXT("Trigger %d is null, skipping"));
				continue;
			}

			AFldHitActorBOX* NewFldHitbox = Cast<AFldHitActorBOX>(HitWorld->SpawnActor(AFldHitActorBOX::StaticClass()));
			NewFldHitbox->SetRootComponent(NewFldHitbox->RootComp_);
			FString TriggerName = FString::Printf(TEXT("%s_FBN_Trigger%d"), *FBNBaseName, i);
			NewFldHitbox->Rename(*TriggerName);
			NewFldHitbox->SetActorLabel(TriggerName);
			UE_LOG(LogRiriModule, Display, TEXT("Trigger %d center: %s"), i, *TriggerVolume->SphereCenter.ToString());
			// Set location, size and rotation
			// BoxExtents defauilt dimensions: 32
			NewFldHitbox->SetActorLocation(FVector(TriggerVolume->SphereCenter.X, TriggerVolume->SphereCenter.Z, TriggerVolume->SphereCenter.Y));
			NewFldHitbox->SetActorScale3D(FVector(TriggerVolume->SphereRadiusX / 16, TriggerVolume->SphereRadiusY / 16, 2));
			FVector2D BoxDiff = FVector2D(TriggerVolume->CubeBottomRight.X - TriggerVolume->CubeBottomLeft.X, TriggerVolume->CubeBottomRight.Z - TriggerVolume->CubeBottomLeft.Z);
			float BoxDP = FMath::Acos(BoxDiff.X / FMath::Sqrt(FMath::Square(BoxDiff.X) + FMath::Square(BoxDiff.Y))) * 180 / PI;
			float BoxAngleDeg = BoxDiff.Y > 0 ? BoxDP : 360 - BoxDP;
			float HitComAngleOffset = -90.0f;
			NewFldHitbox->SetActorRotation(FRotator(0, HitComAngleOffset + BoxAngleDeg, 0));
			NewFldHitbox->UpdateComponentTransforms();

			// Set to the current field ID (for now)
			NewFldHitbox->mMajorID_ = 120;
			NewFldHitbox->mMinorID_ = 101;
			// All in AreaChange for now (this uses DT_FldDungeonHitName)
			NewFldHitbox->mType_ = EFldHitType::AreaChange;
			if (TriggerPromptName.Len() > 0) {
				if (FName* TargetKinId = FldDngHitNameToKin.Find(TriggerPromptName)) {
					NewFldHitbox->mNameIndex_ = FCString::Atoi(*TargetKinId->ToString().RightChop(4));
				}
				else {
					FFldHitNameTableRow NewRow;
					NewRow.Name = TriggerPromptName;
					CurrentHighestKinId++;
					FName NewKinId = FName(FString::Printf(TEXT("KIN_%08d"), CurrentHighestKinId));
					FldDngHitName->AddRow(NewKinId, NewRow);
					FldDngHitNameToKin.Add(FldDngHitName->FindRow<FFldHitNameTableRow>(NewKinId, TEXT(""))->Name, NewKinId);
					NewFldHitbox->mNameIndex_ = CurrentHighestKinId;
				}
			}
			else {
				NewFldHitbox->mNameIndex_ = 10000002;
			}
			float HitCompDebugArrowOffset = 0.0f;
			// Convert hit register direction
			switch (TriggerVolume->HitRegisterDirection) {
				case AnyDirection:
					NewFldHitbox->mHeroDirectType_ = FFldHitCoreHeroDirectType::None;
					break;
				case TowardsCenter:
					NewFldHitbox->mHeroDirectType_ = FFldHitCoreHeroDirectType::Center;
					break;
				case Right:
					NewFldHitbox->mHeroDirectType_ = FFldHitCoreHeroDirectType::Right;
					//HitCompDebugArrowOffset = 180.0f;
					HitCompDebugArrowOffset = 90.0f;
					break;
				case Front:
					NewFldHitbox->mHeroDirectType_ = FFldHitCoreHeroDirectType::Front;
					//HitCompDebugArrowOffset = 90.0f;
					break;
				case Left:
					NewFldHitbox->mHeroDirectType_ = FFldHitCoreHeroDirectType::Left;
					HitCompDebugArrowOffset = -90.0f;
					break;
				case Back:
					NewFldHitbox->mHeroDirectType_ = FFldHitCoreHeroDirectType::Back;
					//HitCompDebugArrowOffset = -90.0f;
					HitCompDebugArrowOffset = 180.0f;
					break;
			}
			NewFldHitbox->DirDebugComp_->AddRelativeRotation(FRotator(0, HitCompDebugArrowOffset, 0));
			// Convert prompt type
			switch (HitEntry->PromptType) {
				case EXAMINE_fldCheckName0:
				case EXAMINE_fldCheckName1:
				case EXAMINE_fldCheckName2:
				case EXAMINE_fldCheckName3:
				case EXAMINE_fldCheckName4:
					NewFldHitbox->mCheckIcon_ = EFldHitCoreCheckIconType::Check;
					break;
				case GO_Blank:
				case GO_fldPlaceName:
					NewFldHitbox->mCheckIcon_ = EFldHitCoreCheckIconType::Goto;
					break;
				case STEAL_fldCheckName:
				case ACTION_fldActionName0:
				case ACTION_fldActionName1:
				case ACTION_fldActionName2:
					NewFldHitbox->mCheckIcon_ = EFldHitCoreCheckIconType::Action;
					break;
				case TALK_fldNPCName:
					NewFldHitbox->mCheckIcon_ = EFldHitCoreCheckIconType::Speak;
					break;
				case SHOP_fldCheckName:
					NewFldHitbox->mCheckIcon_ = EFldHitCoreCheckIconType::Shop;
					break;
				default:
					NewFldHitbox->mCheckIcon_ = EFldHitCoreCheckIconType::None;
					break;
			}
			NewFldHitbox->mKeyPushBluePrint_ = Cast<UBlueprint>(BpInteractPlayAsset.GetAsset())->GeneratedClass;
		}
	}
	// Add entrances
	FFbnBlock* EntranceBlock = FbnData.FbnBlocks.FindByPredicate([](FFbnBlock& CurrBlock) { return CurrBlock.Type == EFbnListType::FBN_Entrance; });
	if (EntranceBlock) {
		for (int i = 0; i < EntranceBlock->BlockEntries.Num(); i++) {
			FFbnEntrance* Entrance = (FFbnEntrance*)EntranceBlock->BlockEntries[i];
			AFldPlayerStart* NewEntrance = Cast<AFldPlayerStart>(HitWorld->SpawnActor(AFldPlayerStart::StaticClass()));
			FString EntranceName = FString::Printf(TEXT("%s_FBN_Entrance%d"), *FBNBaseName, i);
			NewEntrance->Rename(*EntranceName);
			NewEntrance->SetActorLabel(EntranceName);
			NewEntrance->SetActorLocation(FVector(Entrance->Position.X, Entrance->Position.Z, Entrance->Position.Y + NewEntrance->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()));
			float EntranceDPDeg = FMath::Acos(Entrance->Rotation.X) * 180 / PI;
			float EntranceRot = Entrance->Rotation.Z > 0 ? EntranceDPDeg : 360 - EntranceDPDeg;
			NewEntrance->SetActorRotation(FRotator(0, EntranceRot, 0));
			NewEntrance->mIndex_ = Entrance->EntranceID;
			NewEntrance->CameraDir->SetRelativeLocation(NewEntrance->GetActorLocation());
		}
	}
	// Add interactable NPC data
	FFbnBlock* NpcBlock = FbnData.FbnBlocks.FindByPredicate([](FFbnBlock& CurrBlock) { return CurrBlock.Type == EFbnListType::FBN_Npc; });
	if (NpcBlock) {
		for (int i = 0; i < NpcBlock->BlockEntries.Num(); i++) {
			FFbnNpc* Npc = (FFbnNpc*)NpcBlock->BlockEntries[i];
			if (Npc->PathNodes.Num() == 0 || FldFntBin.FntBlocks.Find(Npc->FNT_ID) == nullptr) {
				continue;
			}
			// Check entry in FNT - we know that at least one entry exists, so check first one
			FFNTEntry* CurrentFntEntry = FldFntBin.FntBlocks.Find(Npc->FNT_ID)->GetData();
			FString CurrentNpcName = FldNpcName.Table.Data[CurrentFntEntry->npcTxtIdx];
			if (CurrentNpcName == TEXT("TEMP")) {
				continue; // At least until I find a way to hide the name...
			}

			AFldNpcActor* NpcActor = Cast<AFldNpcActor>(HitWorld->SpawnActor(AFldNpcActor::StaticClass()));
			FString NpcName = FString::Printf(TEXT("%s_FBN_NPC%d"), *FBNBaseName, i);
			NpcActor->Rename(*NpcName);
			NpcActor->SetActorLabel(NpcName);
			NpcActor->SetActorLocation(FVector(Npc->PathNodes[0].X, Npc->PathNodes[0].Z, Npc->PathNodes[0].Y));
			float ActorDPDeg = FMath::Acos(Npc->NPCRotation.X) * 180 / PI;
			float ActorRot = Npc->NPCRotation.Z > 0 ? ActorDPDeg : 360 - ActorDPDeg;
			NpcActor->SetActorRotation(FRotator(0, ActorRot, 0));
			NpcActor->mMajorID_ = 301;
			NpcActor->mMinorID_ = i;
			if (FName* TargetKinId = FldNpcNameToKinId.Find(CurrentNpcName)) {
				NpcActor->mNameIndex_ = FCString::Atoi(*TargetKinId->ToString().RightChop(4));
			}
			else {
				FFldNpcNameTableRow NewRow;
				NewRow.Name = CurrentNpcName;
				CurrentHighestNpcKinId++;
				FName NewKinId = FName(FString::Printf(TEXT("KIN_%08d"), CurrentHighestNpcKinId));
				FldNpcNametable->AddRow(NewKinId, NewRow);
				FldNpcNameToKinId.Add(FldNpcNametable->FindRow<FFldNpcNameTableRow>(NewKinId, TEXT(""))->Name, NewKinId);
				NpcActor->mNameIndex_ = CurrentHighestNpcKinId;
			}
			NpcActor->mCharaModelParam_[0].mMajorID = 14000;
			NpcActor->mCharaModelParam_[0].mFbnNumber = 301;

			NpcActor->mCharaBaseClass_ = Cast<UBlueprint>(FldNpcMainAsset.GetAsset())->GeneratedClass;
			NpcActor->mNpcBaseClass_= Cast<UBlueprint>(FldNpcMobAsset.GetAsset())->GeneratedClass;
			NpcActor->mKeyPushBluePrint_ = Cast<UBlueprint>(BpInteractPlayAsset.GetAsset())->GeneratedClass;
		}
	}
	UPackage::Save(HitWorld->GetPackage(), HitWorld, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(HitWorld->GetPackage()->GetPathName(), FPackageName::GetAssetPackageExtension()));


	// Add crowd data (CLT)
	if (FldClt.CrowdModels.Num() == 0) {
		return;
	}

	FString CrowdAssetPath = FPaths::Combine(DataContextObject->SelectedPaths[0].ToString(), TEXT("LV_F120_101_CrowdTarget"));
	Utilities.MakeIntoUnrealPath(CrowdAssetPath);
	UWorld* MobWorld = Cast<UWorld>(CreateAsset(CrowdAssetPath, UWorld::StaticClass(), LevelFactory, BlankCb));

	FString CrowdResrcPath = FPaths::Combine(DataContextObject->SelectedPaths[0].ToString(), TEXT("LV_F120_101_MobResrc"));
	Utilities.MakeIntoUnrealPath(CrowdResrcPath);
	UWorld* MobResrcWorld = Cast<UWorld>(CreateAsset(CrowdResrcPath, UWorld::StaticClass(), LevelFactory, BlankCb));

	for (int i = 0; i < FldClt.CrowdModels.Num(); i++) {
		if (FldClt.CrowdModels[i].spawnTime == 0.0f || FldClt.CrowdModels[i].spawnLimit == 0) {
			// Idle CLT entry, ignore this for now, we'll add Idle mob later
		}
		else {
			AFldCrowdWalkManager* CurrWalkManager = Cast<AFldCrowdWalkManager>(MobResrcWorld->SpawnActor(Cast<UBlueprint>(FldCrowdWalkManagerAsset.GetAsset())->GeneratedClass));
			FString WalkManagerName = FString::Printf(TEXT("%s_CLT_Walk%d"), *FBNBaseName, i);
			CurrWalkManager->Rename(*WalkManagerName);
			CurrWalkManager->SetActorLabel(WalkManagerName);
			FFldCrowdWalkRouteParam NewWalkRoute;
			NewWalkRoute.mRoutePattern_ = EFldCrowdRoutePtn::Normal;
			for (int j = 0; j < FldClt.CrowdModels[i].nodes.positions.Num(); j++) {
				int32 NodeId = (i + 1) * 100 + j + 1;
				FString CrowdTargetName = FString::Printf(TEXT("FldCrowdTarget%d"), NodeId);
				AFldCrowdTarget* NewCrowdTarget = Cast<AFldCrowdTarget>(MobWorld->SpawnActor(AFldCrowdTarget::StaticClass()));
				NewCrowdTarget->Rename(*CrowdTargetName);
				NewCrowdTarget->SetActorLabel(CrowdTargetName);
				FVector CurrNodePos = FldClt.CrowdModels[i].nodes.positions[j];
				NewCrowdTarget->SetActorLocation(FVector(CurrNodePos.X, CurrNodePos.Z, CurrNodePos.Y));
				NewCrowdTarget->mIndex_ = NodeId;
				NewWalkRoute.mPointList.Add(NodeId);
			}
			CurrWalkManager->mRouteParam_.Add(NewWalkRoute);
			CurrWalkManager->mMinTimer_ = FldClt.CrowdModels[i].spawnTime - (FldClt.CrowdModels[i].spawnTime * 0.1);
			CurrWalkManager->mMaxTimer_ = FldClt.CrowdModels[i].spawnTime + (FldClt.CrowdModels[i].spawnTime * 0.1);
			CurrWalkManager->mMobBpList_.Add(FFldCrowdWalkBpParam((TSubclassOf<AMobWalkCharaBaseCore>)((UBlueprint*)McWalkAsset.GetAsset())->GeneratedClass));
		}
	}
	UPackage::Save(MobWorld->GetPackage(), MobWorld, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(MobWorld->GetPackage()->GetPathName(), FPackageName::GetAssetPackageExtension()));
	UPackage::Save(MobResrcWorld->GetPackage(), MobResrcWorld, RF_Public | RF_Standalone, *FPackageName::LongPackageNameToFilename(MobResrcWorld->GetPackage()->GetPathName(), FPackageName::GetAssetPackageExtension()));
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

#undef LOCTEXT_NAMESPACE

IMPLEMENT_PRIMARY_GAME_MODULE(FXrd777RiriModule, xrd777, "xrd777" );