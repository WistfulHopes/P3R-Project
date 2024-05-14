#include "MovieSceneEvtDialogueOptionsSectionTemplate.h"

struct FEvtDialogueOptionsExecutionToken : IMovieSceneExecutionToken {
    FMovieSceneEvtDialogueOptionsSectionData EventData;
    TArray<FMovieSceneObjectBindingID> EventReceivers;
    bool bFireEventsWhenForwards;
    bool bFireEventsWhenBackwards;

    FEvtDialogueOptionsExecutionToken(const FMovieSceneEvtDialogueOptionsSectionData& EventData, const TArray<FMovieSceneObjectBindingID>& EventReceivers,
        bool bFireEventsWhenForwards, bool bFireEventsWhenBackwards)
        : EventData(EventData), EventReceivers(EventReceivers), bFireEventsWhenForwards(bFireEventsWhenForwards),
        bFireEventsWhenBackwards(bFireEventsWhenBackwards)
    {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {

    }
};

FMovieSceneEvtDialogueOptionsSectionTemplate::FMovieSceneEvtDialogueOptionsSectionTemplate() {
    this->bFireEventsWhenForwards = false;
    this->bFireEventsWhenBackwards = false;
}


FMovieSceneEvtDialogueOptionsSectionTemplate::FMovieSceneEvtDialogueOptionsSectionTemplate(const UMovieSceneEvtDialogueOptionsSection& Section)
    : EventData(Section.EventData),
    bFireEventsWhenBackwards(true),
    bFireEventsWhenForwards(true)
{}

void FMovieSceneEvtDialogueOptionsSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtDialogueOptionsExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards));
}
void FMovieSceneEvtDialogueOptionsSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    ExecutionTokens.Add(FEvtDialogueOptionsExecutionToken(EventData, EventReceivers, bFireEventsWhenForwards, bFireEventsWhenBackwards));
}