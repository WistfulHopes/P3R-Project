// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA // Crimes against hunanity

#pragma once

#include "EvtCharaAnimTrackEditor.h"
#include <MovieSceneSequenceEditor.h>
#include <CharacterBase/Public/CharacterBaseCore.h>
#include <CharacterBase/Public/NpcBaseCore.h>
#include <Xrd777/Public/AppPropsCore.h>
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtCharaAnimTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaAnimTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaAnimTrackEditor(InSequencer));
}

FEvtCharaAnimTrackEditor::FEvtCharaAnimTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer)
{

}

FMovieSceneEvalTemplatePtr FEvtCharaAnimTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtCharaAnimationSectionTemplate(*CastChecked<UMovieSceneEvtCharaAnimationSection>(&InSection));
}

void FEvtCharaAnimTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
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
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Character Anim"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Add a track to play character animations"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryExecute, EvtCharacters),
				FCanExecuteAction::CreateRaw(this, &FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryCanExecute)
			)
		);
	}
}

bool FEvtCharaAnimTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true; // lol
}

bool FEvtCharaAnimTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtCharaAnimationTrack::StaticClass());
}

const FSlateBrush* FEvtCharaAnimTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtCharaAnimTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtCharaAnimationTrack* CastTrack = Cast<UMovieSceneEvtCharaAnimationTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaAnimTrackEditor::SetEvtManagerBindingID, CastTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtCharaAnimTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtCharaAnimTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtCharaAnimationTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtCharaAnimationTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtCharaAnimTrackEditor::SetEvtManagerBindingID(UMovieSceneEvtCharaAnimationTrack* Track) {
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

void FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtCharaAnimationTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtCharaAnimationTrack* NewTrack = MovieScene->AddTrack<UMovieSceneEvtCharaAnimationTrack>(InObjectBindingId);
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
	for (UMovieSceneEvtCharaAnimationTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Chara Anim"));
		if (EvtManagerGuid.IsValid()) {
			NewTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
		}
	}
}

bool FEvtCharaAnimTrackEditor::HandleAddEvtCharaAnimTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif