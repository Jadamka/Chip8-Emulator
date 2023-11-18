#include <SDL.h>
#include <stdio.h>
#include <chrono>

#include "cpu.h"

#define SCALE 10

int main(int argc, char* argv[])
{
	CPU cpu;
	std::string filename = "games/Space Invaders [David Winter].ch8";

	cpu.LoadRom(filename.c_str());

	if (filename.find("Space Invaders") != std::string::npos)
		cpu.shift_quirk = true;

	SDL_Window* window = 0;
	SDL_Renderer* renderer = 0;
	SDL_Texture* texture = 0;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL_Init error! SDL_Error: %s", SDL_GetError());
		return -1;
	}

	window = SDL_CreateWindow("Chip8", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISP_W * SCALE, DISP_H * SCALE, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, DISP_W, DISP_H);

	SDL_Event e;
	bool quit = false;

	int pitch = sizeof(cpu.display[0]) * DISP_W; // video pitch for update texture

	auto lastTimeCycle = std::chrono::high_resolution_clock::now();
	double nsPerCycle = 1000000000.0 / CPU_FREQ;
	double deltaCycle = 0;

	auto lastTimeDecrease = std::chrono::high_resolution_clock::now();
	double nsPerDecrase = 1000000000.0 / TIMER_FREQ;
	double deltaDecrease = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym)
					{
						case SDLK_1:
							cpu.keypad[0] = 1;
							break;
						case SDLK_2:
							cpu.keypad[1] = 1;
							break;
						case SDLK_3:
							cpu.keypad[2] = 1;
							break;
						case SDLK_4:
							cpu.keypad[3] = 1;
							break;
						case SDLK_q:
							cpu.keypad[4] = 1;
							break;
						case SDLK_w:
							cpu.keypad[5] = 1;
							break;
						case SDLK_e:
							cpu.keypad[6] = 1;
							break;
						case SDLK_r:
							cpu.keypad[7] = 1;
							break;
						case SDLK_a:
							cpu.keypad[8] = 1;
							break;
						case SDLK_s:
							cpu.keypad[9] = 1;
							break;
						case SDLK_d:
							cpu.keypad[10] = 1;
							break;
						case SDLK_f:
							cpu.keypad[11] = 1;
							break;
						case SDLK_z:
							cpu.keypad[12] = 1;
							break;
						case SDLK_x:
							cpu.keypad[13] = 1;
							break;
						case SDLK_c:
							cpu.keypad[14] = 1;
							break;
						case SDLK_v:
							cpu.keypad[15] = 1;
							break;
					}
					break;
				case SDL_KEYUP:
					switch (e.key.keysym.sym)
					{
						case SDLK_1:
							cpu.keypad[0] = 0;
							break;
						case SDLK_2:
							cpu.keypad[1] = 0;
							break;
						case SDLK_3:
							cpu.keypad[2] = 0;
							break;
						case SDLK_4:
							cpu.keypad[3] = 0;
							break;
						case SDLK_q:
							cpu.keypad[4] = 0;
							break;
						case SDLK_w:
							cpu.keypad[5] = 0;
							break;
						case SDLK_e:
							cpu.keypad[6] = 0;
							break;
						case SDLK_r:
							cpu.keypad[7] = 0;
							break;
						case SDLK_a:
							cpu.keypad[8] = 0;
							break;
						case SDLK_s:
							cpu.keypad[9] = 0;
							break;
						case SDLK_d:
							cpu.keypad[10] = 0;
							break;
						case SDLK_f:
							cpu.keypad[11] = 0;
							break;
						case SDLK_z:
							cpu.keypad[12] = 0;
							break;
						case SDLK_x:
							cpu.keypad[13] = 0;
							break;
						case SDLK_c:
							cpu.keypad[14] = 0;
							break;
						case SDLK_v:
							cpu.keypad[15] = 0;
							break;
						}
					break;
			}
		}

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTimeCycle = now - lastTimeCycle;
		lastTimeCycle = now;
		deltaCycle += elapsedTimeCycle.count() * 1000000000.0;

		while (deltaCycle >= nsPerCycle)
		{
			cpu.Cycle();
			deltaCycle -= nsPerCycle;
		}

		std::chrono::duration<double> elapsedTimeDecrease = now - lastTimeDecrease;
		lastTimeDecrease = now;
		deltaDecrease += elapsedTimeDecrease.count() * 1000000000.0;

		while (deltaDecrease >= nsPerDecrase)
		{
			cpu.Decrease();
			deltaDecrease -= nsPerDecrase;
		}

		SDL_UpdateTexture(texture, nullptr, cpu.display, pitch);
		SDL_RenderClear(renderer); // When object goes too up/down it crashes !!!
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}