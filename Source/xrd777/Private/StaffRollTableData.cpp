#include "StaffRollTableData.h"

FStaffRollTableData::FStaffRollTableData() {
    this->StaffRollIndex = 0;
    this->Ficolor = FColor(0, 0, 0, 255);
    this->Scolor = FColor(0, 0, 0, 255);
    this->Tcolor = FColor(0, 0, 0, 255);
    this->Focolor = FColor(0, 0, 0, 255);
    this->Fistyle = 0;
    this->Sstyle = 0;
    this->Tstyle = 0;
    this->Fostyle = 0;
    this->Fisize = 1;
    this->Ssize = 1;
    this->Tsize = 1;
    this->Fosize = 1;
    this->Command = 0;
    this->SecondCommand = 0;
    this->ThirdCommand = 0;
    this->ForthCommand = 0;
    this->LineCount = 0;
    this->LineCommand = false;
    this->EmptyCount = 0;
    this->StartWaitSeconds = 8.00f;
    this->FinishSeconds = 0.00f;
    this->LastSeconds = 0.00f;
}

