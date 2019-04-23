# MCTargetDesc/CMakeLists.txt
add_llvm_library(LLVMDigitalDesc
  DigitalMCTargetDesc.cpp
  DigitalMCAsmInfo.cpp
  DigitalELFObjectWriter.cpp
  DigitalMCCodeEmitter.cpp
  DigitalAsmBackend.cpp
  DigitalABIInfo.cpp
  )

  add_dependencies(LLVMDigitalDesc DigitalCommonTableGen)