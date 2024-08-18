#include "AppNpcComp.h"

void UAppNpcComp::SetFootForBP(int32 ID) {
}

void UAppNpcComp::SetCosTexID(int32 Index) {
}

ANpcBaseCore* UAppNpcComp::GetBaseCore() const {
    return NULL;
}

UAppNpcComp::UAppNpcComp(const FObjectInitializer& ObjectInitializer)
:Super (ObjectInitializer){
    this->mBaseCore_ = NULL;
    this->Loader = NULL;
}

