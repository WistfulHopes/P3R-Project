// (C)ATLUS. (C)SEGA. :3

#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include <Sequencer/Public/MovieSceneTrackEditor.h>
#include <MovieSceneTools/Public/KeyframeTrackEditor.h>
#include "xrd777/Public/MovieSceneEvtDialogueTrack.h"
#include "xrd777/Public/MovieSceneEvtDialogueSection.h"
#include "xrd777/Public/MovieSceneEvtDialogueSectionTemplate.h"

class XRD777_API FEvtDialogueTrackEditor
	: public FMovieSceneTrackEditor
{
public:
	/**
	 * Factory function to create an instance of this class (called by a sequencer).
	 *
	 * @param InSequencer The sequencer instance to be used by this tool.
	 * @return The new instance of this class.
	 */
	static TSharedRef<ISequencerTrackEditor> CreateTrackEditor(TSharedRef<ISequencer> InSequencer);

	/**
	 * Creates and initializes a new instance.
	 *
	 * @param InSequencer The sequencer instance to be used by this tool.
	 */
	FEvtDialogueTrackEditor(TSharedRef<ISequencer> InSequencer);

	void OnTestButtonExecute(UMovieSceneEvtDialogueTrack* Track);

	// ISequencerTrackEditor interface

	virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const;
	//virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;
	virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;
	virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual const FSlateBrush* GetIconBrush() const override;
	//virtual TSharedPtr<SWidget> BuildOutlinerEditWidget(const FGuid& ObjectBinding, UMovieSceneTrack* Track, const FBuildEditWidgetParams& Params) override;

	// EvtConditionalBranchMenu submenu
	//TSharedRef<SWidget> BuildEventConditionalBranchMenu(UMovieSceneEvtDialogueTrack* DialogTrack);
	void BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtDialogueTrack* DialogTrack);

private:
	void HandleAddEvtDialogueTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds);
	bool HandleAddEvtDialogueTrackMenuEntryCanExecute() const;

	void EvtDialogueTrackSetEvtManagerBindingID(UMovieSceneEvtDialogueTrack* DialogTrack);
};

#endif