// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaPackFaceAnimTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtCharaPackFaceAnimTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaPackFaceAnimTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaPackFaceAnimTrackEditor(InSequencer));
}

FEvtCharaPackFaceAnimTrackEditor::FEvtCharaPackFaceAnimTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtCharaPackFaceAnimTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaPackFaceAnimTrack", "Atlus Event Character Pack Face Anim Track"),
		LOCTEXT("AddEvtCharaPackFaceAnimTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtCharaPackFaceAnimTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtCharaPackFaceAnimTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaPackFaceAnimationTrack::StaticClass());
}

const FSlateBrush* FEvtCharaPackFaceAnimTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtCharaPackFaceAnimationTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtCharaPackFaceAnimationTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtCharaPackFaceAnimationTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
