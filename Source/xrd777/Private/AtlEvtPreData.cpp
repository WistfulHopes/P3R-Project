#include "AtlEvtPreData.h"

FAtlEvtPreData::FAtlEvtPreData() {
    // See default constructor in UAtlEvtSubsystem::GetEvtPreData
    this->EventMajorID = -1;
    this->EventMinorID = -1;
    this->EventCategoryTypeID = -1;
    this->bDisableAutoLoadFirstLightingScenarioLevel = false;
    this->bForceDisableUseCurrentTimeZone = false;
    this->ForcedCldTimeZoneValue = 0;
    this->ForceMonth = 0;
    this->ForceDay = 0;
}

