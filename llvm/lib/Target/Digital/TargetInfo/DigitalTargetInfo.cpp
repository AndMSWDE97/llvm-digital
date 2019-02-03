#include "Digital.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

namespace llvm {
Target &getTheDigitalTarget() {
  static Target TheDigitalTarget;
  return TheDigitalTarget;
}
} // namespace llvm

extern "C" void LLVMInitializeDigitalTargetInfo() {
RegisterTarget<Triple::digital> X(getTheDigitalTarget(), "digital", "digital", "Digital");
}