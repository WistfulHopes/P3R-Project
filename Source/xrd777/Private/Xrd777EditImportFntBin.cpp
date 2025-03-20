// (C)ATLUS. (C)SEGA.
#if WITH_EDITORONLY_DATA

#include "Xrd777EditImportFntBin.h"
#include "Misc/FileHelper.h"
#include "Serialization/MemoryReader.h"

Xrd777EditImportFntBin::Xrd777EditImportFntBin() {}

Xrd777EditImportFntBin::~Xrd777EditImportFntBin() {}

FArchive& operator<<(FArchive& Ar, FFNTEntry& OutTable) {
    Ar << OutTable.ResId;
    Ar << OutTable.Major;
    Ar << OutTable.Minor;
    Ar << OutTable.Sub;
    Ar << OutTable.fileid;
    Ar << OutTable.motion;
    Ar << OutTable.script;
    Ar << OutTable.bitflag0;
    Ar << OutTable.bitflag1;
    Ar << OutTable.personalRadius;
    Ar << OutTable.socialRadius;
    Ar << OutTable.greetingScript;
    Ar << OutTable.NpcCond;
    Ar << OutTable.Field28;
    Ar << OutTable.Flags;
    Ar << OutTable.Scale;
    Ar << OutTable.Radius;
    Ar << OutTable.SearchRadius;
    Ar << OutTable.SearchCenterOffset;
    Ar << OutTable.findOutScript;
    Ar << OutTable.catchupScript;
    Ar << OutTable.chaseSpeed;
    Ar << OutTable.questID;
    Ar << OutTable.flower;
    for (int i = 0; i < 4; i++) {
        uint16 CurrIdx;
        Ar << CurrIdx;
        OutTable.nodeIdx[i] = CurrIdx;
    }
    for (int i = 0; i < 4; i++) {
        uint16 CurrIdx;
        Ar << CurrIdx;
        OutTable.nodeScript[i] = CurrIdx;
    }
    Ar << OutTable.npcTxtIdx;
    Ar << OutTable.personalAngle;
    Ar << OutTable.structSize;
    Ar << OutTable.npcId;
	return Ar;
}

void Xrd777EditImportFntBin::ImportFnt(FString& Path) {
    TArray<uint8> FntBinary;
    bool bLoadSuccess = FFileHelper::LoadFileToArray(FntBinary, *Path);
    if (!bLoadSuccess) {
        return;
    }

    TArrayView<const uint8> BufData = TArrayView<const uint8>((const uint8*)FntBinary.GetData(), FntBinary.Num());
    FMemoryReaderView BufReader = FMemoryReaderView(BufData);
    while (BufReader.Tell() < FntBinary.Num()) {
        FFNTEntry NewEntry;
        BufReader << NewEntry;
        if (TArray<FFNTEntry>* FntEntries = FntBlocks.Find((int32)NewEntry.ResId)) {
            FntEntries->Add(NewEntry);
        }
        else {
            FntBlocks.Add((int32)NewEntry.ResId, TArray<FFNTEntry>(&NewEntry, 1));
        }
        //BufReader << FntBlocks.AddDefaulted_GetRef();
    }
}

#endif