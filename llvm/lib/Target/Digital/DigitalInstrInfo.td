//===- DigitalInstrInfo.td - Target Description for Digital Target -*- tablegen -*-=//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the GNU General Public License Version 3.
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Digital implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Digital profiles and nodes
//===----------------------------------------------------------------------===//

def SDT_DigitalRet          : SDTypeProfile<0, 1, [SDTCisInt<0>]>;
def SDT_DigitalCallSeqStart : SDCallSeqStart<[SDTCisVT<0, i16>]>;
def SDT_DigitalCallSeqEnd   : SDCallSeqEnd<[SDTCisVT<0, i16>, SDTCisVT<1, i16>]>;

def DigitalCallseq_start :
                     SDNode<"ISD::CALLSEQ_START", SDT_DigitalCallSeqStart,
                       [SDNPHasChain, SDNPOutGlue]>;
def DigitalCallseq_end :
                     SDNode<"ISD::CALLSEQ_END",   SDT_DigitalCallSeqEnd,
                       [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

def DigitalRet : SDNode<"DigitalISD::RET", SDTNone,
                       [SDNPHasChain, SDNPOptInGlue, SDNPVariadic]>;

//===----------------------------------------------------------------------===//
// Instruction format superclass
//===----------------------------------------------------------------------===//

include "DigitalInstrFormats.td"

//===----------------------------------------------------------------------===//
// Digital Operand, Complex Patterns and Transformations Definitions.
//===----------------------------------------------------------------------===//
// Instruction operand types

// Signed Operand
def simm16      : Operand<i32> {
  let DecoderMethod= "DecodeSimm16";
}

// Address operand
def mem : Operand<iPTR> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GPR, simm16);
  let EncoderMethod = "getMemEncoding";
}

// Node immediate fits as 16-bit sign extended on target immediate.
// e.g. addi, andi
def immSExt16  : PatLeaf<(imm), [{ return isInt<16>(N->getSExtValue()); }]>;

// Digital Address Mode! SDNode frameindex could possibily be a match
// since load and store instructions from stack used it.
def addr : 
  ComplexPattern<iPTR, 2, "SelectAddr", [frameindex], [SDNPWantParent]>;


class ArithLogic<bits<6> op, string instr_asm, SDNode OpNode,
                 InstrItinClass itin, RegisterClass RC, bit isComm = 0> :
  TwoRegs<op, (outs RC:$rd), (ins RC:$rf, RC:$rs),
     !strconcat(instr_asm, "\t$rd, $rs"),
     [(set RC:$rd, (OpNode RC:$rf, RC:$rs))], itin> {
  let isCommutable = isComm;	// e.g. add rb rc =  add rc rb
  let isReMaterializable = 1;
}

//@JumpFR {
let isBranch=1, isTerminator=1, isBarrier=1, hasDelaySlot = 1,
    isIndirectBranch = 1 in
class JumpFR<bits<6> op, string instr_asm, RegisterClass RC>:
  Return<op, (outs), (ins RC:$rs),
     !strconcat(instr_asm, "\t$rs"), [(brind RC:$rs)], IIBranch> {
}
//@JumpFR }

// Return instruction
class RetBase<RegisterClass RC>: JumpFR<0x35, "RRET", RC> {
  let isReturn = 1;
  let isCodeGenOnly = 1;
  let hasCtrlDep = 1;
  let hasExtraSrcRegAllocReq = 1;
}

let Defs = [SP], Uses = [SP] in {
def ADJCALLSTACKDOWN : DigitalPseudo<(outs), (ins i16imm:$amt1, i16imm:$amt2),
                              "#ADJCALLSTACKDOWN",
                              [(DigitalCallseq_start timm:$amt1, timm:$amt2)]>;
def ADJCALLSTACKUP   : DigitalPseudo<(outs), (ins i16imm:$amt1, i16imm:$amt2),
                              "#ADJCALLSTACKUP",
                              [(DigitalCallseq_end timm:$amt1, timm:$amt2)]>;
}

def NOP     : NoReg<0x0, (outs), (ins), "NOP", [], IIAlu>;

def MOV     : TwoRegs<0x1, (outs GPR:$rd), (ins GPR:$rs), "MOV $rd,$rs",
                [(set GPR:$rd, (load GPR:$rs))], IIAlu>;

def ADD     : ArithLogic<0x2, "ADD", add, IIAlu, GPR, 1>;
def SUB     : ArithLogic<0x4, "SUB", sub, IIAlu, GPR>;
def AND     : ArithLogic<0x6, "AND", and, IIAlu, GPR, 1>;
def OR      : ArithLogic<0x7, "OR",  or,  IIAlu, GPR, 1>;
def EOR     : ArithLogic<0x8, "EOR", xor, IIAlu, GPR, 1>;

def ST      : TwoRegs<0x26, (outs), (ins GPR:$rs, mem:$rd), "ST $rd, $rs", 
                [(store i16:$rs, addr:$rd)], IIStore>;

def BRK     : NoReg<0x3e, (outs), (ins), "BRK", [], IIAlu>;
def RETI    : NoReg<0x3f, (outs), (ins), "RETI", [], IIAlu>;

def JMP      : JumpFR<0x36, "JMP", GPR>;

let isReturn=1, isTerminator=1, isBarrier=1, hasCtrlDep=1 in {
  let hasDelaySlot=1 in
  def RET : DigitalPseudo<(outs), (ins), "" , [(DigitalRet)]>;
}

def RRET     : RetBase<GPR>;