#include "MovieSceneEvtConditionalBranchData.h"

DEFINE_LOG_CATEGORY_STATIC(AtlEvtConditionalBranch, Log, All);

FMovieSceneEvtConditionalBranchData::FMovieSceneEvtConditionalBranchData() {
    this->ConditionalType = EEvtConditionalBranchType::AlwaysExecute;
    this->ConditionalNo = 0;
    this->ConditionalValue = 0;
    this->CompareType = EEvtConditionalBranchCompType::Equal;
}

bool FMovieSceneEvtConditionalBranchData::IsCondition(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) {
    // 0x1410d5e00 (PERSONA3 RELOAD 1.0.0.0 Win64)
    if (ConditionalType == EEvtConditionalBranchType::AlwaysExecute) {
        return true;
    }
    else if (ConditionalType == EEvtConditionalBranchType::RefFromGlobalFlag ||
        ConditionalType == EEvtConditionalBranchType::RefFromGlobalCounter) {
        return GetCompareResult(ConditionalNo);
    }
    else if (ConditionalType == EEvtConditionalBranchType::RefFromLocal) {
        AAtlEvtEventManager* EventManager = nullptr;
        for (TWeakObjectPtr<> BoundObject : Player.FindBoundObjects(Operand)) {
            UObject* InObject = BoundObject.Get();
            if (InObject && InObject->IsA<AAtlEvtEventManager>()) {
                EventManager = Cast<AAtlEvtEventManager>(InObject);
                break;
            }
        }
        if (!EventManager) {
            UE_LOG(AtlEvtConditionalBranch, Error, TEXT("[FMovieSceneEvtConditionalBranchData::IsCondition] No Binding Actor!! Please Bind a AAtlEvtEventManager Actor!!"));
            return false;
        }
        if (EventManager->GetWorld()->WorldType != EWorldType::PIE) {
            UE_LOG(AtlEvtConditionalBranch, Error, TEXT("[FMovieSceneEvtConditionalBranchData::IsCondition] Please run check in PIEPlay!!"));
            return false;
        }
        UAtlEvtSubsystem* EvtSubsystem = EventManager->GetWorld()->GetGameInstance()->GetSubsystem<UAtlEvtSubsystem>();
        return GetCompareResult(EvtSubsystem->GetLocalData(ConditionalNo));
    }
    return false;
}

bool FMovieSceneEvtConditionalBranchData::GetCompareResult(int32 CompareValue) {
    switch (CompareType) {
        case EEvtConditionalBranchCompType::Equal:
            return CompareValue == ConditionalValue;
        case EEvtConditionalBranchCompType::Not:
            return CompareValue != ConditionalValue;
        case EEvtConditionalBranchCompType::LessThan:
            return CompareValue < ConditionalValue;
        case EEvtConditionalBranchCompType::GreaterThan:
            return CompareValue > ConditionalValue;
        case EEvtConditionalBranchCompType::Less:
            return CompareValue <= ConditionalValue;
        case EEvtConditionalBranchCompType::Greater:
            return CompareValue >= ConditionalValue;
        default:
            UE_LOG(AtlEvtConditionalBranch, Error, TEXT("[FMovieSceneEvtConditionalBranchData::IsCondition] Wrong Compare Type[%d]!! Please Check Set the value!!"), (int32)CompareType);
            return false;
    }
}