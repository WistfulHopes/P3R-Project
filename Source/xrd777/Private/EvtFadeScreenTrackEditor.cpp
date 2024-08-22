// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtFadeScreenTrackEditor.h"
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtFadeScreenTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtFadeScreenTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtFadeScreenTrackEditor(InSequencer));
}

FEvtFadeScreenTrackEditor::FEvtFadeScreenTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

void FEvtFadeScreenTrackEditor::BuildAddTrackMenu(FMenuBuilder& MenuBuilder) {
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtFadeScreenTrack", "Atlus Event Fade Screen Track"),
		LOCTEXT("AddEvtFadeScreenTrackTooltip", "TODO: Description"),
		FSlateIcon(FEditorStyle::GetStyleSetName(), "Sequencer.Tracks.Audio"),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryExecute),
			FCanExecuteAction::CreateRaw(this, &FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryCanExecute)
		)
	);
}

bool FEvtFadeScreenTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtFadeScreenTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtFadeScreenTrack::StaticClass());
}

const FSlateBrush* FEvtFadeScreenTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtFadeScreenTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtFadeScreenTrack* CastTrack = Cast<UMovieSceneEvtFadeScreenTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtCharaAnimTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtCharaAnimTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtFadeScreenTrackEditor::SetEvtManagerBindingID, CastTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtCharaAnimEditConditionalBrach", "Conditional Data"),
		FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtFadeScreenTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false,
		FSlateIcon());
}

void FEvtFadeScreenTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtFadeScreenTrack* Track) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtFadeScreenTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([Track] { return FEvtConditionBranchDetailsCustom::MakeInstance(*Track); })
	);
	DetailsView->SetObject(Track);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtFadeScreenTrackEditor::SetEvtManagerBindingID(UMovieSceneEvtFadeScreenTrack* Track) {
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

void FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryExecute() {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	UMovieSceneTrack* SoundFadeTrack = MovieScene->FindMasterTrack<UMovieSceneEvtFadeScreenTrack>();
	if (SoundFadeTrack != nullptr) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	SoundFadeTrack = FindOrCreateMasterTrack<UMovieSceneEvtFadeScreenTrack>().Track;
	check(SoundFadeTrack);
	UMovieSceneSection* NewSection = SoundFadeTrack->CreateNewSection();
	check(NewSection);
	SoundFadeTrack->AddSection(*NewSection);
	if (GetSequencer().IsValid()) {
		GetSequencer()->OnAddTrack(SoundFadeTrack, FGuid());
	}

	// look for event manager
	FGuid EvtManagerGuid;
	for (int i = 0; i < MovieScene->GetPossessableCount(); i++) {
		auto CurrPossessable = MovieScene->GetPossessable(i);
		if (CurrPossessable.GetPossessedObjectClass()->GetDefaultObject()->IsA<AAtlEvtEventManager>()) {
			EvtManagerGuid = CurrPossessable.GetGuid();
		}
	}
	if (EvtManagerGuid.IsValid()) {
		Cast<UMovieSceneEvtFadeScreenTrack>(SoundFadeTrack)->CondBranchData.EvtManagerBindingID 
			= FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
	}
}

bool FEvtFadeScreenTrackEditor::HandleAddEvtFadeScreenTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return ((FocusedMovieScene != nullptr) && (FocusedMovieScene->FindMasterTrack<UMovieSceneEvtFadeScreenTrack>() == nullptr));
}

#undef LOCTEXT_NAMESPACE

#endif
