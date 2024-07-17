// (C)ATLUS. (C)SEGA.


#include "Xrd777EditAssetListWidget.h"
#include "IAssetRegistry.h"

#define LOCTEXT_NAMESPACE "Xrd777EditAssetListWidget"

DEFINE_LOG_CATEGORY_STATIC(LogXrd777EditAssetList, Log, All);

void SXrd777EditAssetListWidget::Construct(const FArguments& InArgs) {
	List = InArgs._InList;
	bToggleMode = InArgs._InitToggleMode;
	CreateAsset = InArgs._CreateAsset;
	ChildSlot
		[
			SNew(SBox)
				.MaxDesiredHeight(200.0f)
				.MinDesiredWidth(500.0f)
				.MaxDesiredWidth(500.0f)
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				.Content()
				[
					SNew(SVerticalBox)
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()
								//.MaxWidth(100.0f)
								.AutoWidth()
								[
									SNew(SButton)
										.Text_Lambda([this]() {
											return bToggleMode 
												? LOCTEXT("Xrd777EditAssetListToggleOn", "Disable All") 
												: LOCTEXT("Xrd777EditAssetListToggleOn", "Enable All");
										})
										.OnClicked_Lambda([this]() {
											bToggleMode = !bToggleMode;
											for (TSharedRef<FXrd777EditAssetListEntry>& ModelEntry : *List) {
												ModelEntry.Get().UpdateCreateAssetToggle();
											}
											return FReply::Handled();
										})
										.IsEnabled_Lambda([this]() {
											return List->Num() > 0;
										})
								]
								+ SHorizontalBox::Slot()
								//.MaxWidth(100.0f)
								.AutoWidth()
								.Padding(FMargin(10, 0, 0, 0))
								[
									SNew(SButton)
										.Text(LOCTEXT("Xrd777EditAssetListCreateAssets", "Create Assets"))
										.OnClicked_Lambda([this]() {
											for (TSharedRef<FXrd777EditAssetListEntry>& ModelEntry : *List) {
												if (ModelEntry.Get().GetCreateAsset()) {
													CreateAsset.Execute(ModelEntry.Get());
												}
											}
											return FReply::Handled();
										})
										.IsEnabled_Lambda([this]() {
											return List->Num() > 0;
										})
								]
								+ SHorizontalBox::Slot()
								.Padding(FMargin(10, 0, 0, 0))
								.VAlign(VAlign_Center)
								.HAlign(HAlign_Right)
								.AutoWidth()
								[
									SNew(STextBlock)
										.Text_Lambda([this]() {
											return FText::FromString(FString::Printf(TEXT("%d assets"), List->Num()));
										})
								]
						]
						+ SVerticalBox::Slot()
						[
							SAssignNew(ListWidget, SListView<TSharedRef<FXrd777EditAssetListEntry>>)
								.ListItemsSource(List)
								.OnGenerateRow_Raw(this, &SXrd777EditAssetListWidget::MakeModelListItemWidget)
								.SelectionMode(ESelectionMode::Single)
								.HeaderRow(
									SNew(SHeaderRow)
									+ SHeaderRow::Column("Filepath")
									.FillWidth(1.0f)
									[
										SNew(SBorder)
											.Padding(5.0f)
											.Content()
											[
												SNew(STextBlock)
													.Text(LOCTEXT("Xrd777EditAssetListFilepathHeader", "Filepath"))
											]
									]
									+ SHeaderRow::Column("CreateAsset")
									.FillWidth(1.0f)
									[
										SNew(SBorder)
											.Padding(5.0f)
											.Content()
											[
												SNew(STextBlock)
													.Text(LOCTEXT("Xrd777EditAssetListCreateAssetCheckboxHeader", "Create Asset?"))
											]
									]
								)
						]
				]
		];
}

TSharedRef<ITableRow> SXrd777EditAssetListWidget::MakeModelListItemWidget(TSharedRef<FXrd777EditAssetListEntry> Item, const TSharedRef<STableViewBase>& InOwnerTable) {
	TSharedRef<ITableRow> NewRow =
		SNew(STableRow<TSharedPtr<FString>>, InOwnerTable)
		[
			SNew(SBorder)
				.Padding(5.0f)
				.Content()
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.MaxWidth(400.0f)
						.HAlign(HAlign_Left)
						.VAlign(VAlign_Center)
						[
							SNew(STextBlock)
								.Text(FText::FromString(Item->Path))
								.ToolTipText_Lambda([Item]() {
								return FText::FromString(Item->Path);
									})
						]
						+ SHorizontalBox::Slot()
						.AutoWidth()
						.HAlign(HAlign_Right)
						.VAlign(VAlign_Center)
						[
							SNew(SCheckBox)
								.IsChecked_Lambda([Item]() {
									return Item.Get().GetCreateAsset() ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
								})
								.IsEnabled_Lambda([Item]() {
									return !Item.Get().GetAlreadyExists();
								})
								.OnCheckStateChanged_Lambda([Item](ECheckBoxState NewState) {
									Item.Get().SetCreateAsset(NewState == ECheckBoxState::Checked);
								})
								.ToolTipText_Lambda([Item]() {
									if (Item.Get().GetAlreadyExists()) {
										return LOCTEXT("Xrd777EditAssetListItemExists", "This asset was already added into the Content Browser");
									}
									else {
										if (Item.Get().GetCreateAsset()) {
											return LOCTEXT("Xrd777EditAssetListItemExists", "This asset will be added to the Content Browser when Create Asset is selected");
										}
										else {
											return LOCTEXT("Xrd777EditAssetListItemExists", "This asset will be ignored when Create Asset is selected");
										}
									}
								})
						]
				]
		];
	return NewRow;
}

void SXrd777EditAssetListWidget::UpdateAssetList(FString& InGamePath, FString& InPath, FString& InWildcard, IAssetRegistry& InAssetRegistry) {
	List->Empty();
	if (!IFileManager::Get().DirectoryExists(*InPath)) {
		UE_LOG(LogXrd777EditAssetList, Display, TEXT("[TryGetEventData] Missing directory error: %s"), *InPath);
		return;
	}
	TArray<FString> FileNamesOut;
	IFileManager::Get().FindFilesRecursive(FileNamesOut, *InPath, *InWildcard, true, false, true);
	for (const FString& FileName : FileNamesOut) {
		FString FilenameGamePath = FileName.RightChop(InGamePath.Len());
		FString FilenameObjectPath = FilenameGamePath.LeftChop(FPaths::GetExtension(FilenameGamePath, false).Len()) + FPaths::GetBaseFilename(FilenameGamePath);
		bool bDoesAssetAlreadyExist = InAssetRegistry.GetAssetByObjectPath(*FilenameObjectPath).IsValid();
		List->Add(MakeShareable(new FXrd777EditAssetListEntry(FilenameGamePath, bDoesAssetAlreadyExist)));
	}
	// Update widgets
	ListWidget.Get()->RequestListRefresh();
	bToggleMode = true;
}

#undef LOCTEXT_NAMESPACE