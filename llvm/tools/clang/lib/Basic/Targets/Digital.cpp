//===--- Digital.cpp - Implement Digital target feature support ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements Digital TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#include "Digital.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

const char *const DigitalTargetInfo::GCCRegNames[] = {
    "r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6",  "r7",  "r8",  "r9",  "r10",
    "r11", "r12"
};

ArrayRef<const char *> DigitalTargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef(GCCRegNames);
}

const TargetInfo::GCCRegAlias DigitalTargetInfo::GCCRegAliases[] = {
    {{"bp"}, "r10"},   {{"sp"}, "r11"},   {{"ra"}, "r12"},
};

ArrayRef<TargetInfo::GCCRegAlias> DigitalTargetInfo::getGCCRegAliases() const {
  return llvm::makeArrayRef(GCCRegAliases);
}

bool DigitalTargetInfo::isValidCPUName(StringRef Name) const {
  return llvm::StringSwitch<bool>(Name).Case("v11", true).Default(false);
}
void DigitalTargetInfo::fillValidCPUList(
    SmallVectorImpl<StringRef> &Values) const {
  Values.emplace_back("v11");
}

bool DigitalTargetInfo::setCPU(const std::string &Name) {
  CPU = llvm::StringSwitch<CPUKind>(Name).Case("v11", CK_V11).Default(CK_NONE);

  return CPU != CK_NONE;
}

bool DigitalTargetInfo::hasFeature(StringRef Feature) const {
  return llvm::StringSwitch<bool>(Feature).Case("digital", true).Default(false);
}

void DigitalTargetInfo::getTargetDefines(const LangOptions &Opts,
                                       MacroBuilder &Builder) const {
  Builder.defineMacro("__digital__");

  switch (CPU) {
  case CK_V11:
    Builder.defineMacro("__DIGITAL_V11__");
    break;
  case CK_NONE:
    llvm_unreachable("Unhandled target CPU");
  }
}
