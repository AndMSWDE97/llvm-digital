//===-- DigitalELFObjectWriter.cpp - Digital ELF Writer -------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "DigitalMCTargetDesc.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCValue.h"
#include "llvm/Support/ErrorHandling.h"
#include <list>
#include <memory>

using namespace llvm;

namespace {

  class DigitalELFObjectWriter : public MCELFObjectTargetWriter {
  public:
    DigitalELFObjectWriter(uint8_t OSABI);

    virtual ~DigitalELFObjectWriter();

    unsigned getRelocType(MCContext &Ctx, const MCValue &Target, const MCFixup &Fixup, bool IsPCRel) const override;
  };
}

DigitalELFObjectWriter::DigitalELFObjectWriter(uint8_t OSABI)
  : MCELFObjectTargetWriter(/*_is64Bit=false*/ false, OSABI, ELF::EM_DIGITAL,
                            /*HasRelocationAddend*/ false) {}

DigitalELFObjectWriter::~DigitalELFObjectWriter() {}

unsigned DigitalELFObjectWriter::getRelocType(MCContext &Ctx,
                                           const MCValue &Target,
                                           const MCFixup &Fixup,
                                           bool IsPCRel) const {
  report_fatal_error("invalid fixup kind!");
}

std::unique_ptr<MCObjectTargetWriter> llvm::createDigitalELFObjectWriter(uint8_t OSABI) {
  return llvm::make_unique<DigitalELFObjectWriter>(OSABI);
}
