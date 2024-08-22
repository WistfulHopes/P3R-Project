// (C)ATLUS. (C)SEGA.

#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include <Sequencer/Public/MovieSceneTrackEditor.h>
#include <xrd777/Public/MovieSceneEvtCharaAnimationTrack.h>
#include <xrd777/Public/MovieSceneEvtCharaAnimationSection.h>
#include <xrd777/Public/MovieSceneEvtCharaAnimationSectionTemplate.h>

class XRD777_API FEvtCharaAnimTrackEditor
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
	FEvtCharaAnimTrackEditor(TSharedRef<ISequencer> InSequencer);

	// ISequencerTrackEditor interface

	//virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const;
	virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;
	//virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;
	virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual const FSlateBrush* GetIconBrush() const override;

	void BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtCharaAnimationTrack* DialogTrack);

private:
	void HandleAddEvtCharaAnimTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds);
	bool HandleAddEvtCharaAnimTrackMenuEntryCanExecute() const;
	void SetEvtManagerBindingID(UMovieSceneEvtCharaAnimationTrack* Track);
};

#endif