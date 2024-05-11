#include "MovieSceneEvtFadeScreenSection.h"

UMovieSceneEvtFadeScreenSection::UMovieSceneEvtFadeScreenSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

