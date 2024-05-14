// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaPropAttachSectionTemplate.h"

struct FEvtCharaPropAttachExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtCharaPropAttachSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaPropAttachExecutionToken(const FMovieSceneEvtCharaPropAttachSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtCharaPropAttachSectionTemplate::FMovieSceneEvtCharaPropAttachSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaPropAttachSectionTemplate::FMovieSceneEvtCharaPropAttachSectionTemplate(const UMovieSceneEvtCharaPropAttachSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtCharaPropAttachSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaPropAttachExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
void FMovieSceneEvtCharaPropAttachSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaPropAttachExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}