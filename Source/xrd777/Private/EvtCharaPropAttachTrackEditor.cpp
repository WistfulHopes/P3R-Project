// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaPropAttachTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtCharaPropAttachTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaPropAttachTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaPropAttachTrackEditor(InSequencer));
}

FEvtCharaPropAttachTrackEditor::FEvtCharaPropAttachTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtCharaPropAttachTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaPropAttachTrack", "Atlus Event Character Prop Attach Track"),
		LOCTEXT("AddEvtCharaPropAttachTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtCharaPropAttachTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtCharaPropAttachTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaPropAttachTrack::StaticClass());
}

const FSlateBrush* FEvtCharaPropAttachTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtCharaPropAttachTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtCharaPropAttachTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtCharaPropAttachTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
