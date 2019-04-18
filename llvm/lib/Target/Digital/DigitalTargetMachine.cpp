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

DigitalTargetMachine::DigitalTargetMachine( const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FeatureString,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       Optional<CodeModel::Model> CodeModel,
                                       CodeGenOpt::Level OptLevel, bool JIT)
    : LLVMTargetMachine(T, "E-m:e-p:16:16-i16:16-n16-S16", TT, CPU, FeatureString,
                        Options, getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CodeModel, CodeModel::Small), OptLevel),
      TLOF(make_unique<DigitalTargetObjectFile>()),
      Subtarget(TT, CPU, FeatureString) {
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

  virtual bool addInstSelector();
};
} // namespace

TargetPassConfig *DigitalTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new DigitalPassConfig(this, PM);
}

bool DigitalPassConfig::addInstSelector() {
  addPass(createDigitalISelDag(getDigitalTargetMachine()));
  return false;
}