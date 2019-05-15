//===-- DigitalRegisterInfo.cpp - Digital Register Information ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Digital implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "DigitalRegisterInfo.h"
#include "Digital.h"
#include "DigitalSubtarget.h"
#include "DigitalTargetMachine.h"
#include "MCTargetDesc/DigitalABIInfo.h"
#include "DigitalMachineFunction.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include <cstdint>

using namespace llvm;

#define DEBUG_TYPE "digital-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "DigitalGenRegisterInfo.inc"

DigitalRegisterInfo::DigitalRegisterInfo(): DigitalGenRegisterInfo(Digital::R1) {}

const MCPhysReg *
DigitalRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_Digital_SaveList;
}

BitVector DigitalRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  
  //const DigitalSubtarget &Subtarget = MF.getSubtarget<DigitalSubtarget>();

  // Use markSuperRegs to ensure any register aliases are also reserved
  markSuperRegs(Reserved, Digital::BP); // BP
  markSuperRegs(Reserved, Digital::SP); // SP
  markSuperRegs(Reserved, Digital::RA); // RA
  assert(checkAllSuperRegsMarked(Reserved));
  return Reserved;
}

bool DigitalRegisterInfo::requiresRegisterScavenging(
    const MachineFunction & /*MF*/) const {
  return true;
}

bool DigitalRegisterInfo::trackLivenessAfterRegAlloc(
    const MachineFunction & /*MF*/) const {
  return true;
}

void DigitalRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                            int SPAdj, unsigned FIOperandNum,
                                            RegScavenger *RS) const {
  report_fatal_error("Subroutines not supported yet");
}

bool DigitalRegisterInfo::hasBasePointer(const MachineFunction &MF) const {
  const MachineFrameInfo &MFI = MF.getFrameInfo();
  // When we need stack realignment and there are dynamic allocas, we can't
  // reference off of the stack pointer, so we reserve a base pointer.
  if (needsStackRealignment(MF) && MFI.hasVarSizedObjects())
    return true;

  return false;
}

unsigned DigitalRegisterInfo::getRARegister() const { return Digital::RA; }

unsigned
DigitalRegisterInfo::getFrameRegister(const MachineFunction & /*MF*/) const {
  return Digital::R8;
}

unsigned DigitalRegisterInfo::getBaseRegister() const { return Digital::BP; }

const uint32_t *
DigitalRegisterInfo::getCallPreservedMask(const MachineFunction & /*MF*/,
                                        CallingConv::ID /*CC*/) const {
  return CSR_Digital_RegMask;
}
