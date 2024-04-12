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
        let w = width / this.width;
        let h = height / this.height;

        stroke(255);
        fill(0);

        for (let y = 0; y < this.height; y++) {
            for (let x = 0; x < this.width; x++) {
                if (this.cells[y][x]) {
                    rect(
                        x * w,
                        y * h,
                        w,
                        h,
                    );
                }
            }
        }
    }

    calculate_alive_neighbours(ix, iy) {
        let amount = 0;

        for (let dy = -1; dy < 2; dy++) {
            for (let dx = -1; dx < 2; dx++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }

                let x = (ix + dx) % this.width;
                let y = (iy + dy) % this.height;

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
                let alive_neighbours = this.calculate_alive_neighbours(x, y);

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

let generation;

function setup() {
    frameRate(10);

    createCanvas(480, 480);

    generation = new Generation(width / 5, height / 5);

    generation.random();
}

function mouseDragged() {
    let x = floor(map(mouseX, 1, width, 0, generation.width));

    let y = floor(map(mouseY, 1, width, 0, generation.height));

    generation.cells[y][x] = 1;
}

function draw() {
    background(0);

    generation.display();
    generation.update();
}
