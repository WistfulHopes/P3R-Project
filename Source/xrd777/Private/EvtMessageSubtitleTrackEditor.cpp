// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtMessageSubtitleTrackEditor.h"
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtMessageSubtitleTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtMessageSubtitleTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtMessageSubtitleTrackEditor(InSequencer));
}

FEvtMessageSubtitleTrackEditor::FEvtMessageSubtitleTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods
FMovieSceneEvalTemplatePtr FEvtMessageSubtitleTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtMessageSubtitleSectionTemplate(*CastChecked<UMovieSceneEvtMessageSubtitleSection>(&InSection));
}

void FEvtMessageSubtitleTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
	// only add this option for characters
	FString AtlEventManagerName = FString(TEXT("BP_AtlEvtEventManager_C"));
	TArray<FGuid> AtlusEventManager = TArray<FGuid>();
	//bool bIsAtlusEventManager = ObjectClass->GetName().Equals(AtlEventManagerName);
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
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Event Message Subtitles"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Add a track for event subtitles"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryExecute, AtlusEventManager),
				FCanExecuteAction::CreateRaw(this, &FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryCanExecute)
			)
		);
	}
}
bool FEvtMessageSubtitleTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtMessageSubtitleTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtMessageSubtitleTrack::StaticClass());
}

const FSlateBrush* FEvtMessageSubtitleTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtMessageSubtitleTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtMessageSubtitleTrack* CastTrack = Cast<UMovieSceneEvtMessageSubtitleTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtMessageSubtitleTrackEditor::SetEvtManagerBindingID, CastTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtMessageSubtitleTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtMessageSubtitleTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtMessageSubtitleTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtMessageSubtitleTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtMessageSubtitleTrackEditor::SetEvtManagerBindingID(UMovieSceneEvtMessageSubtitleTrack* Track) {
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

void FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtMessageSubtitleTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtMessageSubtitleTrack* NewTrack = MovieScene->AddTrack<UMovieSceneEvtMessageSubtitleTrack>(InObjectBindingId);
		NewTracks.Add(NewTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewSection = NewTrack->CreateNewSection();
			check(NewSection);
			NewTrack->AddSection(*NewSection);
			GetSequencer()->OnAddTrack(NewTrack, InObjectBindingId);
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
	for (UMovieSceneEvtMessageSubtitleTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Message Subtitle"));
		if (EvtManagerGuid.IsValid()) {
			NewTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
		}
	}
}

bool FEvtMessageSubtitleTrackEditor::HandleAddEvtMessageSubtitleTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif
