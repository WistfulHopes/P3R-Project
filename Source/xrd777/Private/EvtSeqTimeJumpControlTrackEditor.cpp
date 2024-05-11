// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtSeqTimeJumpControlTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtSeqTimeJumpControlTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtSeqTimeJumpControlTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtSeqTimeJumpControlTrackEditor(InSequencer));
}

FEvtSeqTimeJumpControlTrackEditor::FEvtSeqTimeJumpControlTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtSeqTimeJumpControlTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtSeqTimeJumpControlTrack", "Atlus Event Sequence Time Jump Control Track"),
		LOCTEXT("AddEvtSeqTimeJumpControlTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtSeqTimeJumpControlTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtSeqTimeJumpControlTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtSeqTimeJumpControllerTrack::StaticClass());
}

const FSlateBrush* FEvtSeqTimeJumpControlTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
