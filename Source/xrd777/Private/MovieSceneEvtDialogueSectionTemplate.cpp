// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "MovieSceneEvtDialogueSectionTemplate.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY_STATIC(LogEvtDialogueSectionTemplate, Log, All);

struct FEvtDialogueExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtDialogueSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventRecievers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtDialogueExecutionToken(const FMovieSceneEvtDialogueSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventRecievers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : EventData(EventData), EventRecievers(EventRecievers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards), CondBranchData(CondBranchData)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

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
    ExecutionTokens.Add(FEvtDialogueExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}

void FMovieSceneEvtDialogueSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtDialogueExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}