// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaOpControlTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtCharaOpControlTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaOpControlTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaOpControlTrackEditor(InSequencer));
}

FEvtCharaOpControlTrackEditor::FEvtCharaOpControlTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtCharaOpControlTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaOperationControllerTrack", "Atlus Event Character Operation Controller Track"),
		LOCTEXT("AddEvtCharaOperationControllerTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaOpControlTrackEditor::HandleAddEvtCharaOpControlTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtCharaOpControlTrackEditor::HandleAddEvtCharaOpControlTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtCharaOpControlTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtCharaOpControlTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaOperationControllerTrack::StaticClass());
}

const FSlateBrush* FEvtCharaOpControlTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtCharaOpControlTrackEditor::HandleAddEvtCharaOpControlTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtCharaOperationControllerTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtCharaOperationControllerTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtCharaOpControlTrackEditor::HandleAddEvtCharaOpControlTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtCharaOperationControllerTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif