#pragma once

#include <SDL.h>
#include <SDL_audio.h>
#include <stdint.h>
#include <string>
#include <fstream>

// For audio: Beep()
#include <Windows.h>

#define FONT_START_ADDRESS 80 // 0x050 (should be to 0x09F, but its not needed, just make sure it doesnt go above 0x200)
#define START_ADDRESS 512 // 0x200 (noting should be in this memory until i fill it with data from ROM)

#define DISP_W 64
#define DISP_H 32
#define CPU_FREQ 500
#define TIMER_FREQ 60

class CPU
{
	private:
		void CallIns();
	public:
		CPU();
		~CPU();
		void Cycle();
		void Decrease();
		void LoadRom(const char* filename);

		bool shift_quirk;
		
		uint8_t memory[4096];
		uint8_t regs[16];
		uint16_t I;
		uint16_t pc;
		uint8_t sp;
		uint16_t stack[16];
		uint8_t delay;
		uint8_t sound;
		uint8_t keypad[16];
		uint8_t font[80] = // 5(bytes for each character) * 16(rows of characters)
		{
			0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
			0x20, 0x60, 0x20, 0x20, 0x70, // 1
			0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
			0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
			0x90, 0x90, 0xF0, 0x10, 0x10, // 4
			0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
			0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
			0xF0, 0x10, 0x20, 0x40, 0x40, // 7
			0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
			0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
			0xF0, 0x90, 0xF0, 0x90, 0x90, // A
			0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
			0xF0, 0x80, 0x80, 0x80, 0xF0, // C
			0xE0, 0x90, 0x90, 0x90, 0xE0, // D
			0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
			0xF0, 0x80, 0xF0, 0x80, 0x80  // F
		};
		uint32_t display[DISP_W * DISP_H];

		uint16_t opcode;
};
