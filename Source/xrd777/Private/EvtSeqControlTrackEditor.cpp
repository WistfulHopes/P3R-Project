// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtSeqControlTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtSeqControlTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtSeqControlTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtSeqControlTrackEditor(InSequencer));
}

FEvtSeqControlTrackEditor::FEvtSeqControlTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtSeqControlTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtSeqControlTrack", "Atlus Event Sequence Control Track"),
		LOCTEXT("AddEvtSeqControlTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtSeqControlTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtSeqControlTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtSeqControllerTrack::StaticClass());
}

const FSlateBrush* FEvtSeqControlTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtSeqControllerTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtSeqControllerTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtSeqControllerTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
