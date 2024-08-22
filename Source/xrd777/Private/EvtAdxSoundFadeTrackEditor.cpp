// (C)ATLUS. (C)SEGA. :3

#if WITH_EDITORONLY_DATA // Crimes against hunanity

#pragma once

#include "EvtAdxSoundFadeTrackEditor.h"
#include "Core/Public/Math/RangeBound.h"
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtAdxSoundFadeTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtAdxSoundFadeTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtAdxSoundFadeTrackEditor(InSequencer));
}

FEvtAdxSoundFadeTrackEditor::FEvtAdxSoundFadeTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{

}
/*
TSharedRef<ISequencerSection> FEvtAdxSoundFadeTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) {
	return MakeShareable(new FEvtAdxSoundFadeSection(SectionObject));
}
*/

// Methods

void FEvtAdxSoundFadeTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtAdxSoundFadeTrack", "Atlus Event ADX Sound Fade Track"),
		LOCTEXT("AddEvtAdxSoundFadeTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtAdxSoundFadeTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true; // lol
}

bool FEvtAdxSoundFadeTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtAdxSoundFadeTrack::StaticClass());
}

const FSlateBrush* FEvtAdxSoundFadeTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtAdxSoundFadeTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	/*
	UMovieSceneEvtAdxSoundFadeTrack* CastTrack = Cast<UMovieSceneEvtAdxSoundFadeTrack>(Track);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtDialogueEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtAdxSoundFadeTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
	*/
}

void FEvtAdxSoundFadeTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtAdxSoundFadeTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtAdxSoundFadeTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}
// Callbacks

void FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundFadeTrack_Transaction", "P3RE Event ADX Sound Fade Track"));
	MovieScene->Modify();

	UMovieSceneEvtAdxSoundFadeTrack* NewTrack = MovieScene->AddMasterTrack<UMovieSceneEvtAdxSoundFadeTrack>();
	ensure(NewTrack);
	UMovieSceneSection* NewSection = NewTrack->CreateNewSection();
	NewTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(NewTrack, FGuid());
	}
}

bool FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif