#include "MovieSceneEvtScriptTrack.h"
#include <xrd777/Public/MovieSceneEvtScriptSection.h>
#include <xrd777/Public/MovieSceneEvtScriptSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtScriptTrack"

UMovieSceneEvtScriptTrack::UMovieSceneEvtScriptTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtScriptTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtScriptTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtScriptTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtScriptTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtScriptTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtScriptSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtScriptTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtScriptSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtScriptTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtScriptTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtScriptTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Script");
}
#endif

void UMovieSceneEvtScriptTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::PostEvaluation));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtScriptSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtScriptTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtScriptSectionTemplate(*CastChecked<UMovieSceneEvtScriptSection>(&InSection));
}

#undef LOCTEXT_NAMESPACE