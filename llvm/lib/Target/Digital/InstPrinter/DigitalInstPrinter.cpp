//===-- DigitalInstPrinter.cpp - Convert Digital MCInst to asm syntax ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This class prints an Digital MCInst to a .s file.
//
//===----------------------------------------------------------------------===//

#include "DigitalInstPrinter.h"
#include "Digital.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

// Include the auto-generated portion of the assembly writer.
#define PRINT_ALIAS_INSTR
#include "DigitalGenAsmWriter.inc"

void DigitalInstPrinter::printRegName(raw_ostream &OS, unsigned RegNo) const {
  OS << StringRef(getRegisterName(RegNo));
}

bool DigitalInstPrinter::printInst(const MCInst *MI, raw_ostream &OS,
                                 StringRef Alias, unsigned OpNo0,
                                 unsigned OpNo1) {
  OS << "\t" << Alias << " ";
  printOperand(MI, OpNo0, OS);
  OS << ", ";
  printOperand(MI, OpNo1, OS);
  return true;
}

bool DigitalInstPrinter::printAlias(const MCInst *MI, raw_ostream &OS) {
  switch (MI->getOpcode()) {
  default:
    return false;
  }
}

void DigitalInstPrinter::printInst(const MCInst *MI, raw_ostream &OS,
                                 StringRef Annotation,
                                 const MCSubtargetInfo & /*STI*/) {
  if (!printAlias(MI, OS) && !printAliasInstr(MI, OS))
    printInstruction(MI, OS);
  printAnnotation(OS, Annotation);
}

void DigitalInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                    raw_ostream &OS, const char *Modifier) {
  assert((Modifier == 0 || Modifier[0] == 0) && "No modifiers supported");
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isReg())
    OS << getRegisterName(Op.getReg());
  else if (Op.isImm())
    OS << formatHex(Op.getImm());
  else {
    assert(Op.isExpr() && "Expected an expression");
    Op.getExpr()->print(OS, &MAI);
  }
}

void DigitalInstPrinter::printMemImmOperand(const MCInst *MI, unsigned OpNo,
                                          raw_ostream &OS) {
  const MCOperand &Op = MI->getOperand(OpNo);
  if (Op.isImm()) {
    OS << '[' << formatHex(Op.getImm()) << ']';
  } else {
    // Symbolic operand will be lowered to immediate value by linker
    assert(Op.isExpr() && "Expected an expression");
    OS << '[';
    Op.getExpr()->print(OS, &MAI);
    OS << ']';
  }
}

void DigitalInstPrinter::printMemOperand(const MCInst *MI, int opNum, raw_ostream &O) {

  O << "[";
  printOperand(MI, opNum, O);
  O << "]";
}