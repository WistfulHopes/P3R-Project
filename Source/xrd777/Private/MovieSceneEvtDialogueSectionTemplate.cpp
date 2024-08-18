// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "MovieSceneEvtDialogueSectionTemplate.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogEvtDialogueSectionTemplate, Log, All);

struct FEvtDialogueExecutionToken : IMovieSceneExecutionToken {
    TArray<FEvtDialoguePayload> Entries;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtDialogueExecutionToken(const TArray<FEvtDialoguePayload>& Entries, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : Entries(Entries), CondBranchData(CondBranchData) {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {
        // 0x14acdb750 (PERSONA3 RELOAD 1.0.0.0 Win64)
        UObject* PlaybackContext = Player.GetPlaybackContext();
        UWorld* World = PlaybackContext ? PlaybackContext->GetWorld() : nullptr;
        if (!World) {
            return;
        }
        if (!CondBranchData.IsCondition(Context, Operand, PersistentData, Player)) {
            return;
        }
        for (FEvtDialoguePayload& Entry : Entries) {
            int32 CurrFrame = Context.GetTime().GetFrame().Value / (Context.GetFrameRate().Numerator / 30);
            UE_LOG(LogEvtDialogueSectionTemplate, Display, TEXT("AtlEventAnimation_MessageNo%03d START FrameNumber:%d"), Entry.MessageNo, CurrFrame);
            if (Entry.BmdAsset && Entry.BmdAsset->mBuf.Num() > 0) {
                AActor** EventManagerMaybe = World->GetCurrentLevel()->Actors.FindByPredicate([](AActor*& CurrActor) { return CurrActor->IsA<AAtlEvtEventManager>(); });
                if (EventManagerMaybe) {
                    Cast<AAtlEvtEventManager>(*EventManagerMaybe)->ExecuteBmdDialog(Player.GetPlaybackContext(), Entry);
                    /*
                    AAtlEvtEventManager* EventManager = Cast<AAtlEvtEventManager>(*EventManagerMaybe);
                    AAtlEvtLevelSequenceActor* LevelSequenceActor = EventManager->GetAtlEvtLevelSequenceActor(Player.GetPlaybackContext());
                    if (LevelSequenceActor && LevelSequenceActor->SequencePlayer) {

                        EventManager->CurrentBmdPage = Entry.MessagePageID;
                        if (Entry.bPauseSequencer) {
                            LevelSequenceActor->SequencePlayer->Pause();
                        }
                        if (Entry.bWithSelect) {
                            EventManager->ExecuteBmdMessageWithSelect(Entry.BmdAsset, Entry.MessageMajorID, Entry.MessageMinorID, Entry.MessageSubID, Entry.MessagePageID, Entry.SelectMessageMajorID, Entry.SelectMessageMinorID, Entry.SelectMessageSubID, Entry.SelectResponceToLocalDataID, Entry.bMessageRefAffected, Entry.SeqEventMessageID);
                        }
                        else {
                            EventManager->ExecuteBmdMessage(Entry.BmdAsset, Entry.MessageMajorID, Entry.MessageMinorID, Entry.MessageSubID, Entry.MessagePageID, Entry.bMessageRefAffected, Entry.SeqEventMessageID);
                        }
                    }
                    else if (LevelSequenceActor) {
                        UE_LOG(LogEvtDialogueSectionTemplate, Error, TEXT("Sequence Player is null! Cannot pause sequencer!"));
                    }
                    else {
                        UE_LOG(LogEvtDialogueSectionTemplate, Error, TEXT("Level Sequence Actor is missing!!!"));
                    }
                    */
                }
            }
        }
    }
};

FMovieSceneEvtDialogueSectionTemplate::FMovieSceneEvtDialogueSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}

FMovieSceneEvtDialogueSectionTemplate::FMovieSceneEvtDialogueSectionTemplate(const UMovieSceneEvtDialogueSection& InSection)
    : EventData(InSection.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true),
    CondBranchData(InSection.CondBranchData)
{}

void FMovieSceneEvtDialogueSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    //ExecutionTokens.Add(FEvtDialogueExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}

void FMovieSceneEvtDialogueSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    bool bIsPlaying = Context.GetDirection() == EPlayDirection::Forwards && Context.GetRange().Size<FFrameTime>() >= FFrameTime(0) && bFireEventsWhenForwards;
    if (!bIsPlaying) {
        return;
    }
    // Check that the target event data payload entry wraps inside the given swept range
    TArray<FEvtDialoguePayload> PayloadEntries;
    if (EventData.KeyValues.Num() != EventData.Times.Num()) {
        return;
    }
    for (int i = 0; i < EventData.Times.Num(); i++) {
        const FFrameNumber& CurrFrame = EventData.Times[i];
        if (CurrFrame >= SweptRange.GetLowerBoundValue() && CurrFrame < SweptRange.GetUpperBoundValue()) {
            PayloadEntries.Add(EventData.KeyValues[i]);
        }
    }
    if (PayloadEntries.Num() > 0) {
        ExecutionTokens.Add(FEvtDialogueExecutionToken(PayloadEntries, CondBranchData));
    }
}