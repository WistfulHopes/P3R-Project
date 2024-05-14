// (C)ATLUS. (C)SEGA. :3

#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include <Sequencer/Public/MovieSceneTrackEditor.h>
#include "xrd777/Public/MovieSceneEvtScriptTrack.h"

/**
 * 
 */
class XRD777_API FEvtScriptTrackEditor
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
	FEvtScriptTrackEditor(TSharedRef<ISequencer> InSequencer);

	// ISequencerTrackEditor interface
	virtual FMovieSceneEvalTemplatePtr CreateTemplateForSection(const UMovieSceneSection& InSection) const;
	virtual void BuildObjectBindingTrackMenu(FMenuBuilder& MenuBuilder, const TArray<FGuid>& ObjectBindings, const UClass* ObjectClass) override;
	virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;
	virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual const FSlateBrush* GetIconBrush() const override;

	void BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtScriptTrack* Track);

private:
	void HandleAddEvtScriptTrackMenuEntryExecute(TArray<FGuid> InObjectBindingIds);
	bool HandleAddEvtScriptTrackMenuEntryCanExecute() const;
};

#endif