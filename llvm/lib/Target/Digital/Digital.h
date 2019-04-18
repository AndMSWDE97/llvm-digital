//===-- Digital.h - Top-level interface for Digital representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===--------------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// Digital back-end.
//
//===-------------------------------------------------------------------------===//

#ifndef TARGET_DIGITAL_H
#define TARGET_DIGITAL_H

#include "MCTargetDesc/DigitalMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class DigitalTargetMachine;
  class FunctionPass;
  class AsmPrinter;
  class MCInst;
  class MachineInstr;

  FunctionPass *createDigitalISelDag(DigitalTargetMachine &TM);

} // end namespace llvm;

#endif