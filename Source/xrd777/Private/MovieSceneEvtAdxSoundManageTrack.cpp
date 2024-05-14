#include "MovieSceneEvtAdxSoundManageTrack.h"
#include <xrd777/Public/MovieSceneEvtAdxSoundManageSection.h>
#include <xrd777/Public/MovieSceneEvtAdxSoundManageSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtAdxSoundManageTrack"

UMovieSceneEvtAdxSoundManageTrack::UMovieSceneEvtAdxSoundManageTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtAdxSoundManageTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtAdxSoundManageTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtAdxSoundManageTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtAdxSoundManageTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtAdxSoundManageTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtAdxSoundManageSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtAdxSoundManageTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtAdxSoundManageSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtAdxSoundManageTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtAdxSoundManageTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtAdxSoundManageTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtAdxSoundManageSectionTemplate(*CastChecked<UMovieSceneEvtAdxSoundManageSection>(&InSection));
}



#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtAdxSoundManageTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Adx Sound Manage");
}
#endif

/*
EMovieSceneCompileResult UMovieSceneEvtAdxSoundManageTrack::CustomCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(FName(TEXT("SpawnObjects")));
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);
	Track.SetEvaluationPriority(3995);
	return Compile(Track, Args);
}
*/

void UMovieSceneEvtAdxSoundManageTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtAdxSoundManageSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

#undef LOCTEXT_NAMESPACE