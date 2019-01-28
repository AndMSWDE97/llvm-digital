
set(LLVM_TARGET_DEFINITIONS Digital.td)

tablegen(LLVM DigitalGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM DigitalGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM DigitalGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM DigitalGenMCPseudoLowering.inc -gen-pseudo-lowering)

add_public_tablegen_target(DigitalCommonTableGen)

add_llvm_target(DigitalCodeGen
  DigitalTargetMachine.cpp
  DigitalTargetObjectFile.cpp
  )

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
add_subdirectory(InstPrinter)