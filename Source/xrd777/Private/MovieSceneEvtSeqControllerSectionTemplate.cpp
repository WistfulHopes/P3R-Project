// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtSeqControllerSectionTemplate.h"

struct FEvtSeqControllerExecutionToken: IMovieSceneExecutionToken {
    FMovieSceneEvtSeqControllerSectionData EventData;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtSeqControllerExecutionToken(const FMovieSceneEvtSeqControllerSectionData& EventData, bool bFireEventsWhenForwards, 
        bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData),  bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtSeqControllerSectionTemplate::FMovieSceneEvtSeqControllerSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtSeqControllerSectionTemplate::FMovieSceneEvtSeqControllerSectionTemplate(const UMovieSceneEvtSeqControllerSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtSeqControllerSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtSeqControllerExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}

void FMovieSceneEvtSeqControllerSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtSeqControllerExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}