#include "BmdAsset.h"

DEFINE_LOG_CATEGORY_STATIC(BmdAssetDebug, Log, All);

FArchive& operator<<(FArchive& Ar, BmdBinaryHeader& Header) {
	Ar.Seek(8);
	int32 MagicCheckEndian;
	Ar << MagicCheckEndian;
#if PLATFORM_LITTLE_ENDIAN
	if (MagicCheckEndian == BmdBinaryHeader::GetBigEndianMagic()) {
#else
	if (MagicCheckEndian == BmdBinaryHeader::GetittleEndianMagic()) {
#endif
		Ar.SetByteSwapping(true);
	}
	Ar.Seek(0);
	Ar << Header.FileType;
	Ar << Header.Format;
	Ar << Header.UserId;
	Ar << Header.FileSize;
	Ar << Header.Magic;
	Ar << Header.ExtSize;
	Ar << Header.ptrRelocationTable;
	Ar << Header.szRelocationTable;
	Ar << Header.DialogCount;
	Ar << Header.bIsRelocated;
	Ar << Header.Reserved;
	Ar << Header.Version;
	return Ar;
}

FArchive& operator<<(FArchive& Ar, BmdBinaryDialogHeader& Header) {
	int32 DialogKind;
	Ar << DialogKind;
	Header.DialogKind = (BmdBinaryDialogKind)DialogKind;
	Ar << Header.ptrData;
	return Ar;
}

FArchive& operator<<(FArchive& Ar, BmdBinarySpeakerHeader& Header) {
	Ar << Header.ptrSpeakers;
	Ar << Header.SpeakerCount;
	Ar << Header.pExtData;
	Ar << Header.Reserved;
	return Ar;
}

FArchive& operator<<(FArchive& Ar, BmdBinaryMessage& Header) {
	int16 PageCount;
	Ar << PageCount;
	Ar << Header.SpeakerId;
	Header.PageOffsets.Reserve(PageCount);
	Header.PageOffsets.SetNum(PageCount);
	for (int i = 0; i < PageCount; i++) {
		Ar << Header.PageOffsets[i];
	}
	Ar << Header.TokenSize;
	return Ar;
}

FArchive& operator<<(FArchive& Ar, BmdBinarySelectionDialog& Header) {
	Ar << Header.Ext;
	int16 OptionCount;
	Ar << OptionCount;
	int16 Pattern;
	Ar << Pattern;
	Ar << Header.Reserved;
	Header.Pattern = (BmdBinarySelectionDialogPattern)Pattern;
	Header.OptionOffsets.Reserve(OptionCount);
	Header.OptionOffsets.SetNum(OptionCount);
	for (int i = 0; i < OptionCount; i++) {
		Ar << Header.OptionOffsets[i];
	}
	Ar << Header.TokenSize;
	return Ar;
}

BmdFunctionToken* BmdDialogBase::ReadFunctionToken(FArchive& Ar, uint8 FirstByte) {
	checkf(FirstByte == 0xfe, TEXT("First byte for function token should always be 0xFE"));
	uint16 FnHeader;
	Ar << FnHeader;

	uint8 TableIndex = (FnHeader >> 0x5) & 7;
	uint8 FunctionIndex = FnHeader & 0x1f;
	uint8 FunctionSize = (FnHeader & 0xf00) >> 7;
	BmdFunctionToken* NewFunction = new BmdFunctionToken(TableIndex, FunctionIndex, (FunctionSize - 2) / 2);
	for (int i = 0; i < NewFunction->Parameters.Num(); i++) {
		Ar << NewFunction->Parameters[i];
		NewFunction->Parameters[i] = ((NewFunction->Parameters[i] & 0xff) - 1) << 8 | ((NewFunction->Parameters[i] & 0xff00) - 1) >> 8;
	}
	//UE_LOG(BmdAssetDebug, Display, TEXT("Read Function token at %d: %s"), Ar.Tell(), *NewFunction->PrintValue());
	return NewFunction;
}
BmdMessageToken* BmdDialogBase::ReadMessageToken(FArchive& Ar, uint8 FirstByte) {
	TArray<uint8> Bytes;
	Bytes.Add(FirstByte);
	while (Bytes.Last() != 0xa) {
		Ar << Bytes.AddDefaulted_GetRef();
	}
	Bytes.Add(0);
	BmdMessageToken* NewMessage = new BmdMessageToken(Bytes);
	//UE_LOG(BmdAssetDebug, Display, TEXT("Read Message token at %d: %s"), Ar.Tell(), *NewMessage->PrintValue());
	return NewMessage;
}

BmdMessageToken* BmdDialogSelection::ReadMessageToken(FArchive& Ar, uint8 FirstByte) {
	TArray<uint8> Bytes;
	Bytes.Add(FirstByte);
	while (Bytes.Last() != 0x0) {
		Ar << Bytes.AddDefaulted_GetRef();
	}
	//Bytes.Add(0);
	BmdMessageToken* NewMessage = new BmdMessageToken(Bytes);

	// Align to nearest 4 bytes

	int32 StreamAlign = Ar.Tell() % 0x4;
	if (StreamAlign != 0) {
		int32 StreamDiff = 0x4 - StreamAlign;
		Ar.Seek(Ar.Tell() + StreamDiff);
	}

	return NewMessage;
}

// Read through a list of pages worth of tokens
void BmdDialogBase::ReadDialogTokens(FArchive& Ar, TArray<int32>& Offsets, int64 DialogBase, int32 TokenSize) {
	// Page offsets indicate start of page
	int32 CurrentPage = 0;
	int32 StartPos = Ar.Tell();
	uint8 CurrentByte;
	do {
		if (CurrentPage < Offsets.Num() - 1 && Ar.Tell() >= DialogBase + Offsets[CurrentPage + 1]) {
			CurrentPage++;
		}
		if (Ar.Tell() > StartPos + TokenSize) {
			// Check if we exceeded the dialog token size - this can happen with selection dialogs after stream alignment
			break;
		}
		Ar << CurrentByte;
		if (CurrentByte == 0xfe) {
			TSharedPtr<BmdTokenBase> NewFunc(ReadFunctionToken(Ar, CurrentByte));
			Pages[CurrentPage].Add(NewFunc);
		}
		else if (CurrentByte != 0) {
			TSharedPtr<BmdTokenBase> NewMsg(ReadMessageToken(Ar, CurrentByte));
			Pages[CurrentPage].Add(NewMsg);
		}
	} while (CurrentByte != 0);
	//return Ar;
}

FArchive& operator<<(FArchive& Ar, BmdData& Data) {
	// Read the BMD header. This will also set the appropriate endianness for the reader
	Ar << Data.BinaryHeader;
	int64 DialogBase = Ar.Tell();
	TArray<BmdBinaryDialogHeader> BinaryDialogs;
	BinaryDialogs.Reserve(Data.BinaryHeader.DialogCount);
	BinaryDialogs.SetNum(Data.BinaryHeader.DialogCount, false);
	for (int i = 0; i < Data.BinaryHeader.DialogCount; i++) {
		Ar << BinaryDialogs[i];
	}
	BmdBinarySpeakerHeader SpeakerHeader;
	Ar << SpeakerHeader;

	Data.Speakers.Reserve(SpeakerHeader.SpeakerCount);
	Data.Speakers.SetNum(SpeakerHeader.SpeakerCount);

	// Get speaker strings
	Ar.Seek(DialogBase + SpeakerHeader.ptrSpeakers);
	TArray<int32> pSpeakers;
	pSpeakers.Reserve(SpeakerHeader.SpeakerCount);
	pSpeakers.SetNum(SpeakerHeader.SpeakerCount);
	for (int i = 0; i < SpeakerHeader.SpeakerCount; i++) {
		Ar << pSpeakers[i];
	}
	for (int i = 0; i < SpeakerHeader.SpeakerCount; i++) {
		Ar.Seek(DialogBase + pSpeakers[i]);
		TArray<int8> SpeakerBytes;
		while (SpeakerBytes.Num() == 0 || SpeakerBytes.Last() != 0) {
			Ar << SpeakerBytes.AddDefaulted_GetRef();
		}
		Data.Speakers[i] = FString(UTF8_TO_TCHAR(SpeakerBytes.GetData()));
	}

	// Collect function + text tokens for each message and selection

	for (BmdBinaryDialogHeader& BinaryDialog : BinaryDialogs) {
		check((int32)BinaryDialog.DialogKind < 2);
		Ar.Seek(DialogBase + BinaryDialog.ptrData);
		ANSICHAR Name[0x18];
		Ar.Serialize(Name, 0x18);
		if (BinaryDialog.DialogKind == BmdBinaryDialogKind::Message) {
			BmdBinaryMessage MessageBlock;
			Ar << MessageBlock;
			TSharedRef<BmdDialogMessage> NewMessage(new BmdDialogMessage(FString(UTF8_TO_TCHAR(Name)), MessageBlock.PageOffsets.Num(), Data.GetSpeakerName(MessageBlock.SpeakerId)));
			NewMessage.Get().ReadDialogTokens(Ar, MessageBlock.PageOffsets, DialogBase, MessageBlock.TokenSize);
			Data.Dialogs.Add(NewMessage.Get().Name, NewMessage);
		}
		else {
			BmdBinarySelectionDialog SelectionBlock;
			Ar << SelectionBlock;
			TSharedRef<BmdDialogSelection> NewSelection(new BmdDialogSelection(FString(UTF8_TO_TCHAR(Name)), SelectionBlock.OptionOffsets.Num()));
			NewSelection.Get().ReadDialogTokens(Ar, SelectionBlock.OptionOffsets, DialogBase, SelectionBlock.TokenSize);
			Data.Dialogs.Add(NewSelection.Get().Name, NewSelection);
		}
	}
	return Ar;
}

UBmdAsset::UBmdAsset() {
}

