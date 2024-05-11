#include "MovieSceneEvtCharaHandwritingSection.h"

UMovieSceneEvtCharaHandwritingSection::UMovieSceneEvtCharaHandwritingSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

