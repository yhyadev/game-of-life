#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

float frand(void) { return (float)rand() / (float)RAND_MAX; }

#define GENERATION_WIDTH 170
#define GENERATION_HEIGHT 170

typedef int Generation[GENERATION_WIDTH][GENERATION_HEIGHT];

void generation_display(Generation gen) {
	for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
		for (size_t x = 0; x < GENERATION_WIDTH; x++) {
            printf(gen[y][x] ? "●" : " ");
		}

		printf("\n");
	}
}

void generation_random(Generation gen) {
	for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
		for (size_t x = 0; x < GENERATION_WIDTH; x++) {
            gen[y][x] = (int)(frand() * 2);
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
	Generation gen = {0};

	generation_random(gen);

	while (true) {
		generation_display(gen);
		generation_update(gen);
	}

	return 0;
}
