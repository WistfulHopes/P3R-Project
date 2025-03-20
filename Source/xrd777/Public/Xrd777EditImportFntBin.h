// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#pragma once

#include "CoreMinimal.h"

struct FFNTEntry {
public:
    uint16 ResId;
    uint16 Major;
    uint16 Minor;
    uint16 Sub;
    uint16 fileid;
    uint16 motion;
    uint32 script;
    uint32 bitflag0;
    uint32 bitflag1;
    float personalRadius;
    float socialRadius;
    uint32 greetingScript;
    uint32 NpcCond;
    uint32 Field28;
    uint32 Flags;
    float Scale;
    float Radius;
    float SearchRadius;
    float SearchCenterOffset;
    uint32 findOutScript;
    uint32 catchupScript;
    float chaseSpeed;
    uint32 questID;
    uint32 flower;
    uint16 nodeIdx[4];
    uint16 nodeScript[4];
    uint32 npcTxtIdx;
    float personalAngle;
    uint32 structSize;
    uint32 npcId;
    friend FArchive& operator<<(FArchive& Ar, FFNTEntry& OutTable);
};

/**
 * 
 */
class XRD777_API Xrd777EditImportFntBin
{
public:
	Xrd777EditImportFntBin();
	~Xrd777EditImportFntBin();
    //TArray<FFNTEntry> FntBlocks;
    TMap<int32, TArray<FFNTEntry>> FntBlocks;
    void ImportFnt(FString& Path);
};

#endif