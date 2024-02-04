#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

float frand(void) { return (float)rand() / (float)RAND_MAX; }

int mod(int a, int b) {
	int r = a % b;
	return r < 0 ? r + b : r;
}

#define GENERATION_WIDTH 170
#define GENERATION_HEIGHT 170

typedef int Generation[GENERATION_WIDTH][GENERATION_HEIGHT];

void generation_display(Generation gen) {
	for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
		for (size_t x = 0; x < GENERATION_WIDTH; x++) {
			if (gen[y][x]) {
				printf("●");
			} else {
				printf(" ");
			}
		}

		printf("\n");
	}
}

void generation_random(Generation gen) {
	for (size_t y = 0; y < GENERATION_HEIGHT; y++) {
		for (size_t x = 0; x < GENERATION_WIDTH; x++) {
			if (frand() > 0.90) {
				gen[y][x] = 1;
			}
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

			size_t x = mod(ix + dx, GENERATION_WIDTH);

			size_t y = mod(iy + dy, GENERATION_HEIGHT);

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
								 ? 2
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

		for (int i = 0; i < 40000000; i++)
			;
	}

	return 0;
}
