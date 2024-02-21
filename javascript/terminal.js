function mod(a, b) {
    let r = a % b;
    return r < 0 ? r + b : r;
}

class Generation {
    constructor(width, height) {
        this.cells = new Array(height);

        for (let y = 0; y < height; y++) {
            this.cells[y] = new Array(width).fill(0);
        }

        this.width = width;
        this.height = height;
    }

    random() {
        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                this.cells[y][x] = Math.floor(Math.random() * 2);
            }
        }
    }

    display() {
        for (let y = 0; y < this.height; y++) {
            let line = "";

            for (let x = 0; x < this.width; x++) {
                line += this.cells[y][x] ? "●" : " ";
            }

            console.log(line);
        }
    }

    calculate_alive_neigbours(ix, iy) {
        let amount = 0;

        for (let dy = -1; dy < 2; dy++) {
            for (let dx = -1; dx < 2; dx++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }

                let x = mod(ix + dx, this.width);
                let y = mod(iy + dy, this.height);

                if (this.cells[y][x]) {
                    amount += 1;
                }
            }
        }

        return amount;
    }

    update() {
        let next_gen = new Generation(this.width, this.height);

        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                let alive_neighbours = this.calculate_alive_neigbours(x, y);

                let current_cell = this.cells[y][x];

                let next_state =
                    (current_cell &&
                        (alive_neighbours == 2 || alive_neighbours == 3)) ||
                    (!current_cell && alive_neighbours == 3)
                        ? 1
                        : 0;

                next_gen.cells[y][x] = next_state;
            }
        }

        this.cells = next_gen.cells;
    }
}

let generation = new Generation(170, 170);

function play() {
    generation.random();

    while (true) {
        generation.display();
        generation.update();
    }
}

play();
