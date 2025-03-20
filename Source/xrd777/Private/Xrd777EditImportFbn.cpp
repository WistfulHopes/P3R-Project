// (C)ATLUS. (C)SEGA. :3
#if WITH_EDITORONLY_DATA

#include "Xrd777EditImportFbn.h"
#include "Misc/FileHelper.h"
#include "Serialization/MemoryReader.h"

DEFINE_LOG_CATEGORY_STATIC(FbnAssetDebug, Log, All);

FArchive& operator<<(FArchive& Ar, FFbnBlock& Block) {
    int32 ListPosStart = Ar.Tell();
    int32 sType;
	Ar << sType;
	Block.Type = (EFbnListType)sType;
    UE_LOG(FbnAssetDebug, Display, TEXT("At FBN offset %x: type %d"), ListPosStart, sType);
	Ar << Block.Version;
	Ar << Block.Size;
	Ar << Block.ListOffset;
	if (Block.Size > 0x10) {
        Block.ReadList(Ar, Block.BlockEntries);
	}
    if (Ar.Tell() < ListPosStart + Block.Size) {
		Ar.Seek(ListPosStart + Block.Size);
    }
	return Ar;
}

void FFbnBlock::ReadList(FArchive& Ar, TArray<int8*>& ListOut) {
    int32 EntryCount;
    Ar << EntryCount;
	ListOut.Reserve(EntryCount);
    Ar.Seek(Ar.Tell() + sizeof(int32) * 3);
    for (int i = 0; i < EntryCount; i++) {
        int8* NewBlockEntry = nullptr;
        switch (Type) {
            case FBN_Trigger:             
                NewBlockEntry = (int8*)new FFbnTriggerVolume(Ar, Version);
                break;
            case FBN_Entrance:            
                NewBlockEntry = (int8*)new FFbnEntrance(Ar, Version);
                break;
            case FBN_Hit:
                Ar.SetByteSwapping(false);
                NewBlockEntry = (int8*)new FFbnHitDefinition(Ar, Version);
                Ar.SetByteSwapping(true);
                break;
            case FBN_WanderShadow:        
				NewBlockEntry = (int8*)new FFbnWanderShadow(Ar, Version);
				break;
            case FBN_Chest:               
                NewBlockEntry = (int8*)new FFbnTreasureChest(Ar, Version);
                break;
            case FBN_Cover:               
                NewBlockEntry = (int8*)new FFbnCoverPoints(Ar, Version);
                break;
            case FBN_PatrolShadow:        
                NewBlockEntry = (int8*)new FFbnPatrolShadow(Ar, Version);
                break;
            case FBN_MementosHit:         
                NewBlockEntry = (int8*)new FFbnTriggerVolume(Ar, Version);
                break; 
            case FBN_MementosEntrance:    
                NewBlockEntry = (int8*)new FFbnEntrance(Ar, Version);
                break; 
            case FBN_Npc:                 
                NewBlockEntry = (int8*)new FFbnNpc(Ar, Version);
                break;
            case FBN_SearchObject:        
                NewBlockEntry = (int8*)new FFbnSearchObject(Ar, Version);
                break;
            case FBN_SearchObjectHit:     
                NewBlockEntry = (int8*)new FFbnTriggerVolume(Ar, Version);
                break;
            case FBN_WarningObject:       
                NewBlockEntry = (int8*)new FFbnWarningObject(Ar, Version);
                break;
            case FBN_VoiceHit:            
                NewBlockEntry = (int8*)new FFbnTriggerVolume(Ar, Version);
                break;
            case FBN_GrappleObject:       
                NewBlockEntry = (int8*)new FFbnGrappleObject(Ar, Version);
                break;
            case FBN_GrappleTrigger:      
                NewBlockEntry = (int8*)new FFbnGrappleTrigger(Ar, Version);
                break;
            case FBN_MementosEntrance_2:  
                NewBlockEntry = (int8*)new FFbnEntrance(Ar, Version);
                break;
        }
        if (NewBlockEntry) {
            BlockEntries.Add(NewBlockEntry);
        }
    }
}

FFbnTriggerVolume::FFbnTriggerVolume(FArchive& Ar, int32 Version) {
    Ar << TriggerEnabled;
    Ar << HTBIndex;
    int8 sShape;
    Ar << sShape;
    Shape = (ETriggerShape)sShape;
    Ar << Unk08;
    int8 sHitRegisterDirection;
    Ar << sHitRegisterDirection;
    HitRegisterDirection = (ETriggerDirection)sHitRegisterDirection;
    Ar << SphereCenter;
    Ar << Unk01;
    Ar << Unk02;
    Ar << Unk03;
    Ar << SphereRadiusX;
    Ar << SphereRadiusY;
    Ar << Unk05;
    Ar << CubeBottomRight;
    Ar << CubeTopRight;
    Ar << CubeBottomLeft;
    Ar << CubeTopLeft;
    Ar << Unk06;
    Ar << Unk07;
}

FFbnEntrance::FFbnEntrance(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << Unk01;
    Ar << Position;
    Ar << Rotation;
    Ar << EntranceID;
    Ar << Unk02;
}

FFbnHitDefinition::FFbnHitDefinition(FArchive& Ar, int32 Version) {
    Ar.Seek(Ar.Tell() + (sizeof(int) * 6) + 1); // skip bitflags and padding byte
    int8 sHitType;
    Ar << sHitType; // :ADAHCI:
    HitType = (EHitType)sHitType;
    Ar << NameID;
    Ar << ProcedureIndex;
    int16 sPromptType;
    Ar << sPromptType;
    PromptType = (EPromptTypeList)sPromptType;
    Ar.Seek(Ar.Tell() + sizeof(int) * 7);
}

FFbnWanderShadow::FFbnWanderShadow(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << Unk01;
    Ar << Unk02;
    Ar << Position;
    Ar << Rotation;
    Ar << WanderRadius;
    Ar << Unk04;
}

FFbnTreasureChest::FFbnTreasureChest(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << Position;
    Ar << Rotation;
    Ar << Model_MajorID;
    Ar << Model_MinorID;
    Ar << Chest_ResourceHandle;
    Ar << Unk01;

}

FFbnCoverPoints::FFbnCoverPoints(FArchive& Ar, int32 Version) {
    int32 sBehavior;
    Ar << sBehavior;
    Behavior = (ECoverBehaviorFlags)sBehavior;
    Ar << Unk00;
    Ar << Point1_JokerPosition;
    Ar << Point2_JokerPosition;
    Ar << Point1_PartyRotation;
    Ar << Point2_PartyRotation;
    Ar << Point1_IconPosition;
    Ar << Point2_IconPosition;
    Ar << Point1_CameraRotation;
    Ar << Point2_CameraRotation;
    Ar << Unk01;
    Ar << Field94;
    Ar << Field98;
    if (Version != 0x12051700) {
        Ar << CameraHeightMode;
        Ar << ConnectedPoint_ID;
        Ar << BitflagSection;
        Ar << BitflagFlag;
        Ar << Point1_JokerRotation; 
        Ar << Point2_JokerRotation;
    }
}

FFbnPatrolShadow::FFbnPatrolShadow(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << ShadowSpeed;
    Ar << Unk01;
    Ar << DoesShadowExist;
    Ar << Unk02;
    Ar << Unk03;
    Ar << PathNodeCount;
    Ar << Unk04;
    for (int i = 0; i < PathNodeCount; i++) {
        Ar << ShadowPathNode.AddDefaulted_GetRef();
    }
    for (int i = 0; i < PathNodeCount; i++) {
        Ar << Test.AddDefaulted_GetRef();
    }
}

FFbnNpc::FFbnNpc(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << Unk01;
    Ar << NPCRotation;
    Ar << Unk02;
    Ar << Unk03;
    Ar << FNT_ID;
    Ar << Unk04;
    Ar << Unk05;
    Ar << Unk06;
    Ar << Unk07;
    Ar << PathNodeCount;
    Ar << Unk08;
    for (int i = 0; i < PathNodeCount; i++) {
        Ar << PathNodes.AddDefaulted_GetRef();
    }
}

FFbnSearchObject::FFbnSearchObject(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << Unk01;
    Ar << Unk02;
    Ar << Position;
    Ar << Rotation;
    Ar << Model_MajorID;
    Ar << Model_MinorID;
    Ar << SearchObject_ResourceHandle;
    Ar << Unk03;
}

FFbnWarningObject::FFbnWarningObject(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << Position;
    Ar << Rotation;
    Ar << Field30;
    Ar << Field31;
    Ar << Field32;
    Ar << Model_MajorID;
    Ar << Model_MinorID;
    Ar << Gimmick_ResourceHandle;
    Ar << Unk03;
    Ar << Unk04;
    if (Version >= 0x15102300) {
        Ar << ActiveTimer;
        Ar << InactiveTime;
    }
    else {
        ActiveTimer = 3.0f;
        InactiveTime = 3.0f;
    }
}

FFbnGrappleObject::FFbnGrappleObject(FArchive& Ar, int32 Version) {
    Ar << Unk00;
    Ar << bJumpAfterGrapple;
    Ar << bJumpAfterGrapple2;
    Ar << Wire_SequenceID;
    Ar << Position;
    Ar << Rotation;
    Ar << Model_MajorID;
    Ar << Model_MinorID;
    Ar << Grapple_ResourceHandle;
    Ar << Unk01;
    Ar << JumpLength;
    Ar << JumpHeight;
}

FFbnGrappleTrigger::FFbnGrappleTrigger(FArchive& Ar, int32 Version) {
    Ar << TriggerEnabled;
    Ar << HTBIndex;
    int8 sShape;
    Ar << sShape;
    Shape = (ETriggerShape)sShape;
    Ar << Unk01;
    int8 sHitRegisterDirection;
    Ar << sHitRegisterDirection;
    HitRegisterDirection = (ETriggerDirection)sHitRegisterDirection;
    Ar << Grapple_ResourceHandle;
    Ar << Unk03;
    Ar << Center;
    Ar << Unk04;
    Ar << Unk05;
    Ar << Unk06;
    Ar << Scale;
    Ar << Unk07;
    Ar << Unk08;
    Ar << BottomRight;
    Ar << TopRight;
    Ar << BottomLeft;
    Ar << TopLeft;
    Ar << Unk09;
    Ar << Unk10;
}

Xrd777EditImportFbn::Xrd777EditImportFbn() {

}

Xrd777EditImportFbn::~Xrd777EditImportFbn() {

}

void Xrd777EditImportFbn::ImportFbn(FString& Filename) {
    TArray<uint8> FbnBinary;
    bool bLoadSuccess = FFileHelper::LoadFileToArray(FbnBinary, *Filename);
    if (!bLoadSuccess) {
        return;
    }

    TArrayView<const uint8> BufData = TArrayView<const uint8>((const uint8*)FbnBinary.GetData(), FbnBinary.Num());
    FMemoryReaderView BufReader = FMemoryReaderView(BufData);
#if PLATFORM_LITTLE_ENDIAN
    BufReader.SetByteSwapping(true);
#endif
    while (BufReader.Tell() < FbnBinary.Num()) {
        BufReader << FbnBlocks.AddDefaulted_GetRef();
    }
}

#endif