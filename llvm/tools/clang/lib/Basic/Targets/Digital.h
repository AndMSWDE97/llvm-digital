//===--- Digital.h - Declare Digital target feature support ---------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file declares Digital TargetInfo objects.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_DIGITAL_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_DIGITAL_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/Compiler.h"

namespace clang {
namespace targets {

class LLVM_LIBRARY_VISIBILITY DigitalTargetInfo : public TargetInfo {

  enum CPUKind {
    CK_NONE,
    CK_V11,
  } CPU;

  static const TargetInfo::GCCRegAlias GCCRegAliases[];
  static const char *const GCCRegNames[];

public:
  DigitalTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
      : TargetInfo(Triple) {
    // Description string has to be kept in sync with backend.
    resetDataLayout("E" 
                    "-m:e" 
                    "-p:16:16" 
                    "-i16:16"
                    "-a:0:16" 
                    "-n16" 
                    "-S16"
    );

    // Setting RegParmMax equal to what mregparm was set to in the old
    // toolchain
    RegParmMax = 4;

    // Set the default CPU to V11
    CPU = CK_V11;

    // Temporary approach to make everything at least word-aligned and allow for
    // safely casting between pointers with different alignment requirements.
    // TODO: Remove this when there are no more cast align warnings on the
    // firmware.
    MinGlobalAlign = 32;
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  bool isValidCPUName(StringRef Name) const override;

  void fillValidCPUList(SmallVectorImpl<StringRef> &Values) const override;

  bool setCPU(const std::string &Name) override;

  bool hasFeature(StringRef Feature) const override;

  ArrayRef<const char *> getGCCRegNames() const override;

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override;

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  ArrayRef<Builtin::Info> getTargetBuiltins() const override { return None; }

  bool validateAsmConstraint(const char *&Name,
                             TargetInfo::ConstraintInfo &info) const override {
    return false;
  }

  const char *getClobbers() const override { return ""; }
};
} // namespace targets
} // namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_DIGITAL_H
