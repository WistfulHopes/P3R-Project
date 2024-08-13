// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtSeqControllerSectionTemplate.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtSeqController, Log, All);

struct FEvtSeqControllerExecutionToken: IMovieSceneExecutionToken {
    TArray<FEvtSeqControllerPayload> Entries;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtSeqControllerExecutionToken(const TArray<FEvtSeqControllerPayload>& Entries, const FMovieSceneEvtConditionalBranchData& CondBranchData)
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
        for (TWeakObjectPtr<> BoundObject : Player.FindBoundObjects(Operand)) {
            if (UObject* InObject = BoundObject.Get()) {
                if (InObject->IsA<AAtlEvtEventManager>()) {
                    AAtlEvtEventManager* EventManager = Cast<AAtlEvtEventManager>(InObject);
                    for (FEvtSeqControllerPayload& Entry : Entries) {
                        AAtlEvtLevelSequenceActor* LevelSequenceActor = EventManager->GetAtlEvtLevelSequenceActor(PlaybackContext);
                        switch (Entry.Operation) {
                        case EEvtSeqControllerOperation::WaitingMessage:
                            // wait message given a particular message ID
                            if (
                                EventManager->CurrentEvtDialoguePayload.SeqEventMessageID == Entry.ClosedEventMessageID
                                && EventManager->MessageState != EEventManagerMessageState::EndMessage
                                ) {
                                LevelSequenceActor->SequencePlayer->Pause();
                            }
                            break;
                        case EEvtSeqControllerOperation::FinishSequencer:
                            LevelSequenceActor->SequencePlayer->GoToEndAndStop();
                            break;
                        case EEvtSeqControllerOperation::PlayAndJumpToSec:
                            LevelSequenceActor->SequencePlayer->SetPlaybackPosition(FMovieSceneSequencePlaybackParams(Entry.JumpToSec, EUpdatePositionMethod::Jump));
                            break;
                        case EEvtSeqControllerOperation::Pause:
                            LevelSequenceActor->SequencePlayer->Pause();
                            break;
                        case EEvtSeqControllerOperation::ViewFieldCamera:
                            UE_LOG(AtlEvtSeqController, Error, TEXT("TODO: View Field Camera"));
                            break;
                        case EEvtSeqControllerOperation::ViewSequencerCamera:
                            UE_LOG(AtlEvtSeqController, Error, TEXT("TODO: View Sequencer Camera"));
                            break;
                        case EEvtSeqControllerOperation::TransitionLightScenarioSublevel:
                            UE_LOG(AtlEvtSeqController, Error, TEXT("TODO: Transition Light Scenario Sublevel"));
                            break;
                        case EEvtSeqControllerOperation::WaitTransitionLightScenarioSublevel:
                            UE_LOG(AtlEvtSeqController, Error, TEXT("TODO: Wait Transition Light Scenario Sublevel"));
                            break;
                        default:
                            UE_LOG(AtlEvtSeqController, Error, TEXT("Invalid sequence controller ID %d!!"), (int32)Entry.Operation);
                            break;
                        }
                    }
                }
                else {
                    UE_LOG(AtlEvtSeqController, Error, TEXT("Bound object should only be the event manager!!!!"));
                }
            }
        }
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
    //ExecutionTokens.Add(FEvtSeqControllerExecutionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}

void FMovieSceneEvtSeqControllerSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    bool bIsPlaying = Context.GetDirection() == EPlayDirection::Forwards && Context.GetRange().Size<FFrameTime>() >= FFrameTime(0) && bFireEventsWhenForwards;
    if (!bIsPlaying) {
        return;
    }
    // Check that the target event data payload entry wraps inside the given swept range
    TArray<FEvtSeqControllerPayload> PayloadEntries;
    for (int i = 0; i < EventData.Times.Num(); i++) {
        const FFrameNumber& CurrFrame = EventData.Times[i];
        if (CurrFrame >= SweptRange.GetLowerBoundValue() && CurrFrame < SweptRange.GetUpperBoundValue()) {
            PayloadEntries.Add(EventData.KeyValues[i]);
        }
    }
    if (PayloadEntries.Num() > 0) {
        ExecutionTokens.Add(FEvtSeqControllerExecutionToken(PayloadEntries, CondBranchData));
    }
}