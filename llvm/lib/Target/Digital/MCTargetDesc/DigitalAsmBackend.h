//===-- DigitalAsmBackend.h - Digital Asm Backend  ------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the DigitalAsmBackend class.
//
//===----------------------------------------------------------------------===//
//

#ifndef LLVM_LIB_TARGET_DIGITAL_ASMBACKEND_H
#define LLVM_LIB_TARGET_DIGITAL_ASMBACKEND_H

#include "DigitalFixupKinds.h"
#include "DigitalMCTargetDesc.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

namespace llvm {

class MCAssembler;
struct MCFixupKindInfo;
class Target;
class MCObjectWriter;

class DigitalAsmBackend : public MCAsmBackend {
  Triple TheTriple;
  Triple::OSType OSType;
  bool IsLittle;

public:
  DigitalAsmBackend(const Target &T, const Triple &TT, bool _isLittle)
    :MCAsmBackend(support::big), TheTriple(TT), IsLittle(_isLittle) {}

  std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const override;

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup, const MCValue &Target, MutableArrayRef<char> Data, uint64_t Value, bool IsResolved, const MCSubtargetInfo *STI) const override;

  unsigned getNumFixupKinds() const override;

  bool writeNopData(raw_ostream &OS, uint64_t Count) const override;

  bool mayNeedRelaxation(const MCInst &Inst,
                         const MCSubtargetInfo &STI) const override {
    return false;
  }

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value,
                            const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override {
    return false;
  }

  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI,
                        MCInst &Res) const override {
    llvm_unreachable("CJGAsmBackend::relaxInstruction() unimplemented");
  }
};

} // namespace llvm

#endif
