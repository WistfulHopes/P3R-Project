// (C)ATLUS. (C)SEGA. :3

#include "MovieSceneEvtCharaAnimationSectionTemplate.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtCharaAnimTemplate, Log, All);

struct FEvtCharaAnimationExectionToken : IMovieSceneExecutionToken {
    TArray<FEvtCharaAnimationPayload> Entries;
    FMovieSceneEvtConditionalBranchData CondBranchData;

    FEvtCharaAnimationExectionToken(const TArray<FEvtCharaAnimationPayload>& Entries, const FMovieSceneEvtConditionalBranchData& CondBranchData)
        : Entries(Entries), CondBranchData(CondBranchData) {}

    virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override {
        // 0x1410bdef0 (PERSONA3 RELOAD 1.0.0.0 Win64)
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
                USkeletalMeshComponent* MeshComp = UBFLEventMovieScene::SkeletalMeshComponentFromObject(InObject);
                if (!MeshComp) {
                    continue;
                }
                for (FEvtCharaAnimationPayload& Entry : Entries) {
                    if (Entry.Animation) {
                        int32 CurrFrame = Context.GetTime().GetFrame().Value / (Context.GetFrameRate().Numerator / 30);
                        UE_LOG(AtlEvtCharaAnimTemplate, Display, TEXT("AtlEventAnimation_%s START FrameNumber:%d"), *Entry.Animation->GetName(), CurrFrame);
                    }
                    UAnimInstance* AnimInst = MeshComp->GetAnimInstance();
                    FName SlotNameStr;
                    switch (Entry.SlotType) {
                    case EEvtCharaAnimationSlotType::DefaultSlot:
                        SlotNameStr = FName("DefaultSlot");
                        break;
                    case EEvtCharaAnimationSlotType::EventSlot:
                        SlotNameStr = FName("EventSlot");
                        break;
                    case EEvtCharaAnimationSlotType::NodSlot:
                        SlotNameStr = FName("NodSlot");
                        break;
                    case EEvtCharaAnimationSlotType::FacialSlot:
                        SlotNameStr = FName("FacialSlot");
                        break;
                    case EEvtCharaAnimationSlotType::ArmL:
                        SlotNameStr = FName("Arm L");
                        break;
                    case EEvtCharaAnimationSlotType::ArmR:
                        SlotNameStr = FName("Arm R");
                        break;
                    default:
                        SlotNameStr = Entry.SlotName;
                        break;
                    }
                    if (SlotNameStr != NAME_None) {
                        if (Entry.AnimArray.Num() == 0) {
                            UAnimMontage* CurrMontage = nullptr;
                            switch (Entry.CharaAnimationType) {
                            case EEvtCharaAnimationType::SimpleMontage:
                                CurrMontage = UBFLEventMovieScene::CreateSlotOffsetAnimationAsDynamicMontage(
                                    MeshComp->SkeletalMesh,
                                    Entry.Animation,
                                    SlotNameStr,
                                    Entry.StartOffset,
                                    Entry.EndOffset,
                                    Entry.BlendIn,
                                    Entry.BlendOut,
                                    Entry.PlayRate,
                                    1,
                                    -1.0f,
                                    0.0f
                                );
                                if (CurrMontage && AnimInst) {
                                    AnimInst->Montage_Play(CurrMontage, Entry.PlayRate, EMontagePlayReturnType::MontageLength, Entry.EndOffset, true);
                                }
                                break;
                            case EEvtCharaAnimationType::LoopAnimationSingle:
                                CurrMontage = UBFLEventMovieScene::CreateSlotOffsetAnimationAsDynamicMontage(
                                    MeshComp->SkeletalMesh,
                                    Entry.Animation,
                                    SlotNameStr,
                                    Entry.StartOffset,
                                    Entry.EndOffset,
                                    Entry.BlendIn,
                                    Entry.BlendOut,
                                    Entry.PlayRate,
                                    1,
                                    -1.0f,
                                    0.0f
                                );
                                if (CurrMontage && AnimInst) {
                                    AnimInst->Montage_Play(CurrMontage, Entry.PlayRate, EMontagePlayReturnType::MontageLength, Entry.EndOffset, true);
                                    FName DefaultName = FName("Default");
                                    AnimInst->Montage_SetNextSection(DefaultName, DefaultName);
                                }
                                break;
                            case EEvtCharaAnimationType::LoopAnimationOnLastFrame:
                                UBFLEventMovieScene::PlaySlotAnimationAsDynamicMontageLoopSecOnLastFrame(
                                    AnimInst,
                                    MeshComp->SkeletalMesh,
                                    Entry.Animation,
                                    SlotNameStr,
                                    Entry.StartOffset,
                                    Entry.EndOffset,
                                    Entry.BlendIn,
                                    Entry.BlendOut,
                                    Entry.PlayRate,
                                    1,
                                    -1.0f,
                                    0.0f
                                );
                                break;
                            case EEvtCharaAnimationType::StopSlotAnimation:
                                if (AnimInst) {
                                    UBFLEventMovieScene::StopSlotAnimation(AnimInst, Entry.BlendOut, SlotNameStr);
                                }
                                break;
                            case EEvtCharaAnimationType::LoopAnimationSingleWithStartOffset:
                                UBFLEventMovieScene::PlaySlotMultiAnimationOffsetAsDynamicMontageTwo(
                                    AnimInst,
                                    MeshComp->SkeletalMesh,
                                    Entry.Animation,
                                    Entry.Animation,
                                    SlotNameStr,
                                    Entry.StartOffset,
                                    Entry.EndOffset,
                                    Entry.BlendIn,
                                    Entry.BlendOut,
                                    Entry.PlayRate,
                                    1,
                                    -1.0f,
                                    0.0f
                                );
                                break;
                            }
                        }
                        else {
                            if (
                                Entry.CharaAnimationType == EEvtCharaAnimationType::SimpleMontage ||
                                Entry.CharaAnimationType == EEvtCharaAnimationType::LoopAnimationSingle ||
                                Entry.CharaAnimationType == EEvtCharaAnimationType::LoopAnimationOnLastFrame ||
                                Entry.CharaAnimationType == EEvtCharaAnimationType::LoopAnimationSingleWithStartOffset
                                ) {
                                UBFLEventMovieScene::PlaySlotMultiAnimationAsDynamicMontage(
                                    AnimInst,
                                    MeshComp->SkeletalMesh,
                                    Entry.Animation,
                                    Entry.AnimArray,
                                    SlotNameStr,
                                    Entry.CharaAnimationType,
                                    Entry.BlendIn,
                                    Entry.BlendOut,
                                    Entry.PlayRate,
                                    1,
                                    -1.0f,
                                    0.0f
                                );
                            }
                            else if (Entry.CharaAnimationType == EEvtCharaAnimationType::StopSlotAnimation) {
                                if (AnimInst) {
                                    AnimInst->StopSlotAnimation(Entry.BlendOut);
                                }
                            }
                        }
                    }
                }
            }
        }
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
    //ExecutionTokens.Add(FEvtCharaAnimationExectionToken(EventData, bFireEventsWhenForwards, bFireEventsWhenBackwards, CondBranchData));
}

void FMovieSceneEvtCharaAnimationSectionTemplate::EvaluateSwept(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const TRange<FFrameNumber>& SweptRange, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const {
    bool bIsPlaying = Context.GetDirection() == EPlayDirection::Forwards && Context.GetRange().Size<FFrameTime>() >= FFrameTime(0) && bFireEventsWhenForwards;
    if (!bIsPlaying) {
        return;
    }
    // Check that the target event data payload entry wraps inside the given swept range
    if (EventData.KeyValues.Num() != EventData.Times.Num()) {
        return;
    }
    TArray<FEvtCharaAnimationPayload> PayloadEntries;
    for (int i = 0; i < EventData.Times.Num(); i++) {
        const FFrameNumber& CurrFrame = EventData.Times[i];
        if (CurrFrame >= SweptRange.GetLowerBoundValue() && CurrFrame < SweptRange.GetUpperBoundValue()) {
            PayloadEntries.Add(EventData.KeyValues[i]);
        }
    }
    if (PayloadEntries.Num() > 0) {
        ExecutionTokens.Add(FEvtCharaAnimationExectionToken(PayloadEntries, CondBranchData));
    }
}