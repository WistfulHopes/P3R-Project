// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtScriptTrackEditor.h"
#include <xrd777/Public/MovieSceneEvtScriptSection.h>
#include <xrd777/Public/MovieSceneEvtScriptSectionTemplate.h>
#include "EvtConditionBranchDetailsCustom.h"

#define LOCTEXT_NAMESPACE "FEvtScriptTrackEditor"

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtScriptTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtScriptTrackEditor(InSequencer));
}

FEvtScriptTrackEditor::FEvtScriptTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}

FMovieSceneEvalTemplatePtr FEvtScriptTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtScriptSectionTemplate(*CastChecked<UMovieSceneEvtScriptSection>(&InSection));
}

bool FEvtScriptTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtScriptTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtScriptTrack::StaticClass());
}

const FSlateBrush* FEvtScriptTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

void FEvtScriptTrackEditor::HandleAddEvtScriptTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtScriptTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtScriptTrack* NewObjectTrack = MovieScene->AddTrack<UMovieSceneEvtScriptTrack>(InObjectBindingId);
		NewTracks.Add(NewObjectTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewDialogSection = NewObjectTrack->CreateNewSection();
			check(NewDialogSection);
			NewObjectTrack->AddSection(*NewDialogSection);
			GetSequencer()->OnAddTrack(NewObjectTrack, InObjectBindingId);
		}
	}

	check(NewTracks.Num() != 0);
	for (UMovieSceneEvtScriptTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Script"));
	}
}

bool FEvtScriptTrackEditor::HandleAddEvtScriptTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();

	return FocusedMovieScene != nullptr;
}

void FEvtScriptTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
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
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "Event Script"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Call flowscript procedures"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtScriptTrackEditor::HandleAddEvtScriptTrackMenuEntryExecute, AtlusEventManager),
				FCanExecuteAction::CreateRaw(this, &FEvtScriptTrackEditor::HandleAddEvtScriptTrackMenuEntryCanExecute)
			)
		);
	}
}
void FEvtScriptTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	auto* CastTrack = Cast<UMovieSceneEvtScriptTrack>(Track);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtDialogueEditConditionalBrach", "Conditional Data"), FText(),
		FNewMenuDelegate::CreateRaw(this, &FEvtScriptTrackEditor::BuildEventConditionalBranchMenu, CastTrack),
		false, FSlateIcon());
}

void FEvtScriptTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtScriptTrack* DialogTrack) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtScriptTrack::StaticClass(),
		FOnGetDetailCustomizationInstance::CreateLambda([DialogTrack] { return FEvtConditionBranchDetailsCustom::MakeInstance(*DialogTrack); })
	);
	DetailsView->SetObject(DialogTrack);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

#undef LOCTEXT_NAMESPACE

#endif
