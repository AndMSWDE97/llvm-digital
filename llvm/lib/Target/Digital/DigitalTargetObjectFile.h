#ifndef LLVM_LIB_TARGET_DIGITAL_DIGITALTARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_DIGITAL_DIGITALTARGETOBJECTFILE_H

#include "DigitalTargetMachine.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"

namespace llvm {
class DigitalTargetMachine;
  class DigitalTargetObjectFile : public TargetLoweringObjectFileELF {
    MCSection *SmallDataSection;
    MCSection *SmallBSSSection;
    const DigitalTargetMachine *TM;
  public:

    void Initialize(MCContext &Ctx, const TargetMachine &TM) override;

  };
} // end namespace llvm