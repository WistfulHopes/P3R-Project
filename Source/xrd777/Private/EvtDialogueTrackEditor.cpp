// (C)ATLUS. (C)SEGA. :3


#if WITH_EDITORONLY_DATA

#pragma once

#include "EvtDialogueTrackEditor.h"
#include <MovieSceneSequenceEditor.h>
#include "Logging/LogMacros.h"
#include "Sequencer/Public/SequencerSectionPainter.h"
#include "CommonMovieSceneTools.h"
//#include "Sequencer/Public/ISequencerSection.h"
#include "EvtConditionBranchDetailsCustom.h"
#include "IDetailsView.h"
#include "MovieScene/Public/MovieSceneObjectBindingID.h"
#include <Sequencer/Public/SequencerUtilities.h>

#define LOCTEXT_NAMESPACE "FEvtDialogueTrackEditor"

DEFINE_LOG_CATEGORY_STATIC(LogEvtDialogueTrackEditor, Log, All);

class FDialogueSection : public FSequencerSection {
public:
	FDialogueSection(UMovieSceneSection& InSection, TWeakPtr<ISequencer> InSequencer)
		: FSequencerSection(InSection)
		, WeakSequencer(InSequencer)
	{}

	// ISequencerSection interface

	virtual int32 OnPaintSection(FSequencerSectionPainter& Painter) const override {
		int32 LayerId = Painter.PaintSectionBackground();
		return LayerId + 1;
	}

private:
	// The sequencer controlling this section
	TWeakPtr<ISequencer> WeakSequencer;
};

// Constructors

TSharedRef<ISequencerTrackEditor> FEvtDialogueTrackEditor::CreateTrackEditor(TSharedRef<ISequencer> InSequencer) {
	return MakeShareable(new FEvtDialogueTrackEditor(InSequencer));
}
// Basic ctor

FEvtDialogueTrackEditor::FEvtDialogueTrackEditor(TSharedRef<ISequencer> InSequencer)
	: FMovieSceneTrackEditor(InSequencer) {}
// Methods

// Requires making MovieSceneEvtDialogueSection (also all Evt tracks only have one section)

TSharedRef<ISequencerSection> FEvtDialogueTrackEditor::MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) {
	check(SupportsType(SectionObject.GetOuter()->GetClass()));
	return MakeShared<FDialogueSection>(SectionObject, GetSequencer());
}

FMovieSceneEvalTemplatePtr FEvtDialogueTrackEditor::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtDialogueSectionTemplate(*CastChecked<UMovieSceneEvtDialogueSection>(&InSection));
}


void FEvtDialogueTrackEditor::BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) {
	// put dialog tracks in BP_AtlEvtEventManager_C bindings only
	// get selected object class
	
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
			LOCTEXT("AddEvtDialogueTrack_ObjectBinding", "[P3RE] Event Dialog"),
			LOCTEXT("AddEvtDialogueTrackTooltip_ObjectBinding", "[Persona 3 Reload] Add a track to trigger BMD message entries"),
			FSlateIcon(),
			FUIAction(
				FExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryExecute, AtlusEventManager),
				FCanExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryCanExecute)
			)
		);
	}
}

void FEvtDialogueTrackEditor::BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) {
	UMovieSceneEvtDialogueTrack* DialogTrack = Cast<UMovieSceneEvtDialogueTrack>(Track);
	MenuBuilder.AddMenuEntry(
		LOCTEXT("AddEvtDialogueTrack_SetEvtManagerBinding", "Set EVT Manager Binding"),
		LOCTEXT("AddEvtDialogueTrackTooltip_SetEvtManagerBinding", "[Persona 3 Reload] Needed for conditional tracks to work properly"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateRaw(this, &FEvtDialogueTrackEditor::EvtDialogueTrackSetEvtManagerBindingID, DialogTrack)
		)
	);
	MenuBuilder.AddSubMenu(
		LOCTEXT("EvtDialogueEditConditionalBrach", "Conditional Data"), 
		FText(), 
		FNewMenuDelegate::CreateRaw(this, &FEvtDialogueTrackEditor::BuildEventConditionalBranchMenu, DialogTrack),
		false,
		FSlateIcon());
}

void FEvtDialogueTrackEditor::EvtDialogueTrackSetEvtManagerBindingID(UMovieSceneEvtDialogueTrack* DialogTrack) {
	UMovieScene* CurrMovieScene = GetFocusedMovieScene();
	FGuid EvtManagerGuid;
	for (int i = 0; i < CurrMovieScene->GetPossessableCount(); i++) {
		auto CurrPossessable = CurrMovieScene->GetPossessable(i);
		if (CurrPossessable.GetPossessedObjectClass()->GetDefaultObject()->IsA<AAtlEvtEventManager>()) {
			EvtManagerGuid = CurrPossessable.GetGuid();
		}
	}
	if (EvtManagerGuid.IsValid()) {
		DialogTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
	}
	CurrMovieScene->MarkPackageDirty();
}

void FEvtDialogueTrackEditor::BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtDialogueTrack* DialogTrack) {
	FDetailsViewArgs DetailViewArgs = FDetailsViewArgs(false, false, false, FDetailsViewArgs::ActorsUseNameArea, true, nullptr, false, FName());
	TSharedRef<IDetailsView> DetailsView = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailViewArgs);
	DetailsView->RegisterInstancedCustomPropertyLayout(
		UMovieSceneEvtDialogueTrack::StaticClass(), 
		FOnGetDetailCustomizationInstance::CreateLambda([DialogTrack] { return FEvtConditionBranchDetailsCustom::MakeInstance(*DialogTrack); })
	);
	DetailsView->SetObject(DialogTrack);
	Builder.AddWidget(DetailsView, FText::GetEmpty(), true);
}

void FEvtDialogueTrackEditor::OnTestButtonExecute(UMovieSceneEvtDialogueTrack* Track) {
	
}

bool FEvtDialogueTrackEditor::SupportsSequence(UMovieSceneSequence* InSequence) const {
	return true;
}

bool FEvtDialogueTrackEditor::SupportsType(TSubclassOf<UMovieSceneTrack> Type) const {
	return (Type == UMovieSceneEvtDialogueTrack::StaticClass());
}

const FSlateBrush* FEvtDialogueTrackEditor::GetIconBrush() const
{
	return FEditorStyle::GetBrush("Sequencer.Tracks.Audio");
}

// Callbacks

void FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds) {
	UMovieScene* MovieScene = GetFocusedMovieScene();
	if (MovieScene == nullptr || MovieScene->IsReadOnly()) {
		return;
	}
	const FScopedTransaction Transaction(LOCTEXT("AddEvtAdxSoundManageTrack_Transaction", "P3RE Event ADX Sound Manage Track"));
	MovieScene->Modify();
	TArray<UMovieSceneEvtDialogueTrack*> NewTracks;
	for (FGuid InObjectBindingId : InObjectBindingIds) {
		UMovieSceneEvtDialogueTrack* NewDialogObjectTrack = MovieScene->AddTrack<UMovieSceneEvtDialogueTrack>(InObjectBindingId);
		NewTracks.Add(NewDialogObjectTrack);
		if (GetSequencer().IsValid()) {
			UMovieSceneSection* NewDialogSection = NewDialogObjectTrack->CreateNewSection();
			check(NewDialogSection);
			NewDialogObjectTrack->AddSection(*NewDialogSection);
			GetSequencer()->OnAddTrack(NewDialogObjectTrack, InObjectBindingId);
			GetSequencer()->NotifyMovieSceneDataChanged(EMovieSceneDataChangeType::MovieSceneStructureItemAdded);
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

	for (UMovieSceneEvtDialogueTrack* NewTrack : NewTracks) {
		NewTrack->SetDisplayName(LOCTEXT("TrackName", "Evt Dialog"));
		if (EvtManagerGuid.IsValid()) {
			NewTrack->CondBranchData.EvtManagerBindingID = FMovieSceneObjectBindingID(UE::MovieScene::FRelativeObjectBindingID(EvtManagerGuid));
		}
	}
}

bool FEvtDialogueTrackEditor::HandleAddEvtDialogueTrackMenuEntryCanExecute() const
{
	UMovieScene* FocusedMovieScene = GetFocusedMovieScene();
	return FocusedMovieScene != nullptr;
}

#undef LOCTEXT_NAMESPACE

#endif
