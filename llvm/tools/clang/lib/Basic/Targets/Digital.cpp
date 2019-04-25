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
#include "Targets.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/MacroBuilder.h"
#include "clang/Basic/TargetBuiltins.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

ArrayRef<const char *> DigitalTargetInfo::getGCCRegNames() const {
  return llvm::makeArrayRef({"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7",
                             "R8", "R9", "R10", "R11", "R12"});
}

ArrayRef<TargetInfo::GCCRegAlias> DigitalTargetInfo::getGCCRegAliases() const {

	const TargetInfo::GCCRegAlias GCCRegAliases[] = {
      {{"BP"}, "R10"},
      {{"SP"}, "R11"},
      {{"RA"}, "R12"},
  };

  return llvm::makeArrayRef(GCCRegAliases);
}

void DigitalTargetInfo::getTargetDefines(const LangOptions &Opts, MacroBuilder &Builder) const {
  Builder.defineMacro("__digital__");
}