#include "MovieSceneEvtAdxSoundFadeTrack.h"
#include <xrd777/Public/MovieSceneEvtAdxSoundFadeSection.h>
#include <xrd777/Public/MovieSceneEvtAdxSoundFadeSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtAdxSoundFadeTrack"

UMovieSceneEvtAdxSoundFadeTrack::UMovieSceneEvtAdxSoundFadeTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtAdxSoundFadeTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtAdxSoundFadeTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtAdxSoundFadeTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtAdxSoundFadeTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtAdxSoundFadeTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtAdxSoundFadeSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtAdxSoundFadeTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtAdxSoundFadeSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtAdxSoundFadeTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtAdxSoundFadeTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtAdxSoundFadeTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtAdxSoundFadeSectionTemplate(*CastChecked<UMovieSceneEvtAdxSoundFadeSection>(&InSection));
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtAdxSoundFadeTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Adx Sound Fade");
}
#endif

/*
EMovieSceneCompileResult UMovieSceneEvtAdxSoundFadeTrack::CustomCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(FName(TEXT("SpawnObjects")));
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);
	Track.SetEvaluationPriority(3995);
	return Compile(Track, Args);
}
*/

void UMovieSceneEvtAdxSoundFadeTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtAdxSoundFadeSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

#undef LOCTEXT_NAMESPACE