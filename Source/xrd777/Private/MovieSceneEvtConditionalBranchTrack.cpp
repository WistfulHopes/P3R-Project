#include "MovieSceneEvtConditionalBranchTrack.h"

UMovieSceneEvtConditionalBranchTrack::UMovieSceneEvtConditionalBranchTrack(const FObjectInitializer& Init)
	: Super(Init)
{
	CondBranchData = FMovieSceneEvtConditionalBranchData();
}