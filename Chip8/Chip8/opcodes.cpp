#include "opcodes.h"

void OP_00E0(CPU* cpu, uint16_t opcode)
{
	memset(cpu->display, 0, sizeof(cpu->display));
}

void OP_1NNN(CPU* cpu, uint16_t opcode)
{
	uint16_t address = (opcode & 0x0FFF);
	
	cpu->pc = address;
}

void OP_6XNN(CPU* cpu, uint16_t opcode)
{
	uint16_t Vx = (opcode & 0x0F00) >> 8;
	uint16_t byte = (opcode & 0x00FF);

	cpu->regs[Vx] = byte;
}

void OP_7XNN(CPU* cpu, uint16_t opcode)
{
	uint16_t Vx = (opcode & 0x0F00) >> 8;
	uint16_t byte = (opcode & 0x00FF);

	cpu->regs[Vx] += byte;
}

void OP_ANNN(CPU* cpu, uint16_t opcode)
{
	uint16_t address = (opcode & 0x0FFF);

	cpu->I = address;
}

void OP_DXYN(CPU* cpu, uint16_t opcode)
{
	uint16_t Vx = (opcode & 0x0F00) >> 8;
	uint16_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t height = (opcode & 0x000F);

	uint8_t x = cpu->regs[Vx] % DISP_W;
	uint8_t y = cpu->regs[Vy] % DISP_H;

	cpu->flag = 0;

	for (unsigned int i = 0; i < height; i++)
	{
		uint8_t pixel = cpu->memory[cpu->I + i];
		for (unsigned int j = 0; j < 8; j++)
		{
			if (pixel & (0x80 >> j))
			{
				if (cpu->display[(x + j + ((y + i) * DISP_W))] == 0xFFFFFFFF)
					cpu->flag = 1;
				cpu->display[(x + j + ((y + i) * DISP_W))] ^= 0xFFFFFFFF;
			}
		}
	}
}