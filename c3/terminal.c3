module terminal;

import std::io;

import libc;


fn float frand() {
    return (float)libc::rand() / (float)libc::RAND_MAX;
}

fn usz mod(usz a, usz b) {
    return ((a % b) + b) % b;
}

const usz GENERATION_WIDTH = 170;
const usz GENERATION_HEIGHT = 170;

def Generation = int[GENERATION_WIDTH][GENERATION_HEIGHT];

fn void generation_display(Generation *gen) {
	for (usz y = 0; y < GENERATION_HEIGHT; y++) {
		for (usz x = 0; x < GENERATION_WIDTH; x++) {
            io::print((*gen)[y][x] ? "●" : " ");
		}

        io::printn();
	}
}

fn void generation_random(Generation *gen) {
	for (usz y = 0; y < GENERATION_HEIGHT; y++) {
		for (usz x = 0; x < GENERATION_WIDTH; x++) {
            (*gen)[y][x] = (int)(frand() * 2);
		}
	}
}

fn int generation_calculate_alive_neighbours(Generation *gen, usz ix,
										  usz iy) {
	int amount = 0;

	for (int dy = -1; dy < 2; dy++) {
		for (int dx = -1; dx < 2; dx++) {
			if (dx == 0 && dy == 0) {
                continue;
            }

			usz x = mod((ix + dx), GENERATION_WIDTH);
			usz y = mod((iy + dy), GENERATION_HEIGHT);

            amount += (*gen)[y][x];
		}
	}

	return amount;
}

fn void generation_update(Generation *gen) {
	Generation next_gen;

	for (usz y = 0; y < GENERATION_HEIGHT; y++) {
		for (usz x = 0; x < GENERATION_WIDTH; x++) {
			int alive_neighbours =
				generation_calculate_alive_neighbours(gen, x, y);

			int current_cell = (*gen)[y][x];

			int next_state = ((current_cell && (alive_neighbours == 2 ||
												alive_neighbours == 3)) ||
							  (!current_cell && alive_neighbours == 3))
								 ? 1
								 : 0;

			next_gen[y][x] = next_state;
		}
	}

    *gen = next_gen;
}

fn void main() {
	Generation gen;

	generation_random(&gen);

	while (true) {
		generation_display(&gen);
        generation_update(&gen);
	}
}
