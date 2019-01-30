//===-- DigitalFixupKinds.h - Digital Specific Fixup Entries ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_DIGITAL_MCTARGETDESC_DIGITALFIXUPKINDS_H
#define LLVM_LIB_TARGET_DIGITAL_MCTARGETDESC_DIGITALFIXUPKINDS_H

#include "llvm/MC/MCFixup.h"

namespace llvm {
namespace Digital {

  enum Fixups {
    fixup_Digital_NONE = FirstTargetFixupKind,
    fixup_Digital_16,

    // Marker
    LastTargetFixupKind,
    NumTargetFixupKinds = LastTargetFixupKind - FirstTargetFixupKind
  };
} // namespace Digital
} // namespace llvm


#endif
