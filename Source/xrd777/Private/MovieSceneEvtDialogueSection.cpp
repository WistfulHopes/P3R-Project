#include "MovieSceneEvtDialogueSection.h"

UMovieSceneEvtDialogueSection::UMovieSceneEvtDialogueSection() {
	SetRange(TRange<FFrameNumber>::All());
	bSupportsInfiniteRange = true;
}

EMovieSceneChannelProxyType UMovieSceneEvtDialogueSection::CacheChannelProxy() {
	// Set up the channel proxy
	FMovieSceneChannelProxyData Channels;
#if WITH_EDITOR
	FMovieSceneChannelMetaData Metadata;
	Metadata.SetIdentifiers("Values", FText::FromString(TEXT("Values")));
	Metadata.SortOrder = 0;
	Channels.Add(EventData, Metadata, TMovieSceneExternalValue<FEvtDialoguePayload>());
#endif
	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(MoveTemp(Channels));
	return EMovieSceneChannelProxyType::Dynamic;
}