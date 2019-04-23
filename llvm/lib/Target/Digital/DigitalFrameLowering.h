//===-- DigitalFrameLowering.h - Define frame lowering for Digital -*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class implements Digital-specific bits of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_DIGITAL_DIGITALFRAMELOWERING_H
#define LLVM_LIB_TARGET_DIGITAL_DIGITALFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class DigitalSubtarget;

class DigitalFrameLowering : public TargetFrameLowering {
public:
  explicit DigitalFrameLowering(const DigitalSubtarget &STI)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 1, -1) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

  bool hasFP(const MachineFunction &MF) const override;
};
}
#endif