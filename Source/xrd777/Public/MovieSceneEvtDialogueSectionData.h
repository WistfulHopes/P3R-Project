#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Channels/MovieSceneChannel.h"
#include "EvtDialoguePayload.h"
#include "MovieSceneEvtDialogueSectionData.generated.h"

USTRUCT(BlueprintType)
struct XRD777_API FMovieSceneEvtDialogueSectionData : public FMovieSceneChannel {
    GENERATED_BODY()
public:
private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FFrameNumber> Times;
    
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    TArray<FEvtDialoguePayload> KeyValues;
    
public:
    const TArray<FFrameNumber>& GetTimes() const { return Times; }
    const TArray<FEvtDialoguePayload>& GetValues() const { return KeyValues; }
    FMovieSceneEvtDialogueSectionData();
};

