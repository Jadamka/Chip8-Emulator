#pragma once

#include "cpu.h"

void OP_00E0(CPU* cpu, uint16_t opcode);
void OP_1NNN(CPU* cpu, uint16_t opcode);
void OP_6XNN(CPU* cpu, uint16_t opcode);
void OP_7XNN(CPU* cpu, uint16_t opcode);
void OP_ANNN(CPU* cpu, uint16_t opcode);
void OP_DXYN(CPU* cpu, uint16_t opcode);