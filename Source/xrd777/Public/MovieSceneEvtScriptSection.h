#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "MovieSceneEvtScriptSectionData.h"
#include <MovieScene/Public/Channels/MovieSceneChannelProxy.h>
#include "MovieSceneEvtScriptSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEvtScriptSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEvtScriptSectionData EventData;
    
    UMovieSceneEvtScriptSection();
public:
    virtual EMovieSceneChannelProxyType CacheChannelProxy() override;
};