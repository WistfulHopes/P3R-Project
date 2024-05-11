#include "MovieSceneEvtSeqTimeJumpControllerSection.h"

UMovieSceneEvtSeqTimeJumpControllerSection::UMovieSceneEvtSeqTimeJumpControllerSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

