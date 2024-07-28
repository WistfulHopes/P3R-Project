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
				LOCTEXT("Xrd777EditAddLevelFromJson", "[P3RE] Add Level from JSON"),
				LOCTEXT("Xrd777EditAddLevelFromJsonTooltip", "TODO: Tooltip"),
				//FSlateIcon(FEditorStyle::GetStyleSetName(), ),
				FSlateIcon(),
				FUIAction(
					FExecuteAction::CreateLambda([this, DataContextObject]() { OnImportLevelFromJson(DataContextObject); })
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

#undef LOCTEXT_NAMESPACE

IMPLEMENT_PRIMARY_GAME_MODULE(FXrd777RiriModule, xrd777, "xrd777" );