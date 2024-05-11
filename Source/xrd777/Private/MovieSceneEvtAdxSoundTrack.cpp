#include "MovieSceneEvtAdxSoundTrack.h"
#include <xrd777/Public/MovieSceneEvtAdxSoundSection.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtAdxSoundTrack"

UMovieSceneEvtAdxSoundTrack::UMovieSceneEvtAdxSoundTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtAdxSoundTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtAdxSoundTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtAdxSoundTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtAdxSoundTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtAdxSoundTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtAdxSoundSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtAdxSoundTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtAdxSoundSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtAdxSoundTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtAdxSoundTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtAdxSoundTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtAdxSoundSectionTemplate(*CastChecked<UMovieSceneEvtAdxSoundSection>(&InSection));
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtAdxSoundTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Adx Sound");
}
#endif

/*
EMovieSceneCompileResult UMovieSceneEvtAdxSoundTrack::CustomCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(FName(TEXT("SpawnObjects")));
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);
	Track.SetEvaluationPriority(3995);
	return Compile(Track, Args);
}
*/

void UMovieSceneEvtAdxSoundTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::SpawnObjects));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

}

#undef LOCTEXT_NAMESPACE