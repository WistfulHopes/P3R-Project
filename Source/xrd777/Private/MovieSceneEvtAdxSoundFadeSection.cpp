#include "MovieSceneEvtAdxSoundFadeSection.h"

UMovieSceneEvtAdxSoundFadeSection::UMovieSceneEvtAdxSoundFadeSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

