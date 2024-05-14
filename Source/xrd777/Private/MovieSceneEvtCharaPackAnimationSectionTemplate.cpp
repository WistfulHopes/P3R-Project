// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaPackAnimationSectionTemplate.h"

struct FEvtCharaPackAnimationExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtCharaPackAnimationSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaPackAnimationExecutionToken(const FMovieSceneEvtCharaPackAnimationSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtCharaPackAnimationSectionTemplate::FMovieSceneEvtCharaPackAnimationSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaPackAnimationSectionTemplate::FMovieSceneEvtCharaPackAnimationSectionTemplate(const UMovieSceneEvtCharaPackAnimationSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtCharaPackAnimationSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaPackAnimationExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
void FMovieSceneEvtCharaPackAnimationSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaPackAnimationExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}