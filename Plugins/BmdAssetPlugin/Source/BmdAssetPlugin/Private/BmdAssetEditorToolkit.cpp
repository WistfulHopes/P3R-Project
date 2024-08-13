// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "BmdAssetEditorToolkit.h"

void FBmdAssetEditorToolkit::InitEditor(const TArray<UObject*>& InObjects) {
	Asset = Cast<UBmdAsset>(InObjects[0]);
	bCurrentBmdDataLoaded = false;
	if (Asset && Asset->mBuf.Num() > 0) {
		LoadTargetBmd();
	}
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("BmdAssetEditorLayout")
		->AddArea(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.15f)
				->AddTab("BmdAssetEditorSetFile", ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.85f)
				->AddTab("BmdAssetEditorPreview", ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
		);
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone, {}, "BmdAssetEditor", Layout, true, true, InObjects);
}

void FBmdAssetEditorToolkit::LoadTargetBmd() {
	TArrayView<const uint8> BufData = TArrayView<const uint8>((const uint8*)Asset->mBuf.GetData(), Asset->mBuf.Num());
	FMemoryReaderView BufReader = FMemoryReaderView(BufData);
	BufReader << CurrentBmdData;
	bCurrentBmdDataLoaded = true;
}

void FBmdAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) {
	FAssetEditorToolkit::RegisterTabSpawners(TabManager);
	TSharedRef<FWorkspaceItem> WorkspaceCategory = TabManager->AddLocalWorkspaceMenuCategory(GetBaseToolkitName());
	TabManager->RegisterTabSpawner("BmdAssetEditorPreview", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& InArgs) {
		TSharedRef<SWidget> DockTabContent = SNew(STextBlock).Text(INVTEXT("The selected BMD file is empty"));
		if (bCurrentBmdDataLoaded) {
			DockTabContent = CreateBmdDialogList();
		}
		SAssignNew(DialogListBox, SBox)
			[
				DockTabContent
			];
		TSharedRef<SDockTab> DockTab = SNew(SDockTab)
			[
				DialogListBox.ToSharedRef()
			];
		return DockTab;
		}))
		.SetDisplayName(INVTEXT("Preview"))
		.SetGroup(WorkspaceCategory)
	;
	TabManager->RegisterTabSpawner("BmdAssetEditorSetFile", FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs& InArgs) {
		return SNew(SDockTab)
			[
				CreateSetFileSection()
			];
		}))
		.SetDisplayName(INVTEXT("Watch File"))
		.SetGroup(WorkspaceCategory)
	;
}

TSharedRef<SWidget> FBmdAssetEditorToolkit::CreateSetFileSection() {
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(0, 0, 0, 10)
		[
			SNew(SRichTextBlock)
				//.Text(FText::FromString(TEXT("<BmdText.Bold>NOTE:</> The data for this asset is read only in the editor. To edit this, find the matching BMD file and edit that using Atlus Script Compiler. This will be updated whenever the file is compiled.")))
				.Text(FText::FromString(TEXT("<BmdText.Bold>NOTE:</> The data for this asset is read only in the editor. To edit this, find the matching BMD file and edit that using Atlus Script Compiler. This will be updated whenver you click on \"Update Asset\"")))
				.TextStyle(FBmdAssetStyle::Get(), "BmdText.Style")
				.DecoratorStyleSet(&FBmdAssetStyle::Get())
				.Justification(ETextJustify::Left)
		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.Padding(0, 0, 0, 10)
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SRichTextBlock)
						.Text_Lambda([this]() {
						return FText::FromString(FString::Printf(TEXT("File Path: <BmdText.Bold>%s</> "), *Asset->SyncToBmdFile));
							})
						.TextStyle(FBmdAssetStyle::Get(), "BmdText.Style")
								.DecoratorStyleSet(&FBmdAssetStyle::Get())
								.Justification(ETextJustify::Left)
				]
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(15, 0, 0, 0)
				[
					SNew(SButton)
						.Text(INVTEXT("Change Path"))
						.OnClicked_Lambda([this]() {
						SetSyncFile();
						return FReply::Handled();
							})
				]

		]
		+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Fill)
		.Padding(0, 0, 0, 10)
		[
			SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SButton)
						.Text(INVTEXT("Update Asset"))
						.OnClicked_Lambda([this]() {
						UpdateAssetBySyncFile();
						return FReply::Handled();
							})
				]
		];
}

TSharedRef<SWidget> FBmdAssetEditorToolkit::CreateBmdDialogList() {
	TSharedRef<SScrollBox> DialogList = SNew(SScrollBox);
	TArray<FString> DialogKeys;
	CurrentBmdData.Dialogs.GetKeys(DialogKeys);
	for (FString& DialogKey : DialogKeys) {
		TSharedRef<BmdDialogBase>* DialogValueRef = CurrentBmdData.Dialogs.Find(DialogKey);
		if (DialogValueRef) {
			BmdDialogBase& DialogValue = DialogValueRef->Get();
			TSharedRef<SVerticalBox> MessageListPerPage = SNew(SVerticalBox);
			for (TArray<TSharedPtr<BmdTokenBase>>& Page : DialogValue.Pages) {
				FString PageOutput;
				for (TSharedPtr<BmdTokenBase>& PageTokenRef : Page) {
					PageOutput += PageTokenRef.Get()->PrintValue().Replace(TEXT("\n"), TEXT(" "), ESearchCase::IgnoreCase);
				}
				MessageListPerPage.Get().AddSlot()
					.AutoHeight()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Fill)
					[
						SNew(STextBlock)
							.Text(FText::FromString(PageOutput))
					];
			}
			FString SpeakerName = TEXT("");
			if (DialogValue.DialogKind == BmdBinaryDialogKind::Message) {
				if (FString* SpeakerMaybe = ((BmdDialogMessage*)(&DialogValue))->Speaker) {
					SpeakerName = *SpeakerMaybe;
				}
			}
			DialogList.Get().AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.Padding(0, 10)
				[
					SNew(SBorder)
						.BorderImage(FEditorStyle::GetNoBrush())
						[
							SNew(SVerticalBox)
								+ SVerticalBox::Slot()
								.AutoHeight()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.Padding(0, 0, 15, 0)
								[
									SNew(SRichTextBlock)
										.Text(FText::FromString(FString::Printf(TEXT("<BmdText.DialogName>%s</> <BmdText.SpeakerName>%s</>"), *DialogKey, *SpeakerName)))
										.TextStyle(FBmdAssetStyle::Get(), "BmdText.Style")
										.DecoratorStyleSet(&FBmdAssetStyle::Get())
										.Justification(ETextJustify::Left)
								]
								+ SVerticalBox::Slot()
								.AutoHeight()
								.HAlign(HAlign_Fill)
								.VAlign(VAlign_Fill)
								.Padding(0, 0, 15, 0)
								[
									MessageListPerPage
								]
						]
				]
				;
		}
	}
	return DialogList;
}

void FBmdAssetEditorToolkit::SetSyncFile() {
	void* ParentWindowHandle = FSlateApplication::Get().FindBestParentWindowForDialogs(nullptr).Get()->GetNativeWindow()->GetOSWindowHandle();
	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		FString DialogTitle = TEXT("Select the target BMD file");
		FString StartDirectory = FEditorDirectories::Get().GetLastDirectory(ELastDirectory::GENERIC_IMPORT);
		FString DialogFileTypes = TEXT("Atlus Message Script|*.bmd|");
		TArray<FString> OutFileNames;
		if (DesktopPlatform->OpenFileDialog(ParentWindowHandle, DialogTitle, StartDirectory, FString(""), DialogFileTypes, 0, OutFileNames)) {
			Asset->SyncToBmdFile = FPaths::ConvertRelativePathToFull(OutFileNames[0]);
			Asset->MarkPackageDirty();
		}
	}
}

void FBmdAssetEditorToolkit::UpdateAssetBySyncFile() {
	if (Asset && !Asset->SyncToBmdFile.IsEmpty() && IFileManager::Get().FileExists(*Asset->SyncToBmdFile)) {
		TArray<uint8> FileData;
		FFileHelper::LoadFileToArray(FileData, *Asset->SyncToBmdFile);
		Asset->mBuf = (TArray<int8>)FileData;
		Asset->MarkPackageDirty();
		LoadTargetBmd();
		DialogListBox.Get()->SetContent(CreateBmdDialogList());
	}
}

void FBmdAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TabManager) {
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);
}

#endif