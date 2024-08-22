// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtSeqControlTrackEditor.h"
#include <xrd777/Public/MovieSceneEvtSeqControllerSection.h>
#include <xrd777/Public/MovieSceneEvtSeqControllerSectionTemplate.h>
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtSeqControlTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtSeqControlTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtSeqControlTrackEditor(InSequencer));
}

FEvtSeqControlTrackEditor::FEvtSeqControlTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}

FMovieSceneEvalTemplatePtr FEvtSeqControlTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtSeqControllerSectionTemplate(*CastChecked<UMovieSceneEvtSeqControllerSection>(&InSection));
}

void FEvtSeqControlTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
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
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Evt Sequence Controller"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] TODO: Description"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryExecute, AtlusEventManager),
				FCanExecuteAction::CreateRaw(this, &FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryCanExecute)
			)
		);
	}
}

// Methods
bool FEvtSeqControlTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtSeqControlTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtSeqControllerTrack::StaticClass());
}

const FSlateBrush* FEvtSeqControlTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtSeqControlTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtSeqControllerTrack* CastTrack = Cast<UMovieSceneEvtSeqControllerTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtSeqControlTrackEditor::SetEvtManagerBindingID, CastTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtSeqControlTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtSeqControlTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtSeqControllerTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtSeqControllerTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtSeqControlTrackEditor::SetEvtManagerBindingID(UMovieSceneEvtSeqControllerTrack* Track) {
	UMovieScene* CurrMovieScene = GetFocusedMovieScene();
	FGuid EvtManagerGuid;
	for (int i = 0; i < CurrMovieScene->GetPossessableCount(); i++) {
		auto CurrPossessable = CurrMovieScene->GetPossessable(i);
		if (CurrPossessable.GetPossessedObjectClass()->GetDefaultObject()->IsA<AAtlEvtEventManager>()) {
			EvtManagerGuid = CurrPossessable.GetGuid();
		}
	}
	if (EvtManagerGuid.IsValid()) {
		Track->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
	}
	CurrMovieScene->MarkPackageDirty();
}

// Callbacks

void FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtSeqControllerTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtSeqControllerTrack* NewObjectTrack = MovieScene->AddTrack<UMovieSceneEvtSeqControllerTrack>(InObjectBindingId);
		NewTracks.Add(NewObjectTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewDialogSection = NewObjectTrack->CreateNewSection();
			check(NewDialogSection);
			NewObjectTrack->AddSection(*NewDialogSection);
			GetSequencer()->OnAddTrack(NewObjectTrack, InObjectBindingId);
		}
	}

	check(NewTracks.Num() != 0);
	// look for event manager
	FGuid EvtManagerGuid;
	for (int i = 0; i < MovieScene->GetPossessableCount(); i++) {
		auto CurrPossessable = MovieScene->GetPossessable(i);
		if (CurrPossessable.GetPossessedObjectClass()->GetDefaultObject()->IsA<AAtlEvtEventManager>()) {
			EvtManagerGuid = CurrPossessable.GetGuid();
		}
	}
	for (UMovieSceneEvtSeqControllerTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Sequence Controller"));
		if (EvtManagerGuid.IsValid()) {
			NewTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
		}
	}
}

bool FEvtSeqControlTrackEditor::HandleAddEvtSeqControlTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtSeqControllerTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
