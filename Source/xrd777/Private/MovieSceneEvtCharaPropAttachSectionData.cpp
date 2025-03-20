#include "MovieSceneEvtCharaPropAttachSectionData.h"

FMovieSceneEvtCharaPropAttachSectionData::FMovieSceneEvtCharaPropAttachSectionData() {
}

void FMovieSceneEvtCharaPropAttachSectionData::GetKeys(const TRange<FFrameNumber>& WithinRange, TArray<FFrameNumber>* OutKeyTimes, TArray<FKeyHandle>* OutKeyHandles)
{
	GetData().GetKeys(WithinRange, OutKeyTimes, OutKeyHandles);
}

void FMovieSceneEvtCharaPropAttachSectionData::GetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<FFrameNumber> OutKeyTimes)
{
	GetData().GetKeyTimes(InHandles, OutKeyTimes);
}

void FMovieSceneEvtCharaPropAttachSectionData::SetKeyTimes(TArrayView<const FKeyHandle> InHandles, TArrayView<const FFrameNumber> InKeyTimes)
{
	GetData().SetKeyTimes(InHandles, InKeyTimes);
}

void FMovieSceneEvtCharaPropAttachSectionData::DuplicateKeys(TArrayView<const FKeyHandle> InHandles, TArrayView<FKeyHandle> OutNewHandles)
{
	GetData().DuplicateKeys(InHandles, OutNewHandles);
}

void FMovieSceneEvtCharaPropAttachSectionData::DeleteKeys(TArrayView<const FKeyHandle> InHandles)
{
	GetData().DeleteKeys(InHandles);
}

void FMovieSceneEvtCharaPropAttachSectionData::DeleteKeysFrom(FFrameNumber InTime, bool bDeleteKeysBefore)
{
	GetData().DeleteKeysFrom(InTime, bDeleteKeysBefore);
}

void FMovieSceneEvtCharaPropAttachSectionData::ChangeFrameResolution(FFrameRate SourceRate, FFrameRate DestinationRate)
{
	GetData().ChangeFrameResolution(SourceRate, DestinationRate);
}

TRange<FFrameNumber> FMovieSceneEvtCharaPropAttachSectionData::ComputeEffectiveRange() const
{
	return GetData().GetTotalRange();
}

int32 FMovieSceneEvtCharaPropAttachSectionData::GetNumKeys() const
{
	return Times.Num();
}

void FMovieSceneEvtCharaPropAttachSectionData::Reset()
{
	Times.Reset();
	KeyValues.Reset();
	KeyHandles.Reset();
}

void FMovieSceneEvtCharaPropAttachSectionData::Offset(FFrameNumber DeltaPosition)
{
	GetData().Offset(DeltaPosition);
}