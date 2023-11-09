#include <SDL.h>
#include <stdio.h>
#include <chrono>

#include "cpu.h"

#define SCALE 10

int main(int argc, char* argv[])
{
	CPU cpu;
	cpu.LoadRom("roms/IBM-Logo.ch8");
	
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

	auto lastTime = std::chrono::high_resolution_clock::now();
	double nsPerCycle = 1000000000.0 / CPU_FREQ;
	double delta = 0;

	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsedTime = now - lastTime;
		lastTime = now;
		delta += elapsedTime.count() * 1000000000.0;

		while (delta >= nsPerCycle)
		{
			cpu.Cycle();
			delta -= nsPerCycle;
		}

		SDL_UpdateTexture(texture, nullptr, cpu.display, pitch);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}