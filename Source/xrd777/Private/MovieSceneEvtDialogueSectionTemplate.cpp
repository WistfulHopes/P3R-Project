// (C)ATLUS. (C)SEGA. :3

#pragma once

#include "MovieSceneEvtDialogueSectionTemplate.h"

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
    bFireEventsWhenBackwards(false),
    bFireEventsWhenForwards(false)
{}

void FMovieSceneEvtDialogueSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtDialogueExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}
