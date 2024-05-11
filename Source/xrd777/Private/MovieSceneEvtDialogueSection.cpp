#include "MovieSceneEvtDialogueSection.h"

UMovieSceneEvtDialogueSection::UMovieSceneEvtDialogueSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

