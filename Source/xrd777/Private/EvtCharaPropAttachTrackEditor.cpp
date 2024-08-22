// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaPropAttachTrackEditor.h"
#include <CharacterBase/Public/CharacterBaseCore.h>
#include <CharacterBase/Public/NpcBaseCore.h>
#include <Xrd777/Public/AppPropsCore.h>
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtCharaPropAttachTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaPropAttachTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaPropAttachTrackEditor(InSequencer));
}

FEvtCharaPropAttachTrackEditor::FEvtCharaPropAttachTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods
FMovieSceneEvalTemplatePtr FEvtCharaPropAttachTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtCharaPropAttachSectionTemplate(*CastChecked<UMovieSceneEvtCharaPropAttachSection>(&InSection));
}

void FEvtCharaPropAttachTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
	// only add this option for characters
	TArray<FGuid> EvtCharacters = TArray<FGuid>();
	bool bIsEvtCharacter = false;
	// check object binding list
	for (const FGuid Binding : ObjectBindings) {
		if (Binding.IsValid()) {
			UObject* BindingObject = GetSequencer()->FindSpawnedObjectOrTemplate(Binding);
			if (BindingObject != nullptr &&
				(
					BindingObject->IsA(ACharacterBaseCore::StaticClass()) ||
					BindingObject->IsA(ANpcBaseCore::StaticClass()) ||
					BindingObject->IsA(AAppPropsCore::StaticClass())
					)) {
				bIsEvtCharacter = true;
				EvtCharacters.Add(Binding);
			}
		}
	}
	if (bIsEvtCharacter) {
		MenuBuilder.AddMenuEntry(
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Character Prop Attach"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Add a track to attach a prop to a character"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryExecute, EvtCharacters),
				FCanExecuteAction::CreateRaw(this, &FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryCanExecute)
			)
		);
	}
}

bool FEvtCharaPropAttachTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtCharaPropAttachTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaPropAttachTrack::StaticClass());
}

const FSlateBrush* FEvtCharaPropAttachTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtCharaPropAttachTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtCharaPropAttachTrack* CastTrack = Cast<UMovieSceneEvtCharaPropAttachTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaPropAttachTrackEditor::SetEvtManagerBindingID, CastTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtCharaPropAttachTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtCharaPropAttachTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtCharaPropAttachTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtCharaPropAttachTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtCharaPropAttachTrackEditor::SetEvtManagerBindingID(UMovieSceneEvtCharaPropAttachTrack* Track) {
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

void FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtCharaPropAttachTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtCharaPropAttachTrack* NewTrack = MovieScene->AddTrack<UMovieSceneEvtCharaPropAttachTrack>(InObjectBindingId);
		NewTracks.Add(NewTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewDialogSection = NewTrack->CreateNewSection();
			check(NewDialogSection);
			NewTrack->AddSection(*NewDialogSection);
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
	for (UMovieSceneEvtCharaPropAttachTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Chara Prop Attach"));
		if (EvtManagerGuid.IsValid()) {
			NewTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
		}
	}
}

bool FEvtCharaPropAttachTrackEditor::HandleAddEvtCharaPropAttachTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif
