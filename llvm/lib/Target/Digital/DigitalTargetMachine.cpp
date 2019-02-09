//===-- DigitalTargetMachine.cpp - Define TargetMachine for Digital -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the GNU General Public License Version 3.
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "DigitalTargetMachine.h"
#include "Digital.h"
#include "DigitalTargetObjectFile.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

#define DEBUG_TYPE "digital"

extern "C" void LLVMInitializeDigitalTarget() {
  // Register the target.
  RegisterTargetMachine<DigitalTargetMachine> X(getTheDigitalTarget());
}

static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::PIC_;
  return *RM;
}

static StringRef computeDataLayout(const Triple &T) {
  std::string Ret = "";

// "E-m:m-p:16:16-i16:16-n16-S16"
/*
  Ret += "E";
  Ret += "-m:m"; 
  Ret += "-p:16:16"; 
  Ret += "-i16:16";
  Ret += "-n16";   
  Ret += "-S16"; 
*/
    Ret += "E"; // Big endian

  Ret += "-m:e"; // ELF name mangling
  // first value is pointer size, and the second value is both ABI 
  //   and preferred alignment.
  Ret += "-p:16:16"; // 16-bit pointers, 16 bit aligned
  // Alignments for 16 bit integers.
  Ret += "-i16:16"; // 16 bit integers, 16 bit aligned
  Ret += "-a:0:16";  // 16 bit alignment of objects of aggregate type
  Ret += "-n16"; // 16 bit native integer width
  Ret += "-S16"; // 16 bit natural stack alignment
  return Ret;
}

// DataLayout --> Big-endian, 32-bit pointer/ABI/alignment
// The stack is always 8 byte aligned
// On function prologue, the stack is created by decrementing
// its pointer. Once decremented, all references are done with positive
// offset from the stack/frame pointer, using StackGrowsUp enables
// an easier handling.
// Using CodeModel::Large enables different CALL behavior.
DigitalTargetMachine::DigitalTargetMachine( const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FeatureString,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       Optional<CodeModel::Model> CodeModel,
                                       CodeGenOpt::Level OptLevel, bool JIT)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FeatureString,
                        Options, getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CodeModel, CodeModel::Small), OptLevel),
      TLOF(make_unique<DigitalTargetObjectFile>()) {
  initAsmInfo();
}

DigitalTargetMachine::~DigitalTargetMachine() {}

namespace {
//@DigitalPassConfig {
/// Digital Code Generator Pass Configuration Options.
class DigitalPassConfig : public TargetPassConfig {
public:
  DigitalPassConfig(DigitalTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(*TM, PM) {}

  DigitalTargetMachine &getDigitalTargetMachine() const {
    return getTM<DigitalTargetMachine>();
  }
};
} // namespace

TargetPassConfig *DigitalTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new DigitalPassConfig(this, PM);
}
