// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtSeqTimeJumpControllerSectionTemplate.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtSeqTimeJumpController, Log, All);

struct FEvtSeqTimeJumpExecutionToken : IMovieSceneExecutionToken {
    TArray<FEvtSeqTimeJumpControllerPayload> Entries;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtSeqTimeJumpExecutionToken(const TArray<FEvtSeqTimeJumpControllerPayload>& Entries, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : Entries(Entries), CondBranchData(CondBranchData) {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {
        if (!CondBranchData.IsCondition(Context, Operand, PersistentData, Player)) {
            return;
        }
        UE_LOG(AtlEvtSeqTimeJumpController, Display, TEXT("TODO: Time Jump Controller"));
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
    //ExecutionTokens.Add(FEvtSeqTimeJumpExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
void FMovieSceneEvtSeqTimeJumpControllerSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    bool bIsPlaying = Context.GetDirection() == EPlayDirection::Forwards && Context.GetRange().Size<FFrameTime>() >= FFrameTime(0) && bFireEventsWhenForwards;
    if (!bIsPlaying) {
        return;
    }
    // Check that the target event data payload entry wraps inside the given swept range
    TArray<FEvtSeqTimeJumpControllerPayload> PayloadEntries;
    for (int i = 0; i < EventData.Times.Num(); i++) {
        const FFrameNumber& CurrFrame = EventData.Times[i];
        if (CurrFrame >= SweptRange.GetLowerBoundValue() && CurrFrame < SweptRange.GetUpperBoundValue()) {
            PayloadEntries.Add(EventData.KeyValues[i]);
        }
    }
    if (PayloadEntries.Num() > 0) {
        ExecutionTokens.Add(FEvtSeqTimeJumpExecutionToken(PayloadEntries, CondBranchData));
    }
}