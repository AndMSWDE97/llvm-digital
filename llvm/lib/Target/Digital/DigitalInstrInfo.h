//===-- DigitalInstrInfo.h - Digital Instruction Information --------*- C++
//-*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Digital implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_DIGITAL_DIGITALINSTRINFO_H
#define LLVM_LIB_TARGET_DIGITAL_DIGITALINSTRINFO_H

#include "Digital.h"
#include "DigitalRegisterInfo.h"
#include "MCTargetDesc/DigitalMCTargetDesc.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include <cstdint>

#define GET_INSTRINFO_HEADER
#include "DigitalGenInstrInfo.inc"

namespace llvm {

class MachineInstr;
class MachineOperand;
class DigitalSubtarget;
class TargetRegisterClass;
class TargetRegisterInfo;

class DigitalInstrInfo : public DigitalGenInstrInfo {
  virtual void anchor();

public:
  DigitalInstrInfo();
};

//const DigitalInstrInfo *createDigitalInstrInfo(const DigitalSubtarget &STI) {return new DigitalInstrInfo(STI);}
} // namespace llvm
#endif