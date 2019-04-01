@echo off

REM Test for a simple empty main method
"../build/Debug/bin/clang" simple_main/test.c -S -emit-llvm -o simple_main/test.ll
"../build/Debug/bin/llc" -march=digital -relocation-model=pic -filetype=asm simple_main/test.ll -o simple_main/test.s

REM Test for a simple addition
"../build/Debug/bin/clang" add/test.c -S -emit-llvm -o add/test.ll
"../build/Debug/bin/llc" -march=digital -relocation-model=pic -filetype=asm add/test.ll -o add/test.s
cmd /k