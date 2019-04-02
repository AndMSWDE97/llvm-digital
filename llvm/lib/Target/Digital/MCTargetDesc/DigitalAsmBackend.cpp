#include "DigitalAsmBackend.h"
//===-- DigitalASMBackend.cpp - Digital Asm Backend
//----------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the DigitalAsmBackend and DigitalELFObjectWriter classes.
//
//===----------------------------------------------------------------------===//
//

#include "DigitalFixupKinds.h"
#include "DigitalMCTargetDesc.h"
#include "DigitalAsmBackend.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

// Prepare value for the target space for it
static unsigned adjustFixupValue(unsigned Kind, uint64_t Value) {

  switch (Kind) {
  default:
    return 0;
  case Digital::fixup_Digital_16:
    break;
  }  
  return Value;
}

void DigitalAsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup, const MCValue &Target, MutableArrayRef<char> Data, uint64_t Value, bool IsResolved, const MCSubtargetInfo *STI) const { 
	return; 
}

unsigned DigitalAsmBackend::getNumFixupKinds() const{ 
  return Digital::NumTargetFixupKinds; 
}

bool DigitalAsmBackend::writeNopData(raw_ostream &OS, uint64_t Count) const {
  OS.write_zeros(Count);
  return true;
}

std::unique_ptr<MCObjectTargetWriter> DigitalAsmBackend::createObjectTargetWriter() const {
  return createDigitalELFObjectWriter(MCELFObjectTargetWriter::getOSABI(OSType));
}

MCAsmBackend *llvm::createDigitalAsmBackend(const Target &T, const MCSubtargetInfo &STI, const MCRegisterInfo &MRI, const MCTargetOptions &Options) {
  return new DigitalAsmBackend(T,STI.getTargetTriple(),/*IsLittle*/true);
}