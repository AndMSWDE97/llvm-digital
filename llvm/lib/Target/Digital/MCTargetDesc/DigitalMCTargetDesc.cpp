//===-- DigitalMCTargetDesc.cpp - Digital Target Descriptions ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Digital specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "DigitalMCTargetDesc.h"
#include "DigitalMCAsmInfo.h"
#include "InstPrinter/DigitalInstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_MC_DESC
#include "DigitalGenInstrInfo.inc"

//#define GET_SUBTARGETINFO_MC_DESC
//#include "DigitalGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "DigitalGenRegisterInfo.inc"

static MCInstrInfo *createDigitalMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitDigitalMCInstrInfo(X);
  return X;
}

static MCAsmInfo *createDigitalMCAsmInfo(const MCRegisterInfo &MRI,
                                      const Triple &TT) {
  MCAsmInfo *MAI = new DigitalELFMCAsmInfo(TT);

  unsigned SP = MRI.getDwarfRegNum(Digital::SP, true);
  MCCFIInstruction Inst = MCCFIInstruction::createDefCfa(nullptr, SP, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCRegisterInfo *createDigitalMCRegisterInfo(StringRef TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitDigitalMCRegisterInfo(X, Digital::R8);
  return X;
}

static MCInstPrinter *createDigitalMCInstPrinter(const Target &T,
                                                unsigned SyntaxVariant,
                                                const MCAsmInfo &MAI,
                                                const MCInstrInfo &MII,
                                                const MCRegisterInfo &MRI,
                                                const MCSubtargetInfo &STI) {
 /// if (SyntaxVariant == 0)
  //  return new DigitalInstPrinter(MAI, MII, MRI);
  return 0;
}

extern "C" void LLVMInitializeDigitalTargetMC() {

   RegisterMCAsmInfoFn X(getTheDigitalTarget(), createDigitalMCAsmInfo);

	TargetRegistry::RegisterMCInstrInfo(getTheDigitalTarget(), createDigitalMCInstrInfo);
  //    TargetRegistry::RegisterMCRegInfo(TheDigitalTarget, createDigitalMCRegisterInfo);
//    TargetRegistry::RegisterMCSubtargetInfo(TheDigitalTarget, createDigitalMCSubtargetInfo);
    //TargetRegistry::RegisterMCInstrPrinter(TheDigitalTarget, createDigitalMCInstPrinter);
}