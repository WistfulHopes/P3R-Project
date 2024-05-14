// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtDialogueTrackEditor.h"
#include <MovieSceneSequenceEditor.h>
#include "Logging/LogMacros.h"
#include "Sequencer/Public/SequencerSectionPainter.h"
#include "CommonMovieSceneTools.h"
//#include "Sequencer/Public/ISequencerSection.h"
#include "EvtConditionBranchDetailsCustom.h"
#include "IDetailsView.h"

#define LOCTEXT_NAMESPACE "FEvtDialogueTrackEditor"

DEFINE_LOG_CATEGORY_STATIC(LogEvtDialogueTrackEditor, Log, All);

class FDialogueSection : public FSequencerSection {
public:
	FDialogueSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer)
		: FSequencerSection(InSection)
		, WeakSequencer(InSequencer)
	{}

	// ISequencerSection interface
	//virtual bool RequestDeleteCategory(const TArray<FName>& CategoryNamePath) override;
	//virtual bool RequestDeleteKeyArea(const TArray<FName>& KeyAreaNamePath) override;

	virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override {
		int32 LayerId = Painter.PaintSectionBackground();
		// even though this isn't a keyfraem track (if atlus had done that it would've shown in the header dump), we'll still draw the message positions
		// for convenience
		const FSlateBrush* CircleMsgBrush = FEditorStyle::GetBrush("Sequencer.KeyCircle");
		const UMovieSceneEvtDialogueSection& DialogSection = *CastChecked<UMovieSceneEvtDialogueSection>(WeakSection);
		//const FMovieSceneEvtDialogueSectionData& DialogSectionEvents = DialogSection.EventData;

		FTimeToPixel TimeConverter = Painter.GetTimeConverter();
		FFrameRate TickResolution = TimeConverter.GetTickResolution();
		/*
		FSlateDrawElement::MakeText(
			Painter.DrawElements,
			Painter.LayerId + 1,
			Painter.SectionGeometry.ToPaintGeometry(),
			FText::Format(LOCTEXT("EvtDialogueTrackEditorDrawTest", "Test")),
			FStyleDefaults::GetFontInfo()
		);
		*/
		FSlateDrawElement::MakeBox(
			Painter.DrawElements,
			Painter.LayerId + 1,
			Painter.SectionGeometry.ToPaintGeometry(),
			FCoreStyle::Get().GetBrush("GenericWhiteBox"),
			ESlateDrawEffect::None,
			FLinearColor(0, 1, 0, 1)
		);

		/*
		TArray<TTuple<FFrameNumber&, FEvtDialoguePayload&>> TimesToValues = TArray<TTuple<FFrameNumber&, FEvtDialoguePayload&>>();
		if (DialogSection.EventData.GetTimes().Num() == DialogSection.EventData.GetValues().Num()) {

		}
		else {
			
		}
		*/
		// TODO: draw keyframes for events
		return LayerId + 1;
	}

private:
	// The sequencer controlling this section
	TWeakPtr<ISequencer> WeakSequencer;
};

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtDialogueTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtDialogueTrackEditor(InSequencer));
}
// Basic ctor

FEvtDialogueTrackEditor::FEvtDialogueTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}

// Keyframe ctor
/*
FEvtDialogueTrackEditor::FEvtDialogueTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FKeyframeTrackEditor<UMovieSceneEvtDialogueTrack>(InSequencer) {}
*/
// Methods

// Requires making MovieSceneEvtDialogueSection (also all Evt tracks only have one section)

TSharedRef<ISequencerSection> FEvtDialogueTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) {
	check(SupportsType(SectionObject.GetOuter()->GetClass()));
	return MakeShared<FDialogueSection>(SectionObject, GetSequencer());
}

FMovieSceneEvalTemplatePtr FEvtDialogueTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtDialogueSectionTemplate(*CastChecked<UMovieSceneEvtDialogueSection>(&InSection));
}

/* Dialogue tracks should be children of Atlus Event Manager
void FEvtDialogueTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtDialogueTrack", "Atlus Event Dialogue Track"),
		LOCTEXT("AddEvtDialogueTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryCanExecute)
		)
	);
}
*/

void FEvtDialogueTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
	// put dialog tracks in BP_AtlEvtEventManager_C bindings only
	// get selected object class
	
	FString AtlEventManagerName = FString(TEXT("BP_AtlEvtEventManager_C"));
	TArray<FGuid> AtlusEventManager = TArray<FGuid>();
	//bool bIsAtlusEventManager = ObjectClass->GetName().Equals(AtlEventManagerName);
	bool bIsAtlusEventManager = false;
	// check object binding list
	for (const FGuid Binding : ObjectBindings) {
		if (Binding.IsValid()) {
			UObject* BindingObject = GetSequencer()->FindSpawnedObjectOrTemplate(Binding);
			if (BindingObject != nullptr && BindingObject->GetClass()->GetName().Equals(AtlEventManagerName)) {
				bIsAtlusEventManager = true;
				AtlusEventManager.Add(Binding);
			}
		}
	}
	if (bIsAtlusEventManager) {
		MenuBuilder.AddMenuEntry(
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "Event Dialog"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Add a track to trigger BMD message entries"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryExecute, AtlusEventManager),
				FCanExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryCanExecute)
			)
		);
	}
}

void FEvtDialogueTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtDialogueTrack* DialogTrack = Cast<UMovieSceneEvtDialogueTrack>(Track);
	/*
	auto EvtConditionalBranchDelegate = [](FMenuBuilder& InnerMenuBuilder) {
		InnerMenuBuilder.AddWidget(
			SNew(SBox)
			.WidthOverride(200.0f)
			.HeightOverride(200.0f)
			.Padding(FMargin(5.0f, 5.0f))
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("Conditional Branch WIP (Slot 1)")))
				]
				+ SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				[
					SNew(STextBlock).Text(FText::FromString(TEXT("Conditional Branch WIP (Slot 2)")))
				]
			],
			FText::GetEmpty(), true, false
		);
	};
	*/
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtDialogueEditConditionalBrach", "Conditional Data"), 
		FText(), 
		//FNewMenuDelegate::CreateLambda(EvtConditionalBranchDelegate),
		FNewMenuDelegate::CreateRaw(this, &FEvtDialogueTrackEditor::BuildEventConditionalBranchMenu, DialogTrack),
		false,
		FSlateIcon());
}

void FEvtDialogueTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtDialogueTrack* DialogTrack) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtDialogueTrack::StaticClass(), 
		FOnGetDetailCustomizationInstance::CreateLambda([DialogTrack] { return FEvtConditionBranchDetailsCustom::MakeInstance(*DialogTrack); })
	);
	DetailsView->SetObject(DialogTrack);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtDialogueTrackEditor::OnTestButtonExecute(UMovieSceneEvtDialogueTrack* Track) {
	
}

bool FEvtDialogueTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtDialogueTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtDialogueTrack::StaticClass());
}

const FSlateBrush* FEvtDialogueTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtDialogueTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtDialogueTrack* NewDialogObjectTrack = MovieScene->AddTrack<UMovieSceneEvtDialogueTrack>(InObjectBindingId);
		NewTracks.Add(NewDialogObjectTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewDialogSection = NewDialogObjectTrack->CreateNewSection();
			check(NewDialogSection);
			NewDialogObjectTrack->AddSection(*NewDialogSection);
			GetSequencer()->OnAddTrack(NewDialogObjectTrack, InObjectBindingId);
		}
	}

	check(NewTracks.Num() != 0);
	for (UMovieSceneEvtDialogueTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Dialog"));
	}
}

bool FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif
