cmake_minimum_required(VERSION 3.28.2)
project(CheckASM_NASM ASM_NASM)
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/result.cmake"
  "set(CMAKE_ASM_NASM_COMPILER \"${CMAKE_ASM_NASM_COMPILER}\")\n"
  
  )