// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "Xrd777EditImportClt.h"
#include "Misc/FileHelper.h"
#include "Serialization/MemoryReader.h"

Xrd777EditImportClt::Xrd777EditImportClt() {}

Xrd777EditImportClt::~Xrd777EditImportClt() {}

FModelledNPCHeader::FModelledNPCHeader(FArchive& Ar, uint32 Version) {
    Ar << blockCount;
    if (Version >= 0x14102500) {
        Ar << Flags;
        if (Version >= 0x14102800) {
            Ar << ClipEnd;
            if (Version >= 0x15041600) {
                Ar << ClipStart;
            }
        }
    }
    if (Version < 0x14102500) {
        Ar.Seek(Ar.Tell() + sizeof(int32) * 3);
    }
    else {
        Ar.Seek(Ar.Tell() + sizeof(int32) * 0xc);
    }
}

FArchive& operator<<(FArchive& Ar, FPathNodeContainer& Out) {
    Ar << Out.Field00;
    Ar << Out.Field04;
    Ar << Out.Field08;
    uint16 nodeCount;
    Ar << nodeCount;
    Ar << Out.Field0E;
    for (int i = 0; i < nodeCount; i++) {
        Ar << Out.positions.AddDefaulted_GetRef();
    }
    return Ar;
}

FArchive& operator<<(FArchive& Ar, FModelledNPCVariations& Out) {
    Ar << Out.crowdResrcEntry;
    Ar << Out.percentChance;
    return Ar;
}

FArchive& operator<<(FArchive& Ar, FModelledNPCData& Out) {
    int32 sFlags;
    Ar << sFlags;
    Out.flags = (EModelledNPCFlags)sFlags;
    Ar << Out.type;
    Ar << Out.startNode;
    Ar << Out.endNode;
    Ar << Out.Field0A;
    Ar << Out.Field0B;
    Ar << Out.Field0C;
    Ar << Out.Field0D;
    Ar << Out.Field0E;
    Ar << Out.Field0F;
    Ar << Out.Field10;
    Ar << Out.Field12;
    Ar << Out.Field13;
    Ar << Out.Field14;
    Ar << Out.Field16;
    Ar << Out.Field18;
    for (int i = 0; i < 5; i++) {
        FModelledNPCVariations NewNpcVariation;
        Ar << NewNpcVariation;
        Out.variations[i] = NewNpcVariation;
    }
    Ar << Out.Rotation;
    Ar << Out.SpawnFlags1;
    Ar << Out.SpawnFlags2;
    Ar << Out.spawnLimit;
    Ar << Out.spawnTime;
    Ar << Out.nodes;
    return Ar;
}
FArchive& operator<<(FArchive& Ar, FCutoutNPCHeader& Out) {
    Ar << Out.clipEnd;
    Ar << Out.clipStart;
    Ar << Out.count;
    Ar << Out.cutoutFlags;
    Ar << Out.Field10;
    Ar << Out.Field14;
    Ar << Out.Field18;
    Ar << Out.Field1C;
    return Ar;
}

void Xrd777EditImportClt::ImportClt(FString& Filename) {
    TArray<uint8> CltBinary;
    bool bLoadSuccess = FFileHelper::LoadFileToArray(CltBinary, *Filename);
    if (!bLoadSuccess) {
        return;
    }

    TArrayView<const uint8> BufData = TArrayView<const uint8>((const uint8*)CltBinary.GetData(), CltBinary.Num());
    FMemoryReaderView BufReader = FMemoryReaderView(BufData);
#if PLATFORM_LITTLE_ENDIAN
    BufReader.SetByteSwapping(true);
#endif
    BufReader << CltVersion;
    FModelledNPCHeader NpcHeader = FModelledNPCHeader(BufReader, CltVersion);
    for (int i = 0; i < (int32)NpcHeader.blockCount; i++) {
        BufReader << CrowdModels.AddZeroed_GetRef();
        //CrowdModels.Add(FModelledNPCData(BufReader, CltVersion));
    }
    if ((NpcHeader.Flags & 1) != 0) {
        FCutoutNPCHeader CutoutHeader;
        BufReader << CutoutHeader;
        for (int i = 0; i < (int32)CutoutHeader.count; i++) {
            BufReader << CrowdCutouts.AddDefaulted_GetRef();
        }
    }
}

#endif