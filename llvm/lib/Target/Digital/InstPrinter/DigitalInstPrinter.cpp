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

void DigitalInstPrinter::printInst(const MCInst *MI, raw_ostream &O, StringRef Annot, const MCSubtargetInfo &STI) {
    
    printInstruction(MI, O);
    printAnnotation(O, Annot);
}

void DigitalInstPrinter::printRegName(raw_ostream &O, unsigned RegNo) const {
  O << getRegisterName(RegNo);
}

void DigitalInstPrinter::printOperand(const MCInst *MI, unsigned OpNo,
                                    raw_ostream &O, const char *Modifier) {
  assert((Modifier == 0 || Modifier[0] == 0) && "No modifiers supported");
  const MCOperand &MO = MI->getOperand(OpNo);

  if (MO.isReg()) {
    printRegName(O, MO.getReg());
    return;
  }

  if (MO.isImm()) {
    O << MO.getImm();
    return;
  }

  assert(MO.isExpr() && "Unknown operand kind in printOperand");
  MO.getExpr()->print(O, &MAI);
}

void DigitalInstPrinter::printMemOperand(const MCInst *MI, int opNum, raw_ostream &O) {

  O << "[";
  printOperand(MI, opNum, O);
  O << "]";
}