// (C)ATLUS. (C)SEGA. :3

#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"
#include "MovieSceneEvtConditionalBranchData.h"
#include "MovieSceneEvtConditionalBranchTrack.h"

/**
 *
 */
class XRD777_API FEvtConditionBranchDetailsCustom : public IDetailCustomization
{
public:
    static TSharedRef<IDetailCustomization> MakeInstance(const UMovieSceneEvtConditionalBranchTrack& Track) {
        auto NewInstance = new FEvtConditionBranchDetailsCustom(Track);
        return MakeShareable(NewInstance);
    }
    FEvtConditionBranchDetailsCustom(const UMovieSceneEvtConditionalBranchTrack& Track) {
        TrackClass = Track.GetClass();
    }
    /** IDetailCustomization interface */
    virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder);
private:
    UClass* TrackClass;
};

#endif