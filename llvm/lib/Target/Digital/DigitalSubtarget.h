//===-- DigitalSubtarget.h - Define Subtarget for the Digital ----*- C++
//-*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Digital specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_DIGITAL_SUBTARGET_H
#define LLVM_TARGET_DIGITAL_SUBTARGET_H

#include "DigitalISelLowering.h"
#include "DigitalFrameLowering.h"
#include "DigitalInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/CodeGen/TargetFrameLowering.h"

#define GET_SUBTARGETINFO_HEADER
#include "DigitalGenSubtargetInfo.inc"

namespace llvm {

class DigitalSubtarget : public DigitalGenSubtargetInfo {
  virtual void anchor();
  bool ExtendedInsts;

public:
  /// This constructor initializes the data members to match that
  /// of the specified triple.
  ///
  DigitalSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS, const TargetMachine &TM);

  DigitalSubtarget &initializeSubtargetDependencies(StringRef CPU,
                                                    StringRef FS);

  const DigitalFrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const DigitalInstrInfo *getInstrInfo() const override { 
	  return &InstrInfo; 
  }
  const DigitalRegisterInfo *getRegisterInfo() const override {
    return &RegInfo;
  }
  
  const DigitalTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }

  /// ParseSubtargetFeatures - Parses features string setting specified
  /// subtarget options.  Definition of function is auto generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

  private:
    DigitalFrameLowering FrameLowering;
    DigitalInstrInfo InstrInfo;
    DigitalRegisterInfo RegInfo;
    DigitalTargetLowering TLInfo;
    SelectionDAGTargetInfo TSInfo;
};
} // namespace llvm

#endif // LLVM_TARGET_DIGITAL_SUBTARGET_H