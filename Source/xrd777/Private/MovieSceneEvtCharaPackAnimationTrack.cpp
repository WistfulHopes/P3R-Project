#include "MovieSceneEvtCharaPackAnimationTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaPackAnimationSection.h>
#include <xrd777/Public/MovieSceneEvtCharaPackAnimationSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"
#include "Evaluation/MovieSceneEvaluationTrack.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaPackAnimationTrack"

UMovieSceneEvtCharaPackAnimationTrack::UMovieSceneEvtCharaPackAnimationTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtCharaPackAnimationTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaPackAnimationTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaPackAnimationTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaPackAnimationTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaPackAnimationTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaPackAnimationSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaPackAnimationTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaPackAnimationSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaPackAnimationTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaPackAnimationTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaPackAnimationTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Pack Anim");
}
#endif

void UMovieSceneEvtCharaPackAnimationTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtCharaPackAnimationSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtCharaPackAnimationTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtCharaPackAnimationSectionTemplate(*CastChecked<UMovieSceneEvtCharaPackAnimationSection>(&InSection));
}

#undef LOCTEXT_NAMESPACE