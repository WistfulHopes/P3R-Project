#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "MovieSceneEvtFadeScreenSectionData.h"
#include <MovieScene/Public/Channels/MovieSceneChannelProxy.h>
#include "MovieSceneEvtFadeScreenSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEvtFadeScreenSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEvtFadeScreenSectionData EventData;
    
    UMovieSceneEvtFadeScreenSection();
public:
    virtual EMovieSceneChannelProxyType CacheChannelProxy() override;
};