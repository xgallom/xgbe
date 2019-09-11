//
// Created by Revolware Company on 2019-09-06.
//

#ifndef XGBE_INSTRUCTIONTABLE_H
#define XGBE_INSTRUCTIONTABLE_H

#include "Instructions.h"

extern const Instruction::Handler InstructionTable[Instructions::InstructionsCount];
extern const char InstructionNameTable[Instructions::InstructionsCount][Instructions::MaxInstructionNameSize];

#endif //XGBE_INSTRUCTIONTABLE_H
