# MCTargetDesc/CMakeLists.txt
add_llvm_library(LLVMDigitalDesc
  DigitalMCTargetDesc.cpp
  DigitalMCAsmInfo.cpp
  )

  add_dependencies(LLVMDigitalDesc DigitalCommonTableGen)