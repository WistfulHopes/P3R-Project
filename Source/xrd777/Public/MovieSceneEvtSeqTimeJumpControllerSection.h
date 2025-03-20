#pragma once
#include "CoreMinimal.h"
#include "MovieSceneSection.h"
#include "MovieSceneEvtSeqTimeJumpControllerSectionData.h"
#include <MovieScene/Public/Channels/MovieSceneChannelProxy.h>
#include "MovieSceneEvtSeqTimeJumpControllerSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEvtSeqTimeJumpControllerSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEvtSeqTimeJumpControllerSectionData EventData;
    
public:
    UMovieSceneEvtSeqTimeJumpControllerSection();
public:
    virtual EMovieSceneChannelProxyType CacheChannelProxy() override;
};