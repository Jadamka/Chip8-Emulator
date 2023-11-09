#include "cpu.h"
#include "opcodes.h"

#define FONT_START_ADDRESS 80 // 0x050 (should be to 0x09F, but its not needed, just make sure it doesnt go above 0x200)
#define START_ADDRESS 512 // 0x200 (noting should be in this memory until i fill it with data from ROM)

CPU::CPU()
{
	memset(memory, 0, sizeof(memory));
	memcpy(memory + FONT_START_ADDRESS, font, sizeof(font));
	memset(display, 0, sizeof(display));
	memset(regs, 0, sizeof(regs));
	memset(stack, 0, sizeof(stack));
	memset(keypad, 0, sizeof(keypad));

	pc = START_ADDRESS;
	sp = 0;
	delay = 0;
	sound = 0;
	flag = 0;
	I = 0;
	opcode = 0;
}

void CPU::CallIns()
{
	switch (opcode & 0xF000)
	{
		case 0x0000:
			OP_00E0(this, opcode);
			break;
		case 0x1000:
			OP_1NNN(this, opcode);
			break;
		case 0x6000:
			OP_6XNN(this, opcode);
			break;
		case 0x7000:
			OP_7XNN(this, opcode);
			break;
		case 0xA000:
			OP_ANNN(this, opcode);
			break;
		case 0xD000:
			OP_DXYN(this, opcode);
			break;
	}
}

void CPU::Cycle()
{
	opcode = (memory[pc] << 8| memory[pc + 1]);
	pc += 2;
	CallIns();

	if (delay > 0)
		delay--;
	if (sound > 0)
		sound--;
}

void CPU::LoadRom(const char* filename)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		printf("FAILED TO OPEN ROM FILE");
	}
	std::streampos size = file.tellg();
	file.seekg(0, std::ios::beg);
	file.read((char*)(&memory[START_ADDRESS]), size);
}