//===- DigitalMachineFuctionInfo.h - Digital machine function -*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares Digital-specific per-machine-function information.
//
//===----------------------------------------------------------------------===//

#ifndef DIGITALFUNCTIONINFO_H
#define DIGITALFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"

namespace llvm {

/// DigitalMachineFunctionInfo - This class is derived from MachineFunction and
/// contains private Digital target-specific information for each MachineFunction.
class DigitalFunctionInfo : public MachineFunctionInfo {
  virtual void anchor();

  /// CalleeSavedFrameSize - Size of the callee-saved register portion of the
  /// stack frame in bytes.
  unsigned CalleeSavedFrameSize;

  /// ReturnAddrIndex - FrameIndex for return slot.
  int ReturnAddrIndex;

  /// BytesToPopOnReturn - Number of bytes function pops on return (in addition
  /// to the space used by the return address).
  /// Used on windows platform for stdcall & fastcall name decoration
  unsigned BytesToPopOnReturn = 0;

public:
  DigitalFunctionInfo() : CalleeSavedFrameSize(0) {}

  explicit DigitalFunctionInfo(MachineFunction &MF)
    : CalleeSavedFrameSize(0), ReturnAddrIndex(0) {}

  unsigned getCalleeSavedFrameSize() const { return CalleeSavedFrameSize; }
  void setCalleeSavedFrameSize(unsigned bytes) { CalleeSavedFrameSize = bytes; }

  int getRAIndex() const { return ReturnAddrIndex; }
  void setRAIndex(int Index) { ReturnAddrIndex = Index; }

  unsigned getBytesToPopOnReturn() const { return BytesToPopOnReturn; }
};

} // End llvm namespace

#endif
