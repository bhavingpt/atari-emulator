#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include "reada26.h"
#include "instructions.h"
#include "tia.h"
#include "SDL.h"

void start_sdl();
void end_sdl();

char running = 1;
const int WIDTH = 640;
const int HEIGHT = 480;
int frame_depth = 0;

SDL_Window* tv = nullptr;
SDL_Renderer* ren = nullptr;
SDL_Surface* surf = nullptr;

void color_cycle() {
    frame_depth++;
}

void draw_frame() {
    SDL_Texture *text = SDL_CreateTextureFromSurface(ren, surf);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, text, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(17);

    SDL_DestroyTexture(text);
}

void init_graphics() {
    start_sdl();

    while (running) {
        color_cycle();
        color_cycle();
        color_cycle();

        compute_cycle();

        if (frame_depth == 228*262) draw_frame();
    }

    end_sdl();
}

void start_sdl() {
    SDL_Init( SDL_INIT_VIDEO );
    tv = SDL_CreateWindow("atari", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(tv, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    surf = SDL_LoadBMP("zilker.bmp");
}

void end_sdl() {
    SDL_FreeSurface(surf);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(tv);
    SDL_Quit();
}
