//===---- DigitalABIInfo.cpp - Information about Digital ABI's ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
#include "DigitalABIInfo.h"
#include "DigitalRegisterInfo.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/ADT/StringSwitch.h"
#include "llvm/MC/MCTargetOptions.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

namespace {
//static const MCPhysReg O16IntRegs[2] = {Digital::R3, Digital::R4};
static const MCPhysReg O16IntRegs[2] = {3, 4};
static const MCPhysReg S16IntRegs = {};
}

const ArrayRef<MCPhysReg> DigitalABIInfo::GetByValArgRegs() const {
  if (IsO16())
    return makeArrayRef(O16IntRegs);
  if (IsS16())
    return makeArrayRef(S16IntRegs);
  llvm_unreachable("Unhandled ABI");
}

const ArrayRef<MCPhysReg> DigitalABIInfo::GetVarArgRegs() const {
  if (IsO16())
    return makeArrayRef(O16IntRegs);
  if (IsS16())
    return makeArrayRef(S16IntRegs);
  llvm_unreachable("Unhandled ABI");
}

unsigned DigitalABIInfo::GetCalleeAllocdArgSizeInBytes(CallingConv::ID CC) const {
  if (IsO16())
    return CC != 0;
  if (IsS16())
    return 0;
  llvm_unreachable("Unhandled ABI");
}

DigitalABIInfo DigitalABIInfo::computeTargetABI() {
  DigitalABIInfo abi(ABI::Unknown);

  abi = ABI::S16;

  assert(abi.ThisABI != ABI::Unknown);

  return abi;
}

unsigned DigitalABIInfo::GetStackPtr() const {
  //return Digital::SP;
  return 14;
}

unsigned DigitalABIInfo::GetFramePtr() const {
 // return Digital::BP;
  return 13;
}

unsigned DigitalABIInfo::GetEhDataReg(unsigned I) const {
  /*static const unsigned EhDataReg[] = {
    Digital::R3, Digital::R4
  };*/
  static const unsigned EhDataReg[] = {3, 4};

  return EhDataReg[I];
}

int DigitalABIInfo::EhDataRegSize() const {
  if (ThisABI == ABI::S16)
    return 0;
  else
    return 2;
}
