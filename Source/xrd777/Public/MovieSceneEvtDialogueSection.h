#pragma once
#include "CoreMinimal.h"
#include "Curves/NameCurve.h"
#include "MovieSceneSection.h"
#include "MovieSceneEvtDialogueSectionData.h"
#include <xrd777/Public/MovieSceneEvtConditionalBranchData.h>
#include "MovieSceneEvtDialogueSection.generated.h"

UCLASS(Blueprintable, MinimalAPI)
class UMovieSceneEvtDialogueSection : public UMovieSceneSection {
    GENERATED_BODY()
public:
    UMovieSceneEvtDialogueSection();

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess=true))
    FMovieSceneEvtDialogueSectionData EventData;
    
private:
    UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
    FNameCurve Events;
public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
    FMovieSceneEvtConditionalBranchData CondBranchData;
};

