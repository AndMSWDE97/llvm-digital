//===---- DigitalABIInfo.h - Information about Digital ABI's --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_DIGITAL_MCTARGETDESC_DIGITALABIINFO_H
#define LLVM_LIB_TARGET_DIGITAL_MCTARGETDESC_DIGITALABIINFO_H

#include "llvm/ADT/Triple.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/MC/MCRegisterInfo.h"

namespace llvm {

class MCTargetOptions;
class StringRef;
class TargetRegisterClass;

class DigitalABIInfo {
public:
  enum class ABI { Unknown, O16, S16 };

protected:
  ABI ThisABI;

public:
  DigitalABIInfo(ABI ThisABI) : ThisABI(ThisABI) {}

  static DigitalABIInfo Unknown() { return DigitalABIInfo(ABI::Unknown); }
  static DigitalABIInfo O16() { return DigitalABIInfo(ABI::O16); }
  static DigitalABIInfo S16() { return DigitalABIInfo(ABI::S16); }
  static DigitalABIInfo computeTargetABI();

  bool IsKnown() const { return ThisABI != ABI::Unknown; }
  bool IsO16() const { return ThisABI == ABI::O16; }
  bool IsS16() const { return ThisABI == ABI::S16; }
  ABI GetEnumValue() const { return ThisABI; }

  /// The registers to use for byval arguments.
  const ArrayRef<MCPhysReg> GetByValArgRegs() const;

  /// The registers to use for the variable argument list.
  const ArrayRef<MCPhysReg> GetVarArgRegs() const;

  /// Obtain the size of the area allocated by the callee for arguments.
  /// CallingConv::FastCall affects the value for O32.
  unsigned GetCalleeAllocdArgSizeInBytes(CallingConv::ID CC) const;

  /// Ordering of ABI's
  /// DigitalGenSubtargetInfo.inc will use this to resolve conflicts when given
  /// multiple ABI options.
  bool operator<(const DigitalABIInfo Other) const {
    return ThisABI < Other.GetEnumValue();
  }

  unsigned GetStackPtr() const;
  unsigned GetFramePtr() const;

  unsigned GetEhDataReg(unsigned I) const;
  int EhDataRegSize() const;
};
}

#endif
