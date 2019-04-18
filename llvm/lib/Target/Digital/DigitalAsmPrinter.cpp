//===-- DigitalAsmPrinter.cpp - Digital LLVM assembly writer ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains a printer that converts from our internal representation
// of machine-dependent LLVM code to the Digital assembly language.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "asm-printer"
#include "Digital.h"
#include "DigitalTargetMachine.h"
#include "InstPrinter/DigitalInstPrinter.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
  class DigitalAsmPrinter : public AsmPrinter {
  public:
    explicit DigitalAsmPrinter(TargetMachine &TM,
                               std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}

    StringRef getPassName() const override{ return "Digital Assembly Printer"; }

    void printOperand(const MachineInstr *MI, int OpNum,
                      raw_ostream &O, const char* Modifier = 0);
                      
    void printMemOperand(const MachineInstr *MI, int opNum, raw_ostream &O);
    void printSrcMemOperand(const MachineInstr *MI, int OpNum,
                            raw_ostream &O);
    bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                         unsigned AsmVariant, const char *ExtraCode,
                         raw_ostream &O);
    bool PrintAsmMemoryOperand(const MachineInstr *MI,
                               unsigned OpNo, unsigned AsmVariant,
                               const char *ExtraCode, raw_ostream &O);
    void EmitInstruction(const MachineInstr *MI);
  };
} // end of anonymous namespace


void DigitalAsmPrinter::printOperand(const MachineInstr *MI, int OpNum, raw_ostream &O, const char *Modifier) {

  const MachineOperand &MO = MI->getOperand(OpNum);
  
  if (MO.isReg()) {
	//printRegName(O, Op.getReg());
    O << DigitalInstPrinter::getRegisterName(MO.getReg());
    return;
  }
  
  if (MO.isImm()) {
    O << MO.getImm();
    return;
  }
}

void DigitalAsmPrinter::printMemOperand(const MachineInstr *MI, int opNum, raw_ostream &O) {

  O << "[";
  printOperand(MI, opNum, O);
  O << "]";
}

void DigitalAsmPrinter::printSrcMemOperand(const MachineInstr *MI, int OpNum,
                                          raw_ostream &O) {
  
}

/// PrintAsmOperand - Print out an operand for an inline asm expression.
///
bool DigitalAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                                       unsigned AsmVariant,
                                       const char *ExtraCode, raw_ostream &O) {
    return false;
}

bool DigitalAsmPrinter::PrintAsmMemoryOperand(const MachineInstr *MI,
                                             unsigned OpNo, unsigned AsmVariant,
                                             const char *ExtraCode,
                                             raw_ostream &O) {
  return false;
}

//===----------------------------------------------------------------------===//
void DigitalAsmPrinter::EmitInstruction(const MachineInstr *MI) {

}

// Force static initialization.
extern "C" void LLVMInitializeDigitalAsmPrinter() {
  RegisterAsmPrinter<DigitalAsmPrinter> X(getTheDigitalTarget());
}
