#include "MovieSceneEvtSeqTimeJumpControllerTrack.h"
#include <xrd777/Public/MovieSceneEvtSeqTimeJumpControllerSection.h>
#include <xrd777/Public/MovieSceneEvtSeqTimeJumpControllerSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"
#include "Evaluation/MovieSceneEvaluationTrack.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtSeqControllerTrack"

UMovieSceneEvtSeqTimeJumpControllerTrack::UMovieSceneEvtSeqTimeJumpControllerTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtSeqTimeJumpControllerTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtSeqTimeJumpControllerTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtSeqTimeJumpControllerTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtSeqTimeJumpControllerTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtSeqTimeJumpControllerTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtSeqTimeJumpControllerSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtSeqTimeJumpControllerTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtSeqTimeJumpControllerSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtSeqTimeJumpControllerTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtSeqTimeJumpControllerTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtSeqTimeJumpControllerTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Time Jump Controller");
}
#endif

void UMovieSceneEvtSeqTimeJumpControllerTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::PostEvaluation));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtSeqTimeJumpControllerSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtSeqTimeJumpControllerTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtSeqTimeJumpControllerSectionTemplate(*CastChecked<UMovieSceneEvtSeqTimeJumpControllerSection>(&InSection));
}

#undef LOCTEXT_NAMESPACE