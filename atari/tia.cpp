#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include "reada26.h"
#include "instructions.h"
#include "tia.h"
#include "SDL.h"

void start_sdl();
void end_sdl();

char running = 1;
const int WIDTH = 640;
const int HEIGHT = 384;
int x_pos = 0;
int y_pos = 0;

uint32_t* pixels = new uint32_t[640*384];
SDL_Window* tv = nullptr;
SDL_Renderer* ren = nullptr;
SDL_Texture * tex = nullptr;

void color_cycle() {
    x_pos++;
    if (x_pos == 228) {
        x_pos = 0;
        y_pos++;
    }

    if (x_pos > 68 && y_pos > 40 && y_pos < 232) {
        uint32_t color = rand()%4294967040;
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 4; i++) {
                pixels[4*(x_pos-68) + i + 640*(2*(y_pos-40) + j)] = color;
            }
        }
    }
}

void draw_frame() {
    x_pos = 0;
    y_pos = 0;
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_RenderClear(ren);
    SDL_UpdateTexture(tex, NULL, pixels, 640 * 4);
}

void init_graphics() {
    start_sdl();

    while (running) {
        color_cycle();
        color_cycle();
        color_cycle();

        compute_cycle();

        if (y_pos == 262) draw_frame();
    }

    end_sdl();
}

void start_sdl() {
    SDL_Init( SDL_INIT_VIDEO );
    tv = SDL_CreateWindow("atari", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(tv, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 384);

}

void end_sdl() {
    delete[] pixels;
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(tv);
    SDL_Quit();
}
