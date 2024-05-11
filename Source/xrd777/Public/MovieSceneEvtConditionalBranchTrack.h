#pragma once
#include "CoreMinimal.h"
#include "MovieSceneNameableTrack.h"
#include "MovieSceneEvtConditionalBranchData.h"
#include "MovieSceneEvtConditionalBranchTrack.generated.h"

UCLASS(abstract, Blueprintable, MinimalAPI)
class UMovieSceneEvtConditionalBranchTrack : public UMovieSceneNameableTrack {
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    FMovieSceneEvtConditionalBranchData CondBranchData;

    //UMovieSceneEvtConditionalBranchTrack();

    UMovieSceneEvtConditionalBranchTrack(const FObjectInitializer& Init);
};