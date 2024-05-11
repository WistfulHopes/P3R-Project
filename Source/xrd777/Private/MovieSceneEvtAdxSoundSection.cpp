#include "MovieSceneEvtAdxSoundSection.h"

UMovieSceneEvtAdxSoundSection::UMovieSceneEvtAdxSoundSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

