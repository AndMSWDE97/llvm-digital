//===-- DigitalMCTargetDesc.h - Digital Target Descriptions -------*- C++
//-*-===//
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

#ifndef LLVM_LIB_TARGET_DIGITAL_MCTARGETDESC_DIGITALMCTARGETDESC_H
#define LLVM_LIB_TARGET_DIGITAL_MCTARGETDESC_DIGITALMCTARGETDESC_H

#include "llvm/Config/config.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/MC/MCContext.h"
#include "llvm/Support/DataTypes.h"
#include <memory>

namespace llvm {

class MCAsmBackend;
class MCCodeEmitter;
class MCContext;
class MCInstrInfo;
class MCObjectTargetWriter;
class MCRegisterInfo;
class MCSubtargetInfo;
class MCTargetOptions;
class StringRef;
class Target;
class Triple;
class raw_ostream;
class raw_pwrite_stream;

Target &getTheDigitalTarget();

MCCodeEmitter *createDigitalMCCodeEmitter(const MCInstrInfo &MCII, const MCRegisterInfo &MRI, MCContext &Ctx);

MCAsmBackend *createDigitalAsmBackend(const Target &T, const MCSubtargetInfo &STI, const MCRegisterInfo &MRI, const MCTargetOptions &Options);

std::unique_ptr<MCObjectTargetWriter> createDigitalELFObjectWriter(uint8_t OSABI);

} // namespace llvm

// Defines symbolic names for Digital registers.  This defines a mapping from
// register name to register number.
#define GET_REGINFO_ENUM
#include "DigitalGenRegisterInfo.inc"

// Defines symbolic names for the Digital instructions.
#define GET_INSTRINFO_ENUM
#include "DigitalGenInstrInfo.inc"

#endif