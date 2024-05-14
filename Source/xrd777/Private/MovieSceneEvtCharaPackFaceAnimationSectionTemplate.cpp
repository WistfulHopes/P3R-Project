// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaPackFaceAnimationSectionTemplate.h"

struct FEvtCharaPackFaceAnimationExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtCharaPackFaceAnimationSectionData EventData;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaPackFaceAnimationExecutionToken(const FMovieSceneEvtCharaPackFaceAnimationSectionData& EventData, bool bFireEventsWhenForwards, 
        bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtCharaPackFaceAnimationSectionTemplate::FMovieSceneEvtCharaPackFaceAnimationSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaPackFaceAnimationSectionTemplate::FMovieSceneEvtCharaPackFaceAnimationSectionTemplate(const UMovieSceneEvtCharaPackFaceAnimationSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtCharaPackFaceAnimationSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaPackFaceAnimationExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
void FMovieSceneEvtCharaPackFaceAnimationSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtCharaPackFaceAnimationExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}