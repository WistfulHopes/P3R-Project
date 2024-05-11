// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtDialogueOptionsTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtDialogueOptionsTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtDialogueOptionsTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtDialogueOptionsTrackEditor(InSequencer));
}

FEvtDialogueOptionsTrackEditor::FEvtDialogueOptionsTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtDialogueOptionsTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtDialgoueOptionsTrack", "Atlus Event Dialogue Options Track"),
		LOCTEXT("AddEvtDialgoueOptionsTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtDialogueOptionsTrackEditor::HandleAddEvtDialogueOptionsTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtDialogueOptionsTrackEditor::HandleAddEvtDialogueOptionsTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtDialogueOptionsTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtDialogueOptionsTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtDialogueOptionsTrack::StaticClass());
}

const FSlateBrush* FEvtDialogueOptionsTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtDialogueOptionsTrackEditor::HandleAddEvtDialogueOptionsTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtDialogueOptionsTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtDialogueOptionsTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtDialogueOptionsTrackEditor::HandleAddEvtDialogueOptionsTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtDialogueOptionsTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
