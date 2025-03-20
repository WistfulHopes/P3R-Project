#include "FldCrowdWalkBpParam.h"

FFldCrowdWalkBpParam::FFldCrowdWalkBpParam() {
    this->mMobBpClass = NULL;
}

FFldCrowdWalkBpParam::FFldCrowdWalkBpParam(const TSubclassOf<AMobWalkCharaBaseCore>& InClass) {
    this->mMobBpClass = InClass;
}

