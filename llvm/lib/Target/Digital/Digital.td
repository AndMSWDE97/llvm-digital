//===-- DigitalOther.td - Describe the Digital Target Machine ----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the GNU General Public License Version 3.
// See LICENSE for details.
//
//===----------------------------------------------------------------------===//
// This is the top level entry point for the Digital target.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

include "DigitalRegisterInfo.td"
include "DigitalSchedule.td"
include "DigitalInstrInfo.td"

def DigitalInstrInfo : InstrInfo;

def DigitalAsmWriter : AsmWriter {
 string AsmWriterClassName = "InstPrinter";
 bit isMCAsmWriter = 1;
}

def DigitalAsmParser : AsmParser {
  let ShouldEmitMatchRegisterName = 0;
}

def DigitalAsmParserVariant : AsmParserVariant {
  int Variant = 0;

  // Recognize hard coded registers.
  string RegisterPrefix = "";
}

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",         []>;

//===---------------------------------------------------------------------===//
// Target Declaration
//===---------------------------------------------------------------------===//

def Digital : Target {
  let InstructionSet         = DigitalInstrInfo;
  let AssemblyWriters        = [DigitalAsmWriter];
  let AssemblyParsers        = [DigitalAsmParser];
  let AssemblyParserVariants = [DigitalAsmParserVariant];
}