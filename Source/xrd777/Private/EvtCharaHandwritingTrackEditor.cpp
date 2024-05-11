// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaHandwritingTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtCharaHandwritingTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaHandwritingTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaHandwritingTrackEditor(InSequencer));
}

FEvtCharaHandwritingTrackEditor::FEvtCharaHandwritingTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtCharaHandwritingTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaHandwritingTrack", "Atlus Event Character Handwriting Track"),
		LOCTEXT("AddEvtCharaHandwritingTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaHandwritingTrackEditor::HandleAddEvtCharaHandwritingTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtCharaHandwritingTrackEditor::HandleAddEvtCharaHandwritingTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtCharaHandwritingTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtCharaHandwritingTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaHandwritingTrack::StaticClass());
}

const FSlateBrush* FEvtCharaHandwritingTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtCharaHandwritingTrackEditor::HandleAddEvtCharaHandwritingTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtCharaHandwritingTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtCharaHandwritingTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtCharaHandwritingTrackEditor::HandleAddEvtCharaHandwritingTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtCharaHandwritingTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
