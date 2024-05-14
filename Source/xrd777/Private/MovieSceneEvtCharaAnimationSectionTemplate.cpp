// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaAnimationSectionTemplate.h"

struct FEvtCharaAnimationExectionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtCharaAnimationSectionData EventData;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaAnimationExectionToken(const FMovieSceneEvtCharaAnimationSectionData& EventData, bool bFireEventsWhenForwards, 
        bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtCharaAnimationSectionTemplate::FMovieSceneEvtCharaAnimationSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaAnimationSectionTemplate::FMovieSceneEvtCharaAnimationSectionTemplate(const UMovieSceneEvtCharaAnimationSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtCharaAnimationSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaAnimationExectionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}

void FMovieSceneEvtCharaAnimationSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaAnimationExectionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}