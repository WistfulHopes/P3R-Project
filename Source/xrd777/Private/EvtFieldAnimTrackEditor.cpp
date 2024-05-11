// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtFieldAnimTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtFieldAnimTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtFieldAnimTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtFieldAnimTrackEditor(InSequencer));
}

FEvtFieldAnimTrackEditor::FEvtFieldAnimTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtFieldAnimTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtFieldAnimTrack", "Atlus Event Field Animation Track"),
		LOCTEXT("AddEvtFieldAnimTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtFieldAnimTrackEditor::HandleAddEvtFieldAnimTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtFieldAnimTrackEditor::HandleAddEvtFieldAnimTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtFieldAnimTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtFieldAnimTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtFieldAnimationTrack::StaticClass());
}

const FSlateBrush* FEvtFieldAnimTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtFieldAnimTrackEditor::HandleAddEvtFieldAnimTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtFieldAnimationTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtFieldAnimationTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtFieldAnimTrackEditor::HandleAddEvtFieldAnimTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtFieldAnimationTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
