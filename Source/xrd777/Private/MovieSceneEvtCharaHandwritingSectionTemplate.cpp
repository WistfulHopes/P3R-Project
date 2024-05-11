// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaHandwritingSectionTemplate.h"

struct FEvtCharaHandwritingExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtCharaHandwritingSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaHandwritingExecutionToken(const FMovieSceneEvtCharaHandwritingSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtCharaHandwritingSectionTemplate::FMovieSceneEvtCharaHandwritingSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaHandwritingSectionTemplate::FMovieSceneEvtCharaHandwritingSectionTemplate(const UMovieSceneEvtCharaHandwritingSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(false),
    bFireEventsWhenForwards(false)
{}

void FMovieSceneEvtCharaHandwritingSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaHandwritingExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}