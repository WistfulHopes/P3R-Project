// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA
#include "Xrd777EditImportFtd.h"
#include "Misc/FileHelper.h"
#include "Serialization/MemoryReader.h"

FArchive& operator<<(FArchive& Ar, FFtdTable& OutTable) {
	Ar.Seek(Ar.Tell() + sizeof(int32));
	Ar << OutTable.Magic;
#if PLATFORM_LITTLE_ENDIAN
	if (OutTable.Magic == FFtdTable::GetBigEndianMagic()) {
		Ar.SetByteSwapping(true);
	}
#else
	if (OutTable.Magic == FFtdTable::GetLittleEndianMagic()) {
		Ar.SetByteSwapping(true);
	}
#endif
	Ar.Seek(0);
	Ar << OutTable.Field00;
	Ar.Seek(Ar.Tell() + sizeof(int32));
	Ar << OutTable.FileSize;
	Ar << OutTable.DataType;
	Ar << OutTable.DataCount;
	OutTable.Data.Reserve(OutTable.DataCount);
	OutTable.Data.SetNum(OutTable.DataCount);
	// TODO: Support data FTDs (string FTDs only)
	for (int i = 0; i < OutTable.DataCount; i++) {
		int32 DataOffset;
		Ar << DataOffset;
		int32 NextOffset = Ar.Tell();
		Ar.Seek(DataOffset);

		int8 StrLength;
		Ar << StrLength;
		Ar.Seek(Ar.Tell() + 3);
		//OutTable.Data[i].Reserve(StrLength * sizeof(TCHAR));
		TArray<int8> StrRaw;
		StrRaw.Reserve(StrLength);
		Ar.Serialize(StrRaw.GetData(), StrLength);
		OutTable.Data[i] = FString(ANSI_TO_TCHAR((ANSICHAR*)StrRaw.GetData()));

		Ar.Seek(NextOffset);
	}
	return Ar;
}

Xrd777EditImportFtd::Xrd777EditImportFtd() {

}

void Xrd777EditImportFtd::ImportFtd(FString& Path) {
	TArray<uint8> FtdBinary;
	bool bLoadSuccess = FFileHelper::LoadFileToArray(FtdBinary, *Path);
	if (!bLoadSuccess) {
		return;
	}

	TArrayView<const uint8> BufData = TArrayView<const uint8>((const uint8*)FtdBinary.GetData(), FtdBinary.Num());
	FMemoryReaderView BufReader = FMemoryReaderView(BufData);
	BufReader << Table;
}

#endif