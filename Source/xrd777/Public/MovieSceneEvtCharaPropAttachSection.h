#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "MovieSceneEvtCharaPropAttachSectionData.h"
#include <MovieScene/Public/Channels/MovieSceneChannelProxy.h>
#include "MovieSceneEvtCharaPropAttachSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEvtCharaPropAttachSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEvtCharaPropAttachSectionData EventData;
    
    UMovieSceneEvtCharaPropAttachSection();
public:
    virtual EMovieSceneChannelProxyType CacheChannelProxy() override;
};

