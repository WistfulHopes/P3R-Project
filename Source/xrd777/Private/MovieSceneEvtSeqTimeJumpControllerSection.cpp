#include "MovieSceneEvtSeqTimeJumpControllerSection.h"

UMovieSceneEvtSeqTimeJumpControllerSection::UMovieSceneEvtSeqTimeJumpControllerSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

EMovieSceneChannelProxyType UMovieSceneEvtSeqTimeJumpControllerSection::CacheChannelProxy() {
	// Set up the channel proxy
	FMovieSceneChannelProxyData Channels;
#if WITH_EDITOR
	FMovieSceneChannelMetaData Metadata;
	Metadata.SetIdentifiers("Values", FText::FromString(TEXT("Values")));
	Metadata.SortOrder = 0;
	Channels.Add(EventData, Metadata, TMovieSceneExternalValue<FEvtSeqTimeJumpControllerPayload>());
#endif
	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(MoveTemp(Channels));
	return EMovieSceneChannelProxyType::Dynamic;
}