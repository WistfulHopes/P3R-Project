// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtFadeScreenSectionTemplate.h"

struct FEvtFadeScreenExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtFadeScreenSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtFadeScreenExecutionToken(const FMovieSceneEvtFadeScreenSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtFadeScreenSectionTemplate::FMovieSceneEvtFadeScreenSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtFadeScreenSectionTemplate::FMovieSceneEvtFadeScreenSectionTemplate(const UMovieSceneEvtFadeScreenSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(false),
    bFireEventsWhenForwards(false)
{}

void FMovieSceneEvtFadeScreenSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtFadeScreenExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}