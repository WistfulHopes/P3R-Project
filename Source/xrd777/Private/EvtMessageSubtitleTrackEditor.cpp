// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtMessageSubtitleTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtMessageSubtitleTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtMessageSubtitleTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtMessageSubtitleTrackEditor(InSequencer));
}

FEvtMessageSubtitleTrackEditor::FEvtMessageSubtitleTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtMessageSubtitleTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtMessageSubtitleTrack", "Atlus Event Message Subtitle Track"),
		LOCTEXT("AddEvtMessageSubtitleTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtMessageSubtitleTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtMessageSubtitleTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtMessageSubtitleTrack::StaticClass());
}

const FSlateBrush* FEvtMessageSubtitleTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtMessageSubtitleTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtMessageSubtitleTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtMessageSubtitleTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
