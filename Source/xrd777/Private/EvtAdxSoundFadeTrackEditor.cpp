// (C)ATLUS. (C)SEGA. :3

#if WITH_EDITORONLY_DATA // Crimes against hunanity

#pragma once

#include "EvtAdxSoundFadeTrackEditor.h"
#include "Core/Public/Math/RangeBound.h"

#define LOCTEXT_NAMESPACE "FEvtAdxSoundFadeTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtAdxSoundFadeTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtAdxSoundFadeTrackEditor(InSequencer));
}

FEvtAdxSoundFadeTrackEditor::FEvtAdxSoundFadeTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{

}
/*
TSharedRef<ISequencerSection> FEvtAdxSoundFadeTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) {
	return MakeShareable(new FEvtAdxSoundFadeSection(SectionObject));
}
*/

// Methods

void FEvtAdxSoundFadeTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtAdxSoundFadeTrack", "Atlus Event ADX Sound Fade Track"),
		LOCTEXT("AddEvtAdxSoundFadeTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtAdxSoundFadeTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	/*
	ETrackSupport TrackSupported = InSequence ? InSequence->IsTrackSupported(UMovieSceneEvtAdxSoundFadeTrack::StaticClass()) : ETrackSupport::NotSupported;
	return TrackSupported == ETrackSupport::Supported;
	*/
	return true; // lol
}

bool FEvtAdxSoundFadeTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtAdxSoundFadeTrack::StaticClass());
}

const FSlateBrush* FEvtAdxSoundFadeTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	/*UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtAdxSoundFadeTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	*/
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundFadeTrack_Transaction", "P3RE Event ADX Sound Fade Track"));
	MovieScene->Modify();

	UMovieSceneEvtAdxSoundFadeTrack* NewTrack = MovieScene->AddMasterTrack<UMovieSceneEvtAdxSoundFadeTrack>();
	ensure(NewTrack);
	UMovieSceneSection* NewSection = NewTrack->CreateNewSection();
	/*
	if (NewSection->SectionRange.Value.HasLowerBound()) {
		NewSection->SectionRange.Value.SetLowerBound(TRangeBound<FFrameNumber>::Open());
	}
	if (NewSection->SectionRange.Value.HasUpperBound()) {
		NewSection->SectionRange.Value.SetUpperBound(TRangeBound<FFrameNumber>::Open());
	}
	*/
	NewTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(NewTrack, FGuid());
	}
	/*SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtAdxSoundFadeTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
	*/
}

bool FEvtAdxSoundFadeTrackEditor::HandleAddEvtAdxSoundFadeTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
	//return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtAdxSoundFadeTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif