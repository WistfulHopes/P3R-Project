// (C)ATLUS. (C)SEGA. :3

#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include <Sequencer/Public/MovieSceneTrackEditor.h>
#include <xrd777/Public/MovieSceneEvtAdxSoundTrack.h>

class FEvtAdxSoundTrackEditor
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
	FEvtAdxSoundTrackEditor(TSharedRef<ISequencer> InSequencer);

	// ISequencerTrackEditor interface

	virtual void BuildAddTrackMenu(FMenuBuilder& MenuBuilder) override;
	virtual bool SupportsSequence(UMovieSceneSequence* InSequence) const override;
	virtual bool SupportsType(TSubclassOf<UMovieSceneTrack> Type) const override;
	virtual const FSlateBrush* GetIconBrush() const override;
	//virtual TSharedRef<ISequencerSection> MakeSectionInterface(UMovieSceneSection& SectionObject, UMovieSceneTrack& Track, FGuid ObjectBinding) override;
	virtual void BuildTrackContextMenu(FMenuBuilder& MenuBuilder, UMovieSceneTrack* Track) override;
private:
	void HandleAddEvtAdxSoundTrackMenuEntryExecute();
	bool HandleAddEvtAdxSoundTrackMenuEntryCanExecute() const;

	void BuildEventConditionalBranchMenu(FMenuBuilder& Builder, UMovieSceneEvtAdxSoundTrack* Track);
};

#endif