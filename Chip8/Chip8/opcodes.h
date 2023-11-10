#pragma once

#include "cpu.h"

void OP_00E0(CPU* cpu, uint16_t opcode);
void OP_00EE(CPU* cpu, uint16_t opcode);
void OP_1NNN(CPU* cpu, uint16_t opcode);
void OP_2NNN(CPU* cpu, uint16_t opcode);
void OP_3XNN(CPU* cpu, uint16_t opcode);
void OP_4XNN(CPU* cpu, uint16_t opcode);
void OP_5XY0(CPU* cpu, uint16_t opcode);
void OP_6XNN(CPU* cpu, uint16_t opcode);
void OP_7XNN(CPU* cpu, uint16_t opcode);
void OP_8XY0(CPU* cpu, uint16_t opcode);
void OP_8XY1(CPU* cpu, uint16_t opcode);
void OP_8XY2(CPU* cpu, uint16_t opcode);
void OP_8XY3(CPU* cpu, uint16_t opcode);
void OP_8XY4(CPU* cpu, uint16_t opcode);
void OP_8XY5(CPU* cpu, uint16_t opcode);
void OP_8XY6(CPU* cpu, uint16_t opcode);
void OP_8XY7(CPU* cpu, uint16_t opcode);
void OP_8XYE(CPU* cpu, uint16_t opcode);
void OP_9XY0(CPU* cpu, uint16_t opcode);
void OP_ANNN(CPU* cpu, uint16_t opcode);
void OP_BNNN(CPU* cpu, uint16_t opcode);
void OP_CXNN(CPU* cpu, uint16_t opcode);
void OP_DXYN(CPU* cpu, uint16_t opcode);
void OP_EX9E(CPU* cpu, uint16_t opcode);
void OP_EXA1(CPU* cpu, uint16_t opcode);
void OP_FX07(CPU* cpu, uint16_t opcode);
void OP_FX15(CPU* cpu, uint16_t opcode);
void OP_FX18(CPU* cpu, uint16_t opcode);
void OP_FX1E(CPU* cpu, uint16_t opcode);
void OP_FX0A(CPU* cpu, uint16_t opcode);
void OP_FX29(CPU* cpu, uint16_t opcode);
void OP_FX33(CPU* cpu, uint16_t opcode);
void OP_FX55(CPU* cpu, uint16_t opcode);
void OP_FX65(CPU* cpu, uint16_t opcode);