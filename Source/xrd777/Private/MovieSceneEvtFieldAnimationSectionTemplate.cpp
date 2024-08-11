// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtFieldAnimationSectionTemplate.h"

struct FEvtFieldAnimationExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtFieldAnimationSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtFieldAnimationExecutionToken(const FMovieSceneEvtFieldAnimationSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {
    }
};

FMovieSceneEvtFieldAnimationSectionTemplate::FMovieSceneEvtFieldAnimationSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtFieldAnimationSectionTemplate::FMovieSceneEvtFieldAnimationSectionTemplate(const UMovieSceneEvtFieldAnimationSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtFieldAnimationSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtFieldAnimationExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}void FMovieSceneEvtFieldAnimationSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtFieldAnimationExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}