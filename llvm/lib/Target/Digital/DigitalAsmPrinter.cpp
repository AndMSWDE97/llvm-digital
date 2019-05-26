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

#include "Digital.h"
#include "DigitalTargetMachine.h"
#include "InstPrinter/DigitalInstPrinter.h"
#include "DigitalInstrInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Mangler.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstBuilder.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"

#define DEBUG_TYPE "asm-printer"
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
    bool PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                         unsigned AsmVariant, const char *ExtraCode,
                         raw_ostream &O);
    void EmitInstruction(const MachineInstr *MI);
  private:
    void customEmitInstruction(const MachineInstr *MI);
    void emitCallInstruction(const MachineInstr *MI);
  };
} // end of anonymous namespace


void DigitalAsmPrinter::printOperand(const MachineInstr *MI, int OpNum, raw_ostream &O, const char *Modifier) {

  const MachineOperand &MO = MI->getOperand(OpNum);

  switch (MO.getType()) {
  case MachineOperand::MO_Register:
    O << DigitalInstPrinter::getRegisterName(MO.getReg());
    break;

  case MachineOperand::MO_Immediate:
    O << MO.getImm();
    break;

  case MachineOperand::MO_MachineBasicBlock:
    O << *MO.getMBB()->getSymbol();
    break;

  case MachineOperand::MO_GlobalAddress:
    O << *getSymbol(MO.getGlobal());
    break;

  case MachineOperand::MO_BlockAddress: {
    MCSymbol *BA = GetBlockAddressSymbol(MO.getBlockAddress());
    O << BA->getName();
    break;
  }

  case MachineOperand::MO_ExternalSymbol:
    O << *GetExternalSymbolSymbol(MO.getSymbolName());
    break;

  default:
    llvm_unreachable("<unknown operand type>");
  }
}

void DigitalAsmPrinter::printMemOperand(const MachineInstr *MI, int opNum, raw_ostream &O) {

  O << "[";
  printOperand(MI, opNum, O);
  O << "]";
}

bool DigitalAsmPrinter::PrintAsmOperand(const MachineInstr *MI, unsigned OpNo,
                                       unsigned AsmVariant,
                                       const char *ExtraCode, raw_ostream &O) {
  if (ExtraCode && ExtraCode[0]) {
    if (ExtraCode[1])
      return true; // Unknown modifier.

    switch (ExtraCode[0]) {
    // The highest-numbered register of a pair.
    case 'H': {
      if (OpNo == 0)
        return true;
      const MachineOperand &FlagsOP = MI->getOperand(OpNo - 1);
      if (!FlagsOP.isImm())
        return true;
      unsigned Flags = FlagsOP.getImm();
      unsigned NumVals = InlineAsm::getNumOperandRegisters(Flags);
      if (NumVals != 2)
        return true;
      unsigned RegOp = OpNo + 1;
      if (RegOp >= MI->getNumOperands())
        return true;
      const MachineOperand &MO = MI->getOperand(RegOp);
      if (!MO.isReg())
        return true;
      unsigned Reg = MO.getReg();
      O << DigitalInstPrinter::getRegisterName(Reg);
      return false;
    }
    default:
      return true; // Unknown modifier.
    }
  }
  printOperand(MI, OpNo, O);
  return false;
}

void DigitalAsmPrinter::customEmitInstruction(const MachineInstr *MI) {
  MCSubtargetInfo STI = getSubtargetInfo();
  MCInst TmpInst;
  OutStreamer->EmitInstruction(TmpInst, STI);
}

void DigitalAsmPrinter::emitCallInstruction(const MachineInstr *MI) {

}

void DigitalAsmPrinter::EmitInstruction(const MachineInstr *MI) {
  MachineBasicBlock::const_instr_iterator I = MI->getIterator();
  MachineBasicBlock::const_instr_iterator E = MI->getParent()->instr_end();

  do {
    if (I->isCall()) {
      emitCallInstruction(&*I);
      continue;
    }

    customEmitInstruction(&*I);
  } while ((++I != E) && I->isInsideBundle());
}
// Force static initialization.
extern "C" void LLVMInitializeDigitalAsmPrinter() {
  RegisterAsmPrinter<DigitalAsmPrinter> X(getTheDigitalTarget());
}
