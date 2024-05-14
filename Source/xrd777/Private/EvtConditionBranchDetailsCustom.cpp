// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "EvtConditionBranchDetailsCustom.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "EvtConditionalBranchDetails"

void FEvtConditionBranchDetailsCustom::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) {
    DetailBuilder.HideCategory(TrackClass->GetFName());
    DetailBuilder.HideCategory(FName(TEXT("Track")));
    DetailBuilder.HideCategory(FName(TEXT("General")));
}

#undef LOCTEXT_NAMESPACE

#endif