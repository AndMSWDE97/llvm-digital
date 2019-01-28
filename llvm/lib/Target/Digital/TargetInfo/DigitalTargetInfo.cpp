#include "Digital.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;
Target llvm::TheDigitalTarget;
extern "C" void LLVMInitializeDigitalTargetInfo() {
RegisterTarget<Triple::digital> X(TheDigialTarget, "digital",
"digital");
}