#include "MovieSceneEvtCharaPropAttachTrack.h"
#include <xrd777/Public/MovieSceneEvtCharaPropAttachSection.h>

#define LOCTEXT_NAMESPACE "MovieSceneEvtCharaPropAttachTrack"

UMovieSceneEvtCharaPropAttachTrack::UMovieSceneEvtCharaPropAttachTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	bFireEventsWhenForwards = true;
	bFireEventsWhenBackwards = true;
}

bool UMovieSceneEvtCharaPropAttachTrack::IsEmpty() const
{
	return Sections.Num() == 0;
}


void UMovieSceneEvtCharaPropAttachTrack::AddSection(UMovieSceneSection& Section)
{
	Sections.Add(&Section);
}


void UMovieSceneEvtCharaPropAttachTrack::RemoveSection(UMovieSceneSection& Section)
{
	Sections.Remove(&Section);
}

void UMovieSceneEvtCharaPropAttachTrack::RemoveSectionAt(int32 SectionIndex)
{
	Sections.RemoveAt(SectionIndex);
}

bool UMovieSceneEvtCharaPropAttachTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneEvtCharaPropAttachSection::StaticClass();
}

UMovieSceneSection* UMovieSceneEvtCharaPropAttachTrack::CreateNewSection()
{
	return NewObject<UMovieSceneEvtCharaPropAttachSection>(this, NAME_None, RF_Transactional);
}

const TArray<UMovieSceneSection*>& UMovieSceneEvtCharaPropAttachTrack::GetAllSections() const
{
	return Sections;
}


bool UMovieSceneEvtCharaPropAttachTrack::HasSection(const UMovieSceneSection& Section) const
{
	return Sections.Contains(&Section);
}


#if WITH_EDITORONLY_DATA
FText UMovieSceneEvtCharaPropAttachTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("DisplayName", "Evt Chara Prop Attach");
}
#endif

#undef LOCTEXT_NAMESPACE

