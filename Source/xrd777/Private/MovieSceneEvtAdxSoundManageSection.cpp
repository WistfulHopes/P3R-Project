#include "MovieSceneEvtAdxSoundManageSection.h"

UMovieSceneEvtAdxSoundManageSection::UMovieSceneEvtAdxSoundManageSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

