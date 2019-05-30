//===-- DigitalISelLowering.cpp - Digital DAG Lowering Implementation  --------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Digital uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#include "DigitalISelLowering.h"
#include "Digital.h"
#include "DigitalRegisterInfo.h"
#include "DigitalSubtarget.h"
#include "DigitalTargetMachine.h"
#include "DigitalMachineFunction.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/SelectionDAGNodes.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/DiagnosticPrinter.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "digital-lower"

DigitalTargetLowering::DigitalTargetLowering(const TargetMachine &TM, const DigitalSubtarget &STI)
    : TargetLowering(TM) {

  addRegisterClass(MVT::i16, &Digital::GPRRegClass);

  computeRegisterProperties(STI.getRegisterInfo());

  setStackPointerRegisterToSaveRestore(Digital::SP);

  setTargetDAGCombine(ISD::ADD);
  setTargetDAGCombine(ISD::SUB);
  setTargetDAGCombine(ISD::AND);
  setTargetDAGCombine(ISD::OR);
  setTargetDAGCombine(ISD::XOR);

  setBooleanContents(ZeroOrOneBooleanContent);
  setMinFunctionAlignment(2);
  setPrefFunctionAlignment(2);
}

SDValue DigitalTargetLowering::LowerOperation(SDValue Op,
                                            SelectionDAG &DAG) const {
  switch (Op.getOpcode()) {
  default:
    report_fatal_error("unimplemented operand");
  }
}

// Calling Convention Implementation.
#include "DigitalGenCallingConv.inc"

// Transform physical registers into virtual registers.
SDValue DigitalTargetLowering::LowerFormalArguments(
    SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
    const SmallVectorImpl<ISD::InputArg> &Ins, const SDLoc &DL,
    SelectionDAG &DAG, SmallVectorImpl<SDValue> &InVals) const {

  switch (CallConv) {
  default:
    report_fatal_error("Unsupported calling convention");
  case CallingConv::C:
    break;
  }

  MachineFunction &MF = DAG.getMachineFunction();
  MachineRegisterInfo &RegInfo = MF.getRegInfo();

  if (IsVarArg)
    report_fatal_error("VarArg not supported");

  // Assign locations to all of the incoming arguments.
  SmallVector<CCValAssign, 16> ArgLocs;
  CCState CCInfo(CallConv, IsVarArg, MF, ArgLocs, *DAG.getContext());
  CCInfo.AnalyzeFormalArguments(Ins, CC_Digital);

  for (auto &VA : ArgLocs) {
    if (!VA.isRegLoc())
      report_fatal_error("Defined with too many args");

    // Arguments passed in registers.
    EVT RegVT = VA.getLocVT();
    if (RegVT != MVT::i16) {
      //DEBUG(dbgs() << "LowerFormalArguments Unhandled argument type: " << RegVT.getEVTString() << "\n");
      report_fatal_error("unhandled argument type");
    }
    const unsigned VReg = RegInfo.createVirtualRegister(&Digital::GPRRegClass);
    RegInfo.addLiveIn(VA.getLocReg(), VReg);
    SDValue ArgIn = DAG.getCopyFromReg(Chain, DL, VReg, RegVT);

    InVals.push_back(ArgIn);
  }
  return Chain;
}

SDValue
DigitalTargetLowering::LowerReturn(SDValue Chain, CallingConv::ID CallConv,
                                 bool IsVarArg,
                                 const SmallVectorImpl<ISD::OutputArg> &Outs,
                                 const SmallVectorImpl<SDValue> &OutVals,
                                 const SDLoc &DL, SelectionDAG &DAG) const {
  if (IsVarArg) {
    report_fatal_error("VarArg not supported");
  }
  MachineFunction &MF = DAG.getMachineFunction();
  DigitalFunctionInfo *FuncInfo = MF.getInfo<DigitalFunctionInfo>();

  // Stores the assignment of the return value to a location.
  SmallVector<CCValAssign, 16> RVLocs;

  // Info about the registers and stack slot.
  CCState CCInfo(CallConv, IsVarArg, DAG.getMachineFunction(), RVLocs,
                 *DAG.getContext());

  CCInfo.AnalyzeReturn(Outs, RetCC_Digital);

  SDValue Flag;
  SmallVector<SDValue, 4> RetOps(1, Chain);

  RetOps.push_back(DAG.getTargetConstant(FuncInfo->getBytesToPopOnReturn(), DL, MVT::i16));

  // Copy the result values into the output registers.
  for (unsigned i = 0, e = RVLocs.size(); i < e; ++i) {
    CCValAssign &VA = RVLocs[i];
    assert(VA.isRegLoc() && "Can only return in registers!");

    Chain = DAG.getCopyToReg(Chain, DL, VA.getLocReg(), OutVals[i], Flag);

    // Guarantee that all emitted copies are stuck together.
    Flag = Chain.getValue(1);
    RetOps.push_back(DAG.getRegister(VA.getLocReg(), VA.getLocVT()));
  }

  RetOps[0] = Chain; // Update chain.

  // Add the flag if we have it.
  if (Flag.getNode()) {
    RetOps.push_back(Flag);
  }

  return DAG.getNode(DigitalISD::RET, DL, MVT::Other, RetOps);
}

const char *DigitalTargetLowering::getTargetNodeName(unsigned Opcode) const {
  switch ((DigitalISD::NodeType)Opcode) {
  case DigitalISD::FIRST_NUMBER:
    break;
  case DigitalISD::RET:
    return "DigitalISD::RET";
  }
  return nullptr;
}