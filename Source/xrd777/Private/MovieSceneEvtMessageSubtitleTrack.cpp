#include "MovieSceneEvtMessageSubtitleTrack.h"
#include <xrd777/Public/MovieSceneEvtMessageSubtitleSection.h>
#include <xrd777/Public/MovieSceneEvtMessageSubtitleSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"
#include "Evaluation/MovieSceneEvaluationTrack.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtSeqControllerTrack"

UMovieSceneEvtMessageSubtitleTrack::UMovieSceneEvtMessageSubtitleTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtMessageSubtitleTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtMessageSubtitleTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtMessageSubtitleTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtMessageSubtitleTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtMessageSubtitleTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtMessageSubtitleSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtMessageSubtitleTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtMessageSubtitleSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtMessageSubtitleTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtMessageSubtitleTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtMessageSubtitleTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Msg Subtitle");
}
#endif

void UMovieSceneEvtMessageSubtitleTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtMessageSubtitleSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtMessageSubtitleTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtMessageSubtitleSectionTemplate(*CastChecked<UMovieSceneEvtMessageSubtitleSection>(&InSection));
}

#undef LOCTEXT_NAMESPACE