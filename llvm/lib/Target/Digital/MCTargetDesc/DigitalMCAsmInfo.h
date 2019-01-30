//===-- DigitalMCAsmInfo.h - Digital asm properties --------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source 
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the DigitalMCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef DIGITALTARGETASMINFO_H
#define DIGITALTARGETASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
  class StringRef;

  class DigitalMCAsmInfo : public MCAsmInfo {
    virtual void anchor();
  public:
    explicit DigitalMCAsmInfo(StringRef TT);
  };

} // namespace llvm

#endif
