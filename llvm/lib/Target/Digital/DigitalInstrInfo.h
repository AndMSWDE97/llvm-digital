//===-- DigitalInstrInfo.h - Digital Instruction Information --------*- C++
//-*-===//
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

#ifndef LLVM_LIB_TARGET_DIGITAL_DIGITALINSTRINFO_H
#define LLVM_LIB_TARGET_DIGITAL_DIGITALINSTRINFO_H

#include "DigitalRegisterInfo.h"
#include "MCTargetDesc/DigitalMCTargetDesc.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "DigitalGenInstrInfo.inc"

namespace llvm {

class DigitalInstrInfo : public DigitalGenInstrInfo {
  const DigitalRegisterInfo RegisterInfo;

public:
  DigitalInstrInfo();

  // getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  // such, whenever a client has an instance of instruction info, it should
  // always be able to get register info as well (through this method).
  virtual const DigitalRegisterInfo &getRegisterInfo() const {
    return RegisterInfo;
  }

  bool areMemAccessesTriviallyDisjoint(MachineInstr &MIa, MachineInstr &MIb,
                                       AliasAnalysis *AA) const override;
/*
  unsigned isLoadFromStackSlot(const MachineInstr &MI,
                               int &FrameIndex) const override;

  unsigned isLoadFromStackSlotPostFE(const MachineInstr &MI,
                                     int &FrameIndex) const override;

  unsigned isStoreToStackSlot(const MachineInstr &MI,
                              int &FrameIndex) const override;*/

  void copyPhysReg(MachineBasicBlock &MBB, MachineBasicBlock::iterator Position,
                   const DebugLoc &DL, unsigned DestinationRegister,
                   unsigned SourceRegister, bool KillSource) const override;

  void
  storeRegToStackSlot(MachineBasicBlock &MBB,
                      MachineBasicBlock::iterator Position,
                      unsigned SourceRegister, bool IsKill, int FrameIndex,
                      const TargetRegisterClass *RegisterClass,
                      const TargetRegisterInfo *RegisterInfo) const override;

  void
  loadRegFromStackSlot(MachineBasicBlock &MBB,
                       MachineBasicBlock::iterator Position,
                       unsigned DestinationRegister, int FrameIndex,
                       const TargetRegisterClass *RegisterClass,
                       const TargetRegisterInfo *RegisterInfo) const override;

  bool expandPostRAPseudo(MachineInstr &MI) const override;

/*  bool getMemOperandWithOffset(MachineInstr &LdSt, MachineOperand *&BaseOp,
                               int64_t &Offset,
                               const TargetRegisterInfo *TRI) const override;

  bool getMemOperandWithOffsetWidth(MachineInstr &LdSt, MachineOperand *&BaseOp,
                                    int64_t &Offset, unsigned &Width,
                                    const TargetRegisterInfo *TRI) const;*/

  std::pair<unsigned, unsigned>
  decomposeMachineOperandsTargetFlags(unsigned TF) const override;

  /*
  ArrayRef<std::pair<unsigned, const char *>>
  getSerializableDirectMachineOperandTargetFlags() const override;

  bool analyzeBranch(MachineBasicBlock &MBB, MachineBasicBlock *&TrueBlock,
                     MachineBasicBlock *&FalseBlock,
                     SmallVectorImpl<MachineOperand> &Condition,
                     bool AllowModify) const override;

  unsigned removeBranch(MachineBasicBlock &MBB,
                        int *BytesRemoved = nullptr) const override;*/

  // For a comparison instruction, return the source registers in SrcReg and
  // SrcReg2 if having two register operands, and the value it compares against
  // in CmpValue. Return true if the comparison instruction can be analyzed.
  /*bool analyzeCompare(const MachineInstr &MI, unsigned &SrcReg,
                      unsigned &SrcReg2, int &CmpMask,
                      int &CmpValue) const override;*/

  // See if the comparison instruction can be converted into something more
  // efficient. E.g., on Lanai register-register instructions can set the flag
  // register, obviating the need for a separate compare.
  /*bool optimizeCompareInstr(MachineInstr &CmpInstr, unsigned SrcReg,
                            unsigned SrcReg2, int CmpMask, int CmpValue,
                            const MachineRegisterInfo *MRI) const override;*/

  // Analyze the given select instruction, returning true if it cannot be
  // understood. It is assumed that MI->isSelect() is true.
  //
  // When successful, return the controlling condition and the operands that
  // determine the true and false result values.
  //
  //   Result = SELECT Cond, TrueOp, FalseOp
  //
  // Lanai can optimize certain select instructions, for example by predicating
  // the instruction defining one of the operands and sets Optimizable to true.
  bool analyzeSelect(const MachineInstr &MI,
                     SmallVectorImpl<MachineOperand> &Cond, unsigned &TrueOp,
                     unsigned &FalseOp, bool &Optimizable) const override;

  // Given a select instruction that was understood by analyzeSelect and
  // returned Optimizable = true, attempt to optimize MI by merging it with one
  // of its operands. Returns NULL on failure.
  //
  // When successful, returns the new select instruction. The client is
  // responsible for deleting MI.
  //
  // If both sides of the select can be optimized, the TrueOp is modifed.
  // PreferFalse is not used.
  /*MachineInstr *optimizeSelect(MachineInstr &MI,
                               SmallPtrSetImpl<MachineInstr *> &SeenMIs,
                               bool PreferFalse) const override;*/

  /*bool reverseBranchCondition(
      SmallVectorImpl<MachineOperand> &Condition) const override;

  unsigned insertBranch(MachineBasicBlock &MBB, MachineBasicBlock *TrueBlock,
                        MachineBasicBlock *FalseBlock,
                        ArrayRef<MachineOperand> Condition,
                        const DebugLoc &DL,
                        int *BytesAdded = nullptr) const override;*/
};

} // namespace llvm
#endif