// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA // Crimes against hunanity

#pragma once

#include "EvtCharaAnimTrackEditor.h"

#define LOCTEXT_NAMESPACE "FEvtCharaAnimTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaAnimTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaAnimTrackEditor(InSequencer));
}

FEvtCharaAnimTrackEditor::FEvtCharaAnimTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{

}
/*
TSharedRef<ISequencerSection> FEvtAdxSoundFadeTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) {
	return MakeShareable(new FEvtAdxSoundFadeSection(SectionObject));
}
*/

// Methods

void FEvtCharaAnimTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack", "Atlus Event Character Animation Track"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtCharaAnimTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	/*
	ETrackSupport TrackSupported = InSequence ? InSequence->IsTrackSupported(UMovieSceneEvtAdxSoundFadeTrack::StaticClass()) : ETrackSupport::NotSupported;
	return TrackSupported == ETrackSupport::Supported;
	*/
	//InSequence->IsA<
	return true; // lol
}

bool FEvtCharaAnimTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaAnimationTrack::StaticClass());
}

const FSlateBrush* FEvtCharaAnimTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtCharaAnimationTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtCharaAnimationTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}

bool FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtCharaAnimationTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif