//===--- Digital.cpp - Digital Helpers for Tools --------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Digital.h"
#include "clang/Driver/Driver.h"
#include "clang/Driver/DriverDiagnostic.h"
#include "clang/Driver/Options.h"
#include "llvm/Option/ArgList.h"
#include "llvm/Support/TargetParser.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang::driver;
using namespace clang::driver::tools;
using namespace clang;
using namespace llvm::opt;

void digital::getDigitalTargetFeatures(const Driver &D, const ArgList &Args, std::vector<StringRef> &Features) {

}

StringRef digital::getDigitalABI(const ArgList &Args, const llvm::Triple &Triple) {
  return "digital";
}