#include "MovieSceneEvtSeqControllerSection.h"

UMovieSceneEvtSeqControllerSection::UMovieSceneEvtSeqControllerSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

