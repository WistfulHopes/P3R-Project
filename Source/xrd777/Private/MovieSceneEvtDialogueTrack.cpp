#include "MovieSceneEvtDialogueTrack.h"
#include <xrd777/Public/MovieSceneEvtDialogueSection.h>
#include <xrd777/Public/MovieSceneEvtDialogueSectionTemplate.h>
#include "Tracks/MovieSceneSpawnTrack.h"
#include "IMovieSceneTracksModule.h"
#include "Logging/LogMacros.h"

#define LOCTEXT_NAMESPACE "MovieSceneEvtDialogueTrack"

DEFINE_LOG_CATEGORY_STATIC(LogEvtDialogueTrackReal, Log, All);

UMovieSceneEvtDialogueTrack::UMovieSceneEvtDialogueTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtDialogueTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtDialogueTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtDialogueTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtDialogueTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtDialogueTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtDialogueSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtDialogueTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtDialogueSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtDialogueTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtDialogueTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}

FMovieSceneEvalTemplatePtr UMovieSceneEvtDialogueTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const {
	return FMovieSceneEvtDialogueSectionTemplate(*CastChecked<UMovieSceneEvtDialogueSection>(&InSection));
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtDialogueTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Dialog");
}
#endif

EMovieSceneCompileResult UMovieSceneEvtDialogueTrack::CustomCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	return Compile(Track, Args);
}

void UMovieSceneEvtDialogueTrack::PostCompile(FMovieSceneEvaluationTrack& Track, const FMovieSceneTrackCompilerArgs& Args) const {
	Track.SetEvaluationGroup(IMovieSceneTracksModule::GetEvaluationGroupName(EBuiltInEvaluationGroup::PreEvaluation));
	Track.SetEvaluationPriority(UMovieSceneSpawnTrack::GetEvaluationPriority() - 100);
	Track.SetEvaluationMethod(EEvaluationMethod::Swept);

	for (int i = 0; i < Track.GetChildTemplates().Num(); i++) {
		((FMovieSceneEvtDialogueSectionTemplate&)Track.GetChildTemplate(i)).CondBranchData = CondBranchData;
	}
}

#undef LOCTEXT_NAMESPACE

