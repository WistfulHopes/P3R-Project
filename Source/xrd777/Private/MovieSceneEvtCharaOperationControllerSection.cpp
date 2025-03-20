#include "MovieSceneEvtCharaOperationControllerSection.h"

UMovieSceneEvtCharaOperationControllerSection::UMovieSceneEvtCharaOperationControllerSection() {
}

EMovieSceneChannelProxyType UMovieSceneEvtCharaOperationControllerSection::CacheChannelProxy() {
	// Set up the channel proxy
	FMovieSceneChannelProxyData Channels;
#if WITH_EDITOR
	FMovieSceneChannelMetaData Metadata;
	Metadata.SetIdentifiers("Values", FText::FromString(TEXT("Values")));
	Metadata.SortOrder = 0;
	Channels.Add(EventData, Metadata, TMovieSceneExternalValue<FEvtCharaOperationControllerPayload>());
#endif
	ChannelProxy = MakeShared<FMovieSceneChannelProxy>(MoveTemp(Channels));
	return EMovieSceneChannelProxyType::Dynamic;
}