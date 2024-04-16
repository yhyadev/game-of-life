#include <stdbool.h>
#include <stddef.h>

#include "common.h"

#include "raylib/src/raylib.h"

#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 480
#define RESOLUTION 5

#define GENERATION_WIDTH (WINDOW_WIDTH / RESOLUTION)
#define GENERATION_HEIGHT (WINDOW_HEIGHT / RESOLUTION)

typedef int Generation[GENERATION_WIDTH][GENERATION_HEIGHT];

void generation_random(Generation gen) {
    for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
        for (size_t x = 0; x < GENERATION_WIDTH; x++) {
            gen[y][x] = (int)(frand() * 2);
        }
    }
}

void generation_display(Generation gen) {
    size_t w = WINDOW_WIDTH / GENERATION_WIDTH;
    size_t h = WINDOW_HEIGHT / GENERATION_HEIGHT;

    for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
        for (size_t x = 0; x < GENERATION_WIDTH; x++) {
            if (gen[y][x]) {
                DrawRectangle(x * w, y * h, w, h, WHITE);
            } else {
                DrawRectangle(x * w, y * h, w, h, BLACK);
            }

            DrawRectangleLines(x * w, y * h, w, h, BLACK);
        }
    }
}

int generation_calculate_alive_neighbours(Generation gen, size_t ix,
                                          size_t iy) {
    int amount = 0;

    for (int dy = -1; dy < 2; dy++) {
        for (int dx = -1; dx < 2; dx++) {
            if (dx == 0 && dy == 0)
                continue;

            size_t x = (ix + dx) % GENERATION_WIDTH;
            size_t y = (iy + dy) % GENERATION_HEIGHT;

            if (gen[y][x]) {
                amount++;
            }
        }
    }

    return amount;
}

void generation_update(Generation gen) {
    Generation next_gen = {0};

    for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
        for (size_t x = 0; x < GENERATION_WIDTH; x++) {
            int alive_neighbours =
                generation_calculate_alive_neighbours(gen, x, y);

            int current_cell = gen[y][x];

            int next_state = ((current_cell && (alive_neighbours == 2 ||
                                                alive_neighbours == 3)) ||
                              (!current_cell && alive_neighbours == 3))
                                 ? 1
                                 : 0;

            next_gen[y][x] = next_state;
        }
    }

    for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
        for (size_t x = 0; x < GENERATION_WIDTH; x++) {
            gen[y][x] = next_gen[y][x];
        }
    }
}

int main(void) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Conway's Game Of Life in Raylib");

    Generation gen = {0};

    generation_random(gen);

    while (!WindowShouldClose()) {
        BeginDrawing();

        generation_display(gen);
        generation_update(gen);

        EndDrawing();
    }

    CloseWindow();
}
