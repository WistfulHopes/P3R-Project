// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA // Crimes against hunanity

#pragma once

#include "EvtAdxSoundManageTrackEditor.h"
#include "Core/Public/Math/RangeBound.h"

#define LOCTEXT_NAMESPACE "FEvtAdxSoundManageTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtAdxSoundManageTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtAdxSoundManageTrackEditor(InSequencer));
}

FEvtAdxSoundManageTrackEditor::FEvtAdxSoundManageTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{

}
/*
TSharedRef<ISequencerSection> FEvtAdxSoundFadeTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) {
	return MakeShareable(new FEvtAdxSoundFadeSection(SectionObject));
}
*/

// Methods

void FEvtAdxSoundManageTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtAdxSoundManageTrack", "Atlus Event ADX Sound Manage Track"),
		LOCTEXT("AddEvtAdxSoundManageTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtAdxSoundManageTrackEditor::HandleAddEvtAdxSoundManageTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtAdxSoundManageTrackEditor::HandleAddEvtAdxSoundManageTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtAdxSoundManageTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	/*
	ETrackSupport TrackSupported = InSequence ? InSequence->IsTrackSupported(UMovieSceneEvtAdxSoundFadeTrack::StaticClass()) : ETrackSupport::NotSupported;
	return TrackSupported == ETrackSupport::Supported;
	*/
	//InSequence->IsA<
	return true; // lol
}

bool FEvtAdxSoundManageTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtAdxSoundManageTrack::StaticClass());
}

const FSlateBrush* FEvtAdxSoundManageTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtAdxSoundManageTrackEditor::HandleAddEvtAdxSoundManageTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	/*UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtAdxSoundManageTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	*/
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	UMovieSceneEvtAdxSoundManageTrack* NewTrack = MovieScene->AddMasterTrack<UMovieSceneEvtAdxSoundManageTrack>();
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
	/*SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtAdxSoundManageTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
	*/
}

bool FEvtAdxSoundManageTrackEditor::HandleAddEvtAdxSoundManageTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
	//return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtAdxSoundManageTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
