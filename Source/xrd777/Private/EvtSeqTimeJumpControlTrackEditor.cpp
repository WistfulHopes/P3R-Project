// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtSeqTimeJumpControlTrackEditor.h"
#include <xrd777/Public/MovieSceneEvtSeqTimeJumpControllerSection.h>
#include <xrd777/Public/MovieSceneEvtSeqTimeJumpControllerSectionTemplate.h>
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtSeqTimeJumpControlTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtSeqTimeJumpControlTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtSeqTimeJumpControlTrackEditor(InSequencer));
}

FEvtSeqTimeJumpControlTrackEditor::FEvtSeqTimeJumpControlTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods
FMovieSceneEvalTemplatePtr FEvtSeqTimeJumpControlTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtSeqTimeJumpControllerSectionTemplate(*CastChecked<UMovieSceneEvtSeqTimeJumpControllerSection>(&InSection));
}
/*
void FEvtSeqTimeJumpControlTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtSeqTimeJumpControlTrack", "Atlus Event Sequence Time Jump Control Track"),
		LOCTEXT("AddEvtSeqTimeJumpControlTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryCanExecute)
		)
	);
}
*/

void FEvtSeqTimeJumpControlTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
	FString AtlEventManagerName = FString(TEXT("BP_AtlEvtEventManager_C"));
	TArray<FGuid> AtlusEventManager = TArray<FGuid>();
	bool bIsAtlusEventManager = false;
	// check object binding list
	for (const FGuid Binding : ObjectBindings) {
		if (Binding.IsValid()) {
			UObject* BindingObject = GetSequencer()->FindSpawnedObjectOrTemplate(Binding);
			if (BindingObject != nullptr && BindingObject->GetClass()->GetName().Equals(AtlEventManagerName)) {
				bIsAtlusEventManager = true;
				AtlusEventManager.Add(Binding);
			}
		}
	}
	if (bIsAtlusEventManager) {
		MenuBuilder.AddMenuEntry(
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Evt Time Jump Controller"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] TODO: Description"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryExecute, AtlusEventManager),
				FCanExecuteAction::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryCanExecute)
			)
		);
	}
}

bool FEvtSeqTimeJumpControlTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtSeqTimeJumpControlTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtSeqTimeJumpControllerTrack::StaticClass());
}

const FSlateBrush* FEvtSeqTimeJumpControlTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtSeqTimeJumpControlTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtSeqTimeJumpControllerTrack* CastTrack = Cast<UMovieSceneEvtSeqTimeJumpControllerTrack>(Track);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtSeqTimeJumpControlTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtSeqTimeJumpControlTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtSeqTimeJumpControllerTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtSeqTimeJumpControllerTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

// Callbacks
/*
void FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}
}
*/

void FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtSeqTimeJumpControllerTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtSeqTimeJumpControllerTrack* NewObjectTrack = MovieScene->AddTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>(InObjectBindingId);
		NewTracks.Add(NewObjectTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewDialogSection = NewObjectTrack->CreateNewSection();
			check(NewDialogSection);
			NewObjectTrack->AddSection(*NewDialogSection);
			GetSequencer()->OnAddTrack(NewObjectTrack, InObjectBindingId);
		}
	}

	check(NewTracks.Num() != 0);
	for (UMovieSceneEvtSeqTimeJumpControllerTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Time Jump Controller"));
	}
}

bool FEvtSeqTimeJumpControlTrackEditor::HandleAddEvtSeqTimeJumpControlTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtSeqTimeJumpControllerTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
