
set(LLVM_TARGET_DEFINITIONS Digital.td)

tablegen(LLVM DigitalGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM DigitalGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM DigitalGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM DigitalGenMCPseudoLowering.inc -gen-pseudo-lowering)
tablegen(LLVM DigitalGenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM DigitalGenAsmWriter.inc -gen-asm-writer)

add_public_tablegen_target(DigitalCommonTableGen)

add_llvm_target(DigitalCodeGen
  DigitalTargetMachine.cpp
  DigitalTargetObjectFile.cpp
  DigitalAsmPrinter.cpp
  DigitalMachineFunction.cpp
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(InstPrinter)
add_subdirectory(AsmParser)