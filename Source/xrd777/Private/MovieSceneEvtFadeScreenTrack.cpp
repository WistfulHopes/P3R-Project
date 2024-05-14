#include "MovieSceneEvtFadeScreenTrack.h"
#include <xrd777/Public/MovieSceneEvtFadeScreenSection.h>
#include <xrd777/Public/MovieSceneEvtFadeScreenSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtFadeScreenTrack"

UMovieSceneEvtFadeScreenTrack::UMovieSceneEvtFadeScreenTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtFadeScreenTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtFadeScreenTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtFadeScreenTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtFadeScreenTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtFadeScreenTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtFadeScreenSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtFadeScreenTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtFadeScreenSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtFadeScreenTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtFadeScreenTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtFadeScreenTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Fade Screen");
}
#endif

void UMovieSceneEvtFadeScreenTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtFadeScreenSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtFadeScreenTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtFadeScreenSectionTemplate(*CastChecked<UMovieSceneEvtFadeScreenSection>(&InSection));
}

#undef LOCTEXT_NAMESPACE
