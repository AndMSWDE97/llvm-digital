//===-- DigitalRegisterInfo.h - Digital Register Information Impl ---*- C++ -*-===//
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

#ifndef LLVM_LIB_TARGET_DIGITAL_DIGITALREGISTERINFO_H
#define LLVM_LIB_TARGET_DIGITAL_DIGITALREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "DigitalGenRegisterInfo.inc"

namespace llvm {

struct DigitalRegisterInfo : public DigitalGenRegisterInfo {

  DigitalRegisterInfo();

  const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                       CallingConv::ID) const override;

  // Code Generation virtual methods.
  const MCPhysReg *
  getCalleeSavedRegs(const MachineFunction *MF = nullptr) const override;

  BitVector getReservedRegs(const MachineFunction &MF) const override;

  bool requiresRegisterScavenging(const MachineFunction &MF) const override;

  bool trackLivenessAfterRegAlloc(const MachineFunction &MF) const override;

  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;

  // Debug information queries.
  unsigned getRARegister() const;
  unsigned getFrameRegister(const MachineFunction &MF) const override;
  unsigned getBaseRegister() const;
  bool hasBasePointer(const MachineFunction &MF) const;

  int getDwarfRegNum(unsigned RegNum, bool IsEH) const;
};
}

#endif