#include "MovieSceneEvtCharaAnimationSection.h"

UMovieSceneEvtCharaAnimationSection::UMovieSceneEvtCharaAnimationSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

