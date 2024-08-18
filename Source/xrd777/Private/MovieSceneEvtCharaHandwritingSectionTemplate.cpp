// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaHandwritingSectionTemplate.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtCharaHandwriting, Log, All);

struct FEvtCharaHandwritingExecutionToken : IMovieSceneExecutionToken {
    // Old format
    /*
    FMovieSceneEvtCharaHandwritingSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;
    */

    // New format (matches in game structure 1:1)
    TArray<FEvtCharaHandwritingPayload> Entries;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    /*
    FEvtCharaHandwritingExecutionToken(const FMovieSceneEvtCharaHandwritingSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}
    */

    FEvtCharaHandwritingExecutionToken(const TArray<FEvtCharaHandwritingPayload>& InEntries, const FMovieSceneEvtConditionalBranchData& InCondBranchData)
        : Entries(InEntries), CondBranchData(InCondBranchData) {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {
        // 0x1410bf320 (PERSONA3 RELOAD 1.0.0.0 Win64)

        // Get dependencies
        UObject* PlaybackContext = Player.GetPlaybackContext();
        UWorld* World = PlaybackContext ? PlaybackContext->GetWorld() : nullptr;
        if (!World) {
            return;
        }
        UGameInstance* GameInstance = World->GetGameInstance();
        if (!GameInstance) {
            return;
        }
        UAtlEvtHandwritingSubsystem* Handwriting = GameInstance->GetSubsystem<UAtlEvtHandwritingSubsystem>();
        if (!Handwriting) {
            return;
        }
        UMovieSceneSequence* MovieSeq = Player.State.FindSequence(Operand.SequenceID);
        if (!MovieSeq) {
            return;
        }
        for (FEvtCharaHandwritingPayload& Entry : Entries) {
            if (CondBranchData.IsCondition(Context, Operand, PersistentData, Player)) {
                UEnum* AtlHandwritingClass = FindObject<UEnum>(ANY_PACKAGE, TEXT("EAtlEvtHandwritingType"));
                UE_LOG(AtlEvtCharaHandwriting, Display, TEXT("Handwriting: Show %s"), *AtlHandwritingClass->GetNameByIndex((int32)Entry.HandwritingType).ToString());
            }
        }
    }
};

FMovieSceneEvtCharaHandwritingSectionTemplate::FMovieSceneEvtCharaHandwritingSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtCharaHandwritingSectionTemplate::FMovieSceneEvtCharaHandwritingSectionTemplate(const UMovieSceneEvtCharaHandwritingSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtCharaHandwritingSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    //ExecutionTokens.Add(FEvtCharaHandwritingExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
void FMovieSceneEvtCharaHandwritingSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    bool bIsPlaying = Context.GetDirection() == EPlayDirection::Forwards && Context.GetRange().Size<FFrameTime>() >= FFrameTime(0) && bFireEventsWhenForwards;
    if (!bIsPlaying) {
        return;
    }
    // Check that the target event data payload entry wraps inside the given swept range
    if (EventData.KeyValues.Num() != EventData.Times.Num()) {
        return;
    }
    TArray<FEvtCharaHandwritingPayload> PayloadEntries;
    for (int i = 0; i < EventData.Times.Num(); i++) {
        const FFrameNumber& CurrFrame = EventData.Times[i];
        if (CurrFrame >= SweptRange.GetLowerBoundValue() && CurrFrame < SweptRange.GetUpperBoundValue()) {
            PayloadEntries.Add(EventData.KeyValues[i]);
        }
    }
    if (PayloadEntries.Num() > 0) {
        ExecutionTokens.Add(FEvtCharaHandwritingExecutionToken(PayloadEntries, CondBranchData));
    }
}