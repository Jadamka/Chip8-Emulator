#include "cpu.h"
#include "opcodes.h"

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
	I = 0;
	opcode = 0;

	shift_quirk = false;
	load_store_quirk = false;
}

void CPU::CallIns()
{
	switch (opcode & 0xF000)
	{
		case 0x0000:
			if (opcode == 0x00E0)
				OP_00E0(this, opcode);
			else if (opcode == 0X00EE)
				OP_00EE(this, opcode);
			break;
		case 0x1000:
			OP_1NNN(this, opcode);
			break;
		case 0x2000:
			OP_2NNN(this, opcode);
			break;
		case 0x3000:
			OP_3XNN(this, opcode);
			break;
		case 0x4000:
			OP_4XNN(this, opcode);
			break;
		case 0x5000:
			OP_5XY0(this, opcode);
			break;
		case 0x6000:
			OP_6XNN(this, opcode);
			break;
		case 0x7000:
			OP_7XNN(this, opcode);
			break;
		case 0x8000:
			switch (opcode & 0x000F)
			{
				case 0x0000:
					OP_8XY0(this, opcode);
					break;
				case 0x0001:
					OP_8XY1(this, opcode);
					break;
				case 0x0002:
					OP_8XY2(this, opcode);
					break;
				case 0x0003:
					OP_8XY3(this, opcode);
					break;
				case 0x0004:
					OP_8XY4(this, opcode);
					break;
				case 0x0005:
					OP_8XY5(this, opcode);
					break;
				case 0x0006:
					OP_8XY6(this, opcode);
					break;
				case 0x0007:
					OP_8XY7(this, opcode);
					break;
				case 0x000E:
					OP_8XYE(this, opcode);
					break;
			}
			break;
		case 0x9000:
			OP_9XY0(this, opcode);
			break;
		case 0xA000:
			OP_ANNN(this, opcode);
			break;
		case 0xB000:
			OP_BNNN(this, opcode);
			break;
		case 0xC000:
			OP_CXNN(this, opcode);
			break;
		case 0xD000:
			OP_DXYN(this, opcode);
			break;
		case 0xE000:
			if ((opcode & 0x000F) == 0x000E)
				OP_EX9E(this, opcode);
			else if ((opcode & 0x000F) == 0x0001)
				OP_EXA1(this, opcode);
			break;
		case 0xF000:
			switch (opcode & 0x000F)
			{
				case 0x0007:
					OP_FX07(this, opcode);
					break;
				case 0x000A:
					OP_FX0A(this, opcode);
					break;
				case 0x0005:
					if ((opcode & 0x00F0) == 0x0010)
						OP_FX15(this, opcode);
					else if ((opcode & 0x00F0) == 0x0050)
						OP_FX55(this, opcode);
					else if ((opcode & 0x00F0) == 0x0060)
						OP_FX65(this, opcode);
					break;
				case 0x0008:
					OP_FX18(this, opcode);
					break;
				case 0x000E:
					OP_FX1E(this, opcode);
					break;
				case 0x0009:
					OP_FX29(this, opcode);
					break;
				case 0x0003:
					OP_FX33(this, opcode);
					break;
			}
			break;
	}
}

void CPU::Cycle()
{
	opcode = (memory[pc] << 8| memory[pc + 1]);
	printf("0x%X\n", opcode);
	pc += 2;
	CallIns();
}

void CPU::Decrease()
{
	if (delay > 0)
		delay--;
	if (sound > 0)
	{
		sound--;
		Beep(500, 1);
	}
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

CPU::~CPU()
{
}