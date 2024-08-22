// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtCharaPackFaceAnimTrackEditor.h"
#include <CharacterBase/Public/CharacterBaseCore.h>
#include <CharacterBase/Public/NpcBaseCore.h>
#include <Xrd777/Public/AppPropsCore.h>
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtCharaPackFaceAnimTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtCharaPackFaceAnimTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtCharaPackFaceAnimTrackEditor(InSequencer));
}

FEvtCharaPackFaceAnimTrackEditor::FEvtCharaPackFaceAnimTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods
FMovieSceneEvalTemplatePtr FEvtCharaPackFaceAnimTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtCharaPackFaceAnimationSectionTemplate(*CastChecked<UMovieSceneEvtCharaPackFaceAnimationSection>(&InSection));
}

void FEvtCharaPackFaceAnimTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
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
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Character Pack Face Anim"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Add a track to attach a prop to a character"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryExecute, EvtCharacters),
				FCanExecuteAction::CreateRaw(this, &FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryCanExecute)
			)
		);
	}
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

void FEvtCharaPackFaceAnimTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtCharaPackFaceAnimationTrack* CastTrack = Cast<UMovieSceneEvtCharaPackFaceAnimationTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtCharaPackFaceAnimTrackEditor::SetEvtManagerBindingID, CastTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtCharaPackFaceAnimTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtCharaPackFaceAnimTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtCharaPackFaceAnimationTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtCharaPackFaceAnimationTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtCharaPackFaceAnimTrackEditor::SetEvtManagerBindingID(UMovieSceneEvtCharaPackFaceAnimationTrack* Track) {
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

void FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtCharaPackFaceAnimationTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtCharaPackFaceAnimationTrack* NewTrack = MovieScene->AddTrack<UMovieSceneEvtCharaPackFaceAnimationTrack>(InObjectBindingId);
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
	for (UMovieSceneEvtCharaPackFaceAnimationTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Pack Face Anim"));
		if (EvtManagerGuid.IsValid()) {
			NewTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
		}
	}
}

bool FEvtCharaPackFaceAnimTrackEditor::HandleAddEvtCharaPackFaceAnimTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif
