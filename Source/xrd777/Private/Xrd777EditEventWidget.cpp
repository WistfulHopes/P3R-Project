// (C)ATLUS. (C)SEGA.

#include "Xrd777EditEventWidget.h"
#include "CoreUObject/Public/UObject/UObjectGlobals.h"
#include "UObject/ReflectedTypeAccessors.h"

#define LOCTEXT_NAMESPACE "Xrd777EditEvent"

TSharedRef<SWidget> SXrd777EditEventWidget::DrawLoadNewEvent() {
	return SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
				.Text(LOCTEXT("Xrd777EditCreateEventCategory", "Category"))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextComboBox)
				.OptionsSource(&EventCategoryOptions)
				.InitiallySelectedItem(EventCategoryOptions[(int32)Data->Search->Category])
				.OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo) {
					UEnum* CurrEnum = StaticEnum<EAtlEvtEventCategoryType>();
					int32 Index = CurrEnum->GetValueByNameString(*NewSelection);
					if (Index != INDEX_NONE) {
						SearchSetCategory((EAtlEvtEventCategoryType)Index);
					}
				})
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
				.Text(LOCTEXT("Xrd777EditCreateEventMajor", "Major"))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SSpinBox<int32>)
				.MinValue(0)
				.MaxValue(999)
				.Delta(1)
				.Value_Lambda([this]() {
					return Data->Search->MajorId;
				})
				.OnValueChanged_Raw(this, &SXrd777EditEventWidget::SearchSetMajorId)
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
				.Text(LOCTEXT("Xrd777EditCreateEventMinor", "Minor"))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SSpinBox<int32>)
				.MinValue(0)
				.MaxValue(999)
				.Delta(1)
				.Value_Lambda([this]() {
					return Data->Search->MinorId;
				})
				.OnValueChanged_Raw(this, &SXrd777EditEventWidget::SearchSetMinorId)

		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
				.Text(LOCTEXT("Xrd777EditCreateEventRank", "Rank"))
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextComboBox)
				.OptionsSource(&EventRankOptions)
				.InitiallySelectedItem(EventRankOptions[(int32)Data->Search->Rank])
				.OnSelectionChanged_Lambda([this](TSharedPtr<FString> NewSelection, ESelectInfo::Type SelectInfo) {
					UEnum* CurrEnum = StaticEnum<EEventManagerEventRank>();
					FString* NewSelectionNoSpaces = new FString(*NewSelection);
					NewSelectionNoSpaces->RemoveSpacesInline();
					int32 Index = CurrEnum->GetValueByNameString(*NewSelectionNoSpaces);
					if (Index != INDEX_NONE) {
						SearchSetRank((EEventManagerEventRank)Index);
					}
				})
		]
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(FMargin(8, 0, 0, 0))
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
				.Text(LOCTEXT("Xrd77EditCreateEventLoad", "Load"))
				.OnClicked_Lambda([this]() {
					SetEventPath.Execute();
					ContentsBox.Get()->SetContent(DrawLoadedEventData());
					return FReply::Handled();
				})
		];
}

FText SXrd777EditEventWidget::GetCurrentEventPath() {
	if (Data->Current != nullptr) {
		return FText::FromString(FString::Printf(TEXT("Event Path: %s"), *Utilities.GetProjectPathForEvent(*Data->Current)));
	}
	else if (Data->SearchLastErrorMessage.Len() > 0) {
		return FText::FromString(Data->SearchLastErrorMessage);
	}
	else {
		return FText::FromString("No path currently selected");
	}
}

TSharedRef<SWidget> SXrd777EditEventWidget::GetObjectData(FText AssetLabel, UObject* InAsset) {
	TSharedRef<SWidget> AssetInfo = SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.FillWidth(1.0f)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(STextBlock)
				.Text(AssetLabel)
		]
		;
	if (InAsset != nullptr) {
		//return SNew(SHorizontalBox)
	}
	return AssetInfo;
}

TSharedRef<SWidget> SXrd777EditEventWidget::DrawLoadedEventData() {
	if (Data->Current == nullptr) {
		return SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			.AutoHeight()
			.Padding(FMargin(0, 8))
			[
				SNew(SSeparator)
			];
	}
	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.AutoHeight()
		.Padding(FMargin(0, 8))
		[
			SNew(SSeparator)
		]
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
						.Text(LOCTEXT("Xrd777EditEventSetChunkIdLabel", "Use Chunk ID for Assets: "))
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(8, 0, 0, 0))
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SSpinBox<int32>)
						.MinValue(0)
						.MaxValue(300)
						.Delta(1)
						.ToolTipText(LOCTEXT("Xrd777EditEventSetChunkIdTooltip", "Chunk ID to apply to event assets"))
						.Value_Lambda([this]() { return ApplyChunkID; })
						.OnValueChanged_Lambda([this](int32 NewValue) { ApplyChunkID = NewValue; })
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(8, 0, 0, 0))
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SButton)
						.Text(LOCTEXT("Xrd777EditEventSetChunkIdButton", "Set Chunk ID"))
				]
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0, 8))
		.AutoHeight()
		[
			GetObjectData(LOCTEXT("Xrd777EditEventLevelLabel", "Level"), Data->EvtLevel)
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0, 8))
		.AutoHeight()
		[
			GetObjectData(LOCTEXT("Xrd777EditEventSoundMainSequence", "Main Sequence"), Data->EvtMainSequence)
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0, 8))
		.AutoHeight()
		[
			GetObjectData(LOCTEXT("Xrd777EditEventSoundSoundSequence", "Sound Sequence"), Data->EvtAudioSequence)
		]
		+ SVerticalBox::Slot()
		.Padding(FMargin(0, 8))
		.AutoHeight()
		[
			GetObjectData(LOCTEXT("Xrd777EditEventScriptLabel", "Script"), Data->EvtFlowscript)
		]
		/*
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
						.Text(LOCTEXT("Xrd777EditEventScriptLabel", "Script"))
				]
				
				+ SHorizontalBox::Slot()
				.Padding(FMargin(8, 0, 0, 0))
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text_Lambda([this]() {
							return FText::FromString(Utilities.GetBfFilenameForEvent(*Data->Current, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath)));
						})
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(8, 0, 0, 0))
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SCheckBox)
						.ToolTipText(LOCTEXT("Xrd777EditEventScriptMakeTooltip", "Create an asset for this?"))
				]
		]
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
						.Text(LOCTEXT("Xrd777EditEventLevelLabel", "Level"))
				]

				+ SHorizontalBox::Slot()
				.Padding(FMargin(8, 0, 0, 0))
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
						.Text_Lambda([this]() {
							return FText::FromString(Utilities.GetLevelFilenameForEvent(*Data->Current, FConvertFilePath::CreateRaw(&Utilities, &FXrd777EditUtilities::MakeIntoUnrealPath)));
						})
				]
				+ SHorizontalBox::Slot()
				.Padding(FMargin(8, 0, 0, 0))
				.AutoWidth()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Center)
				[
					SNew(SCheckBox)
						.ToolTipText(LOCTEXT("Xrd777EditEventScriptMakeTooltip", "Create an asset for this?"))
				]
		]
		*/
		;
}

void SXrd777EditEventWidget::Construct(const FArguments& InArgs) {
	Data = InArgs._Data;
	SetEventPath = InArgs._OnSetEventPath;
	CreateAssetsTest = InArgs._OnCreateAssetsTest;

	UEnum* EvtRank = StaticEnum<EEventManagerEventRank>();
	for (int32 i = 0; i < EvtRank->NumEnums() - 1; i++) {
		EventRankOptions.Add(MakeShareable(new FString(EvtRank->GetDisplayNameTextByIndex(i).ToString())));
	}

	UEnum* EvtCategory = StaticEnum<EAtlEvtEventCategoryType>();
	for (int32 i = 0; i < EvtCategory->NumEnums() - 1; i++) {
		EventCategoryOptions.Add(MakeShareable(new FString(EvtCategory->GetDisplayNameTextByIndex(i).ToString())));
	}

	ChildSlot
		[
			SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					DrawLoadNewEvent()
				]
				+SVerticalBox::Slot()
				.Padding(FMargin(0, 8, 0, 0))
				.AutoHeight()
				[
					SNew(STextBlock)
						.Text_Lambda([this]() { return GetCurrentEventPath(); })
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SAssignNew(ContentsBox, SBox)
					[
						DrawLoadedEventData()
					]
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
						+ SHorizontalBox::Slot()
						.MaxWidth(200.0f)
						.HAlign(HAlign_Fill)
						.VAlign(VAlign_Center)
						[
							SNew(SButton)
								.Text(LOCTEXT("Xrd777EditEventScriptMakeAssets", "Make Event Assets TEST"))
								.OnClicked_Lambda([this]() {
									FXrd777EditEventParams* TestEvent = new FXrd777EditEventParams(EAtlEvtEventCategoryType::CMMU, 2, 120, EEventManagerEventRank::EventRankC);
									CreateAssetsTest.Execute(*TestEvent);
									return FReply::Handled();
								})
						]
				]
		];
}

#undef LOCTEXT_NAMESPACE