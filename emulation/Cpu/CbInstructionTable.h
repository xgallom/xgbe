//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_CBINSTRUCTIONTABLE_H
#define XGBE_CBINSTRUCTIONTABLE_H

#include "Instructions.h"

extern const Instruction::Handler CbInstructionTable[Instructions::InstructionsCount];
extern const char CbInstructionNameTable[Instructions::InstructionsCount][Instructions::MaxInstructionNameSize];

#endif //XGBE_CBINSTRUCTIONTABLE_H
