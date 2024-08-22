// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA // Crimes against hunanity

#pragma once

#include "EvtAdxSoundManageTrackEditor.h"
#include "Core/Public/Math/RangeBound.h"
#include "EvtConditionBranchDetailsCustom.h"

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
	return true; // lol
}

bool FEvtAdxSoundManageTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtAdxSoundManageTrack::StaticClass());
}

const FSlateBrush* FEvtAdxSoundManageTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtAdxSoundManageTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	/*
	UMovieSceneEvtAdxSoundManageTrack* CastTrack = Cast<UMovieSceneEvtAdxSoundManageTrack>(Track);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtDialogueEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtAdxSoundManageTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
	*/
}

void FEvtAdxSoundManageTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtAdxSoundManageTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtAdxSoundManageTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

// Callbacks

void FEvtAdxSoundManageTrackEditor::HandleAddEvtAdxSoundManageTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	UMovieSceneEvtAdxSoundManageTrack* NewTrack = MovieScene->AddMasterTrack<UMovieSceneEvtAdxSoundManageTrack>();
	ensure(NewTrack);
	UMovieSceneSection* NewSection = NewTrack->CreateNewSection();
	NewTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(NewTrack, FGuid());
	}
}

bool FEvtAdxSoundManageTrackEditor::HandleAddEvtAdxSoundManageTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif
