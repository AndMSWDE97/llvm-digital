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

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
  class Triple;

  class DigitalMCAsmInfo : public MCAsmInfoELF {
    void anchor() override;
  public:
    explicit DigitalMCAsmInfo(const Triple &TheTriple);
  };

} // namespace llvm

#endif
