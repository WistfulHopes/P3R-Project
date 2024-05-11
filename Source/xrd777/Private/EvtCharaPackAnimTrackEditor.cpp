// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaPackAnimTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtCharaPackAnimTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaPackAnimTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaPackAnimTrackEditor(InSequencer));
}

FEvtCharaPackAnimTrackEditor::FEvtCharaPackAnimTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtCharaPackAnimTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaPackAnimTrack", "Atlus Event Character Pack Anim Track"),
		LOCTEXT("AddEvtCharaPackAnimTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaPackAnimTrackEditor::HandleAddEvtPackAnimTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtCharaPackAnimTrackEditor::HandleAddEvtPackAnimTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtCharaPackAnimTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtCharaPackAnimTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaPackAnimationTrack::StaticClass());
}

const FSlateBrush* FEvtCharaPackAnimTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtCharaPackAnimTrackEditor::HandleAddEvtPackAnimTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtCharaPackAnimationTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtCharaPackAnimationTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtCharaPackAnimTrackEditor::HandleAddEvtPackAnimTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtCharaPackAnimationTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
