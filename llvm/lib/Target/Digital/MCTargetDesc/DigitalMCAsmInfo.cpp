//===-- DigitalMCAsmInfo.cpp - Digital asm properties -----------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declarations of the DigitalMCAsmInfo properties.
//
//===----------------------------------------------------------------------===//

#include "DigitalMCAsmInfo.h"
#include "llvm/ADT/Triple.h"
using namespace llvm;

void DigitalMCAsmInfo::anchor() { }

DigitalMCAsmInfo::DigitalMCAsmInfo(const Triple &TheTriple) {
  IsLittleEndian = false;
  CommentString = ";";
  SupportsDebugInformation = true;
}
