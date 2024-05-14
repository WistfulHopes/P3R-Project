#include "MovieSceneEvtSeqControllerTrack.h"
#include <xrd777/Public/MovieSceneEvtSeqControllerSection.h>
#include <xrd777/Public/MovieSceneEvtSeqControllerSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtSeqControllerTrack"

UMovieSceneEvtSeqControllerTrack::UMovieSceneEvtSeqControllerTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtSeqControllerTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtSeqControllerTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtSeqControllerTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtSeqControllerTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtSeqControllerTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtSeqControllerSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtSeqControllerTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtSeqControllerSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtSeqControllerTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtSeqControllerTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtSeqControllerTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Sequence Controller");
}
#endif

void UMovieSceneEvtSeqControllerTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::PostEvaluation));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtSeqControllerSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtSeqControllerTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtSeqControllerSectionTemplate(*CastChecked<UMovieSceneEvtSeqControllerSection>(&InSection));
}

#undef LOCTEXT_NAMESPACE