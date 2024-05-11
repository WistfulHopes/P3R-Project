// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtSeqTimeJumpControllerSectionTemplate.h"

struct FEvtSeqTimeJumpExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtSeqTimeJumpControllerSectionData EventData;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtSeqTimeJumpExecutionToken(const FMovieSceneEvtSeqTimeJumpControllerSectionData& EventData, bool bFireEventsWhenForwards,
        bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtSeqTimeJumpControllerSectionTemplate::FMovieSceneEvtSeqTimeJumpControllerSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtSeqTimeJumpControllerSectionTemplate::FMovieSceneEvtSeqTimeJumpControllerSectionTemplate(const UMovieSceneEvtSeqTimeJumpControllerSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtSeqTimeJumpControllerSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtSeqTimeJumpExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}