//==- DigitalCallingConv.td - Calling Conventions for Digital -*- tablegen -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for Digital architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Digital Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_Digital : CallingConv<[
  // Promote i8 return values to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,

  // i16 are returned in registers A, B, C
  CCIfType<[i16], CCAssignToReg<[R10, R11, R12]>>
]>;

//===----------------------------------------------------------------------===//
// Digital Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_Digital : CallingConv<[
  // Promote i8 arguments to i16.
  CCIfType<[i8], CCPromoteToType<i16>>,

  // The first 3 integer arguments of non-varargs functions are passed in
  // integer registers.
  CCIfNotVarArg<CCIfType<[i16], CCAssignToReg<[R10, R11, R12]>>>,

  // Integer values get stored in stack slots that are 1 (16 bit) byte in
  // size and 1-byte aligned.
  CCIfType<[i16], CCAssignToStack<1, 1>>
]>;

def CSR_Digital : CalleeSavedRegs<(add R5, R6, R7, R8, R9)>;
