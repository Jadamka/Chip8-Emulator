#include "opcodes.h"
#include <random>

void OP_00E0(CPU* cpu, uint16_t opcode)
{
	memset(cpu->display, 0, sizeof(cpu->display));
}

void OP_00EE(CPU* cpu, uint16_t opcode)
{
	cpu->pc = cpu->stack[--cpu->sp];
}

void OP_1NNN(CPU* cpu, uint16_t opcode)
{
	uint16_t address = (opcode & 0x0FFF);
	
	cpu->pc = address;
}

void OP_2NNN(CPU* cpu, uint16_t opcode)
{
	uint16_t address = (opcode & 0x0FFF);

	cpu->stack[cpu->sp++] = cpu->pc;
	cpu->pc = address;
}

void OP_3XNN(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = (opcode & 0x00FF);

	if (cpu->regs[Vx] == byte)
		cpu->pc += 2;
}

void OP_4XNN(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = (opcode & 0x00FF);

	if (cpu->regs[Vx] != byte)
		cpu->pc += 2;
}

void OP_5XY0(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	if (cpu->regs[Vx] == cpu->regs[Vy])
		cpu->pc += 2;
}

void OP_6XNN(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = (opcode & 0x00FF);

	cpu->regs[Vx] = byte;
}

void OP_7XNN(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = (opcode & 0x00FF);

	cpu->regs[Vx] += byte;
}

void OP_8XY0(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[Vx] = cpu->regs[Vy];
}

void OP_8XY1(CPU* cpu, uint16_t opcode)
{
	uint16_t Vx = (opcode & 0x0F00) >> 8;
	uint16_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[Vx] |= cpu->regs[Vy];
}

void OP_8XY2(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[Vx] &= cpu->regs[Vy];
}

void OP_8XY3(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[Vx] ^= cpu->regs[Vy];
}

void OP_8XY4(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[0xF] = ((cpu->regs[Vx] + cpu->regs[Vy]) > 0xFF);
	cpu->regs[Vx] += cpu->regs[Vy];
}

void OP_8XY5(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[0xF] = 0;
	if (cpu->regs[Vx] > cpu->regs[Vy])
		cpu->regs[0xF] = 1;

	cpu->regs[Vx] -= cpu->regs[Vy];
}

void OP_8XY6(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[Vx] = cpu->regs[Vy];
	cpu->regs[0xF] = (cpu->regs[Vx] & 0b1);
	cpu->regs[Vx] >>= 0b1;
}

void OP_8XY7(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[0xF] = 0;
	if (cpu->regs[Vx] < cpu->regs[Vy])
		cpu->regs[0xF] = 1;

	cpu->regs[Vx] = (cpu->regs[Vy] - cpu->regs[Vx]);
}

void OP_8XYE(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	cpu->regs[Vx] = cpu->regs[Vy];
	cpu->regs[0xF] = (cpu->regs[Vx] & 0x80) >> 7;
	cpu->regs[Vx] <<= 0b1;
}

void OP_9XY0(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;

	if (cpu->regs[Vx] != cpu->regs[Vy])
		cpu->pc += 2;
}

void OP_ANNN(CPU* cpu, uint16_t opcode)
{
	uint16_t address = (opcode & 0x0FFF);

	cpu->I = address;
}

void OP_BNNN(CPU* cpu, uint16_t opcode)
{
	uint16_t address = (opcode & 0x0FFF);

	cpu->pc = address + cpu->regs[0];
}

void OP_CXNN(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t byte = (opcode & 0x00FF);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 256);

	cpu->regs[Vx] = (distr(gen) & byte);
}

void OP_DXYN(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	uint8_t Vy = (opcode & 0x00F0) >> 4;
	uint8_t height = (opcode & 0x000F);

	uint8_t x = cpu->regs[Vx] % DISP_W;
	uint8_t y = cpu->regs[Vy] % DISP_H;

	cpu->regs[0xF] = 0;

	for (unsigned int i = 0; i < height; i++)
	{
		uint8_t pixel = cpu->memory[cpu->I + i];
		for (unsigned int j = 0; j < 8; j++)
		{
			if (pixel & (0x80 >> j))
			{
				if (cpu->display[(x + j + ((y + i) * DISP_W))] == 0xFFFFFFFF)
					cpu->regs[0xF] = 1;
				cpu->display[(x + j + ((y + i) * DISP_W))] ^= 0xFFFFFFFF;
			}
		}
	}
}

void OP_EX9E(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	if (cpu->keypad[cpu->regs[Vx]])
		cpu->pc += 2;
}

void OP_EXA1(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	if (!(cpu->keypad[cpu->regs[Vx]]))
		cpu->pc += 2;
}

void OP_FX07(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	cpu->regs[Vx] = cpu->delay;
}

void OP_FX15(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	cpu->delay = cpu->regs[Vx];
}

void OP_FX18(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	cpu->sound = cpu->regs[Vx];
}

void OP_FX1E(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	cpu->I += cpu->regs[Vx];

	if (cpu->I > 0x0FFF)
		cpu->regs[0xF] = 1;
}

void OP_FX0A(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;
	bool press = false;

	for (unsigned int i = 0; i < sizeof(cpu->keypad); i++)
	{
		if (cpu->keypad[i])
		{
			cpu->regs[Vx] = i;
			press = true;
			break;
		}
	}

	if (!press)
		cpu->pc -= 2;
}

void OP_FX29(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	cpu->I = FONT_START_ADDRESS + (cpu->regs[Vx] * 5); // Check later for errors
}

void OP_FX33(CPU* cpu, uint16_t opcode)
{
	uint8_t Vx = (opcode & 0x0F00) >> 8;

	cpu->memory[cpu->I + 2] = cpu->regs[Vx] % 10;
	cpu->memory[cpu->I + 1] = (cpu->regs[Vx] / 10) % 10;
	cpu->memory[cpu->I] = (cpu->regs[Vx] / 100) % 10;
}

void OP_FX55(CPU* cpu, uint16_t opcode)
{
	uint8_t x = (opcode & 0x0F00) >> 8;

	for (unsigned int i = 0; i <= x; i++)
	{
		cpu->memory[cpu->I + i] = cpu->regs[i];
	}
}

void OP_FX65(CPU* cpu, uint16_t opcode)
{
	uint8_t x = (opcode & 0x0F00) >> 8;

	for (int i = 0; i <= x; i++)
	{
		cpu->regs[i] = cpu->memory[cpu->I + i];
	}
}