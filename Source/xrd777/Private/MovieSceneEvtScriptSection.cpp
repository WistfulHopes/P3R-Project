#include "MovieSceneEvtScriptSection.h"

UMovieSceneEvtScriptSection::UMovieSceneEvtScriptSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

