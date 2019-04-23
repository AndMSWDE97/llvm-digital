//===-- DigitalInstrInfo.cpp - Digital Instruction Information ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Digital implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#include "DigitalInstrInfo.h"
#include "Digital.h"
#include "DigitalSubtarget.h"
#include "DigitalTargetMachine.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "DigitalGenInstrInfo.inc"

// Pin the vtable to this file.
void DigitalInstrInfo::anchor() {}

DigitalInstrInfo::DigitalInstrInfo(const DigitalSubtarget &STI) : Subtarget(STI){}