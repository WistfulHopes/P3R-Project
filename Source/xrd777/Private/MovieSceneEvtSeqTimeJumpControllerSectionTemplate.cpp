// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtSeqTimeJumpControllerSectionTemplate.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtSeqTimeJumpController, Log, All);

struct FEvtSeqTimeJumpExecutionToken : IMovieSceneExecutionToken {
    TArray<TTuple<float, FEvtSeqTimeJumpControllerPayload>> Entries;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtSeqTimeJumpExecutionToken(const TArray<TTuple<float, FEvtSeqTimeJumpControllerPayload>>& Entries, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : Entries(Entries), CondBranchData(CondBranchData) {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {
        UObject* PlaybackContext = Player.GetPlaybackContext();
        UWorld* World = PlaybackContext ? PlaybackContext->GetWorld() : nullptr;
        if (!World) {
            return;
        }
        if (!CondBranchData.IsCondition(Context, Operand, PersistentData, Player)) {
            return;
        }
        AActor** EventManagerMaybe = World->GetCurrentLevel()->Actors.FindByPredicate([](AActor*& CurrActor) { return CurrActor->IsA<AAtlEvtEventManager>(); });
        if (EventManagerMaybe) {
            AAtlEvtEventManager* EventManager = Cast<AAtlEvtEventManager>(*EventManagerMaybe);
            AAtlEvtLevelSequenceActor* LevelSequenceActor = EventManager->GetAtlEvtLevelSequenceActor(PlaybackContext);
            for (TTuple<float, FEvtSeqTimeJumpControllerPayload>& Entry : Entries) {
                switch (Entry.Value.Operation) {
                case EEvtSeqTimeJumpControllerOperation::TimeJump:
                    LevelSequenceActor->SequencePlayer->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(Entry.Key, EUpdatePositionMethod::Jump));
                    UE_LOG(AtlEvtSeqTimeJumpController, Display, TEXT("Time Jump: New Time is %f sec"), Entry.Key);
                    break;
                default:
                    UE_LOG(AtlEvtSeqTimeJumpController, Display, TEXT("TODO: Time Jump Controller type %d"), (int32)Entry.Value.Operation);
                    break;
                }
            }
        }
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
    TArray<TTuple<float, FEvtSeqTimeJumpControllerPayload>> PayloadEntries;
    for (int i = 0; i < EventData.Times.Num() - 1; i++) {
        const FFrameNumber& CurrFrame = EventData.Times[i];
        // Get time value for the next event in the time sequence, use that as a jumping off point if conditions are met
        if (CurrFrame >= SweptRange.GetLowerBoundValue() && CurrFrame < SweptRange.GetUpperBoundValue()) {
            PayloadEntries.Emplace((float)EventData.Times[i + 1].Value / Context.GetFrameRate().Numerator, EventData.KeyValues[i]);
        }
    }
    if (PayloadEntries.Num() > 0) {
        ExecutionTokens.Add(FEvtSeqTimeJumpExecutionToken(PayloadEntries, CondBranchData));
    }
}