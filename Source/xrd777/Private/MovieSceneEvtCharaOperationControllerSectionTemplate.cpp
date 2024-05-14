// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaOperationControllerSectionTemplate.h"

struct FEvtCharaOperationControllerExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtCharaOperationControllerSectionData EventData;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaOperationControllerExecutionToken(const FMovieSceneEvtCharaOperationControllerSectionData& EventData,bool bFireEventsWhenForwards, 
        bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtCharaOperationControllerSectionTemplate::FMovieSceneEvtCharaOperationControllerSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaOperationControllerSectionTemplate::FMovieSceneEvtCharaOperationControllerSectionTemplate(const UMovieSceneEvtCharaOperationControllerSection& InSection)
    : EventData(InSection.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtCharaOperationControllerSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaOperationControllerExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
void FMovieSceneEvtCharaOperationControllerSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaOperationControllerExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}