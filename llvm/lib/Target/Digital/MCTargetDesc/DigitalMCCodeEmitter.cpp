//===-- DigitalMCCodeEmitter.cpp - Convert Digital Code to Machine Code ---------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements the DigitalMCCodeEmitter class.
//
//===----------------------------------------------------------------------===//

#include "DigitalMCCodeEmitter.h"
#include "DigitalFixupKinds.h"
#include "DigitalMCTargetDesc.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APInt.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrDesc.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
#include <cassert>
#include <cstdint>

using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

#define GET_INSTRMAP_INFO
#include "DigitalGenInstrInfo.inc"
#undef GET_INSTRMAP_INFO

STATISTIC(MCNumEmitted, "Number of MC instructions emitted");

namespace llvm {

MCCodeEmitter *createDigitalMCCodeEmitter(const MCInstrInfo &MCII, const MCRegisterInfo &MRI, MCContext &Ctx) {
  return new DigitalMCCodeEmitter(MCII, Ctx, true);
}

void DigitalMCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo &STI) const {

	uint16_t Binary = getBinaryCodeForInstr(MI, Fixups, STI);
  
	int Size = 4;

	EmitInstruction(Binary, Size, STI, OS);
}

void DigitalMCCodeEmitter::EmitInstruction(uint64_t Val, unsigned Size,
                                        const MCSubtargetInfo &STI,
                                        raw_ostream &OS) const {
	
	return;
}

unsigned DigitalMCCodeEmitter::getMachineOpValue(const MCInst &MI, const MCOperand &MO, SmallVectorImpl<MCFixup> &Fixups, const MCSubtargetInfo &STI) const {

  if (MO.isReg())
    return Ctx.getRegisterInfo()->getEncodingValue(MO.getReg());

  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());

  llvm_unreachable("Unhandled expression!");
  return 0;
}

unsigned DigitalMCCodeEmitter::getMemEncoding(const MCInst &MI, unsigned OpNo,
                                  SmallVectorImpl<MCFixup> &Fixups,
                                  const MCSubtargetInfo &STI) const {
  // Base register is encoded in bits 20-16, offset is encoded in bits 15-0.
  assert(MI.getOperand(OpNo).isReg());
  unsigned RegBits = getMachineOpValue(MI, MI.getOperand(OpNo), Fixups, STI) << 16;
  unsigned OffBits = getMachineOpValue(MI, MI.getOperand(OpNo+1), Fixups, STI);

  return (OffBits & 0xFFFF) | RegBits;
}

} // end namespace llvm

#include "DigitalGenMCCodeEmitter.inc"