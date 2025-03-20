#include "MovieSceneEvtCharaHandwritingSection.h"

UMovieSceneEvtCharaHandwritingSection::UMovieSceneEvtCharaHandwritingSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

EMovieSceneChannelProxyType UMovieSceneEvtCharaHandwritingSection::CacheChannelProxy() {
	// Set up the channel proxy
	FMovieSceneChannelProxyData Channels;
#if WITH_EDITOR
	FMovieSceneChannelMetaData Metadata;
	Metadata.SetIdentifiers("Values", FText::FromString(TEXT("Values")));
	Metadata.SortOrder = 0;
	Channels.Add(EventData, Metadata, TMovieSceneExternalValue<FEvtCharaHandwritingPayload>());
#endif
	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(MoveTemp(Channels));
	return EMovieSceneChannelProxyType::Dynamic;
}