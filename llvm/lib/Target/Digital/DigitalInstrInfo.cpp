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

#include "Digital.h"
#include "DigitalInstrInfo.h"
#include "DigitalMachineFunction.h"
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

DigitalInstrInfo::DigitalInstrInfo()
    : DigitalGenInstrInfo(Digital::ADJCALLSTACKDOWN, Digital::ADJCALLSTACKUP),
      RegisterInfo() {}

void DigitalInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator Position,
                                 const DebugLoc &DL,
                                 unsigned DestinationRegister,
                                 unsigned SourceRegister,
                                 bool KillSource) const {
  if (!Digital::GPRRegClass.contains(DestinationRegister, SourceRegister)) {
    llvm_unreachable("Impossible reg-to-reg copy");
  }

  BuildMI(MBB, Position, DL, get(Digital::MOV), DestinationRegister)
    .addReg(SourceRegister, getKillRegState(KillSource));
}

void DigitalInstrInfo::storeRegToStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator Position,
    unsigned SourceRegister, bool IsKill, int FrameIndex,
    const TargetRegisterClass *RegisterClass,
    const TargetRegisterInfo * /*RegisterInfo*/) const {
  DebugLoc DL;
  if (Position != MBB.end()) {
    DL = Position->getDebugLoc();
  }

  if (!Digital::GPRRegClass.hasSubClassEq(RegisterClass)) {
    llvm_unreachable("Can't store this register to stack slot");
  }
  BuildMI(MBB, Position, DL, get(Digital::ST))
      .addReg(SourceRegister, getKillRegState(IsKill))
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

void DigitalInstrInfo::loadRegFromStackSlot(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator Position,
    unsigned DestinationRegister, int FrameIndex,
    const TargetRegisterClass *RegisterClass,
    const TargetRegisterInfo * /*RegisterInfo*/) const {
  DebugLoc DL;
  if (Position != MBB.end()) {
    DL = Position->getDebugLoc();
  }

  if (!Digital::GPRRegClass.hasSubClassEq(RegisterClass)) {
    llvm_unreachable("Can't load this register from stack slot");
  }
  BuildMI(MBB, Position, DL, get(Digital::MOV), DestinationRegister)
      .addFrameIndex(FrameIndex)
      .addImm(0);
}

bool DigitalInstrInfo::areMemAccessesTriviallyDisjoint(
    MachineInstr &MIa, MachineInstr &MIb, AliasAnalysis * /*AA*/) const {
  assert(MIa.mayLoadOrStore() && "MIa must be a load or store.");
  assert(MIb.mayLoadOrStore() && "MIb must be a load or store.");

  if (MIa.hasUnmodeledSideEffects() || MIb.hasUnmodeledSideEffects() ||
      MIa.hasOrderedMemoryRef() || MIb.hasOrderedMemoryRef())
    return false;

  // Retrieve the base register, offset from the base register and width. Width
  // is the size of memory that is being loaded/stored (e.g. 1, 2, 4).  If
  // base registers are identical, and the offset of a lower memory access +
  // the width doesn't overlap the offset of a higher memory access,
  // then the memory accesses are different.
  const TargetRegisterInfo *TRI = &getRegisterInfo();
  MachineOperand *BaseOpA = nullptr, *BaseOpB = nullptr;
  int64_t OffsetA = 0, OffsetB = 0;
  unsigned int WidthA = 0, WidthB = 0;
  /*if (getMemOperandWithOffsetWidth(MIa, BaseOpA, OffsetA, WidthA, TRI) &&
      getMemOperandWithOffsetWidth(MIb, BaseOpB, OffsetB, WidthB, TRI)) {
    if (BaseOpA->isIdenticalTo(*BaseOpB)) {
      int LowOffset = std::min(OffsetA, OffsetB);
      int HighOffset = std::max(OffsetA, OffsetB);
      int LowWidth = (LowOffset == OffsetA) ? WidthA : WidthB;
      if (LowOffset + LowWidth <= HighOffset)
        return true;
    }
  }*/
  return false;
}

bool DigitalInstrInfo::expandPostRAPseudo(MachineInstr &MI) const {
  MachineBasicBlock *MBB = MI.getParent();

  switch(MI.getOpcode()) {
  default:
    return false;
  case Digital::RET:
    expandRet(MBB, MI);
    break;
  }

  MBB->erase(MI);
  return false;
}

void DigitalInstrInfo::expandRet(MachineBasicBlock *MBB,
				 MachineInstr &MI) const {
  
  BuildMI(*MBB, MI, MI.getDebugLoc(), get(Digital::RET)).addReg(Digital::SP);
}

std::pair<unsigned, unsigned>
DigitalInstrInfo::decomposeMachineOperandsTargetFlags(unsigned TF) const {
  return std::make_pair(TF, 0u);
}

bool DigitalInstrInfo::analyzeSelect(const MachineInstr &MI,
                                   SmallVectorImpl<MachineOperand> &Cond,
                                   unsigned &TrueOp, unsigned &FalseOp,
                                   bool &Optimizable) const {
  // Select operands:
  // 0: Def.
  // 1: True use.
  // 2: False use.
  // 3: Condition code.
  TrueOp = 1;
  FalseOp = 2;
  Cond.push_back(MI.getOperand(3));
  Optimizable = true;
  return false;
}
