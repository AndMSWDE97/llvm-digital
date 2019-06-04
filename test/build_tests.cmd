@echo off

REM Parameters to feed debug execution
REM -march=digital -filetype=asm C:/LLVM_SRC/llvm-digital/test/simple_main/test.ll -o C:/LLVM_SRC/llvm-digital/test/simple_main/test.s

REM Test for a simple empty main method
"../build/Debug/bin/clang" simple_main/test.c -O3 --target=digital -S -emit-llvm -o simple_main/test.ll
"../build/Debug/bin/llc" -march=digital -relocation-model=pic -filetype=asm -debug-only=isel simple_main/test.ll -o simple_main/test.s

REM Test for a simple addition
REM "../build/Debug/bin/clang" add/test.c -O3 --target=digital -S -emit-llvm -o add/test.ll
REM "../build/Debug/bin/llc" -march=digital -relocation-model=pic -filetype=asm add/test.ll -o add/test.s
cmd /k