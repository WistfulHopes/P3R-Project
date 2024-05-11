// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtFadeScreenTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtFadeScreenTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtFadeScreenTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtFadeScreenTrackEditor(InSequencer));
}

FEvtFadeScreenTrackEditor::FEvtFadeScreenTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtFadeScreenTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtFadeScreenTrack", "Atlus Event Fade Screen Track"),
		LOCTEXT("AddEvtFadeScreenTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtFadeScreenTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtFadeScreenTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtFadeScreenTrack::StaticClass());
}

const FSlateBrush* FEvtFadeScreenTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtFadeScreenTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtFadeScreenTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtFadeScreenTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
