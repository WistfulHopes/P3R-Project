#include "MovieSceneEvtCharaOperationControllerTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaOperationControllerSection.h>
#include <xrd777/Public/MovieSceneEvtCharaOperationControllerSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"
#include "Evaluation/MovieSceneEvaluationTrack.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaOperationControllerTrack"

UMovieSceneEvtCharaOperationControllerTrack::UMovieSceneEvtCharaOperationControllerTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtCharaOperationControllerTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaOperationControllerTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaOperationControllerTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaOperationControllerTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaOperationControllerTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaOperationControllerSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaOperationControllerTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaOperationControllerSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaOperationControllerTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaOperationControllerTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaOperationControllerTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Operation Controller");
}
#endif

FMovieSceneEvalTemplatePtr UMovieSceneEvtCharaOperationControllerTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtCharaOperationControllerSectionTemplate(*CastChecked<UMovieSceneEvtCharaOperationControllerSection>(&InSection));
}

void UMovieSceneEvtCharaOperationControllerTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtCharaOperationControllerSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}

}

#undef LOCTEXT_NAMESPACE

