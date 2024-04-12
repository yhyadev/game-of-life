use rand::Rng;

#[derive(Clone)]
struct Generation {
    cells: Vec<u8>,
    width: usize,
    height: usize,
}

impl Generation {
    fn new(width: usize, height: usize) -> Generation {
        let mut cells = Vec::with_capacity(width * height);

        for _ in 0..height {
            for _ in 0..width {
                cells.push(0);
            }
        }

        Generation {
            cells,
            width,
            height,
        }
    }

    fn random(&mut self) {
        let mut rng = rand::thread_rng();

        for y in 0..self.height {
            for x in 0..self.width {
                let index = x + y * self.width;

                self.cells[index] = rng.gen_range(0..2);
            }
        }
    }

    fn display(&self) {
        for y in 0..self.height {
            let mut line = String::new();

            for x in 0..self.width {
                let index = x + y * self.width;

                if self.cells[index] == 1 {
                    line.push('●');
                } else {
                    line.push(' ');
                }
            }

            println!("{}", line);
        }
    }

    fn calculate_alive_neighbours(&self, ix: usize, iy: usize) -> u8 {
        let mut amount = 0;

        for dy in [self.height - 1, 0, 1].into_iter() {
            for dx in [self.width - 1, 0, 1].into_iter() {
                if dx == 0 && dy == 0 {
                    continue;
                }

                let x = (ix + dx) % self.width;
                let y = (iy + dy) % self.height;

                let index = x + y * self.width;

                amount += self.cells[index];
            }
        }

        amount
    }

    fn update(&mut self) {
        let mut next_generation = self.clone();

        for y in 0..self.height {
            for x in 0..self.width {
                let index = x + y * self.width;

                let alive_neighbours = self.calculate_alive_neighbours(x, y);

                let current_cell = self.cells[index];

                let next_state = if (current_cell == 1
                    && (alive_neighbours == 2 || alive_neighbours == 3))
                    || (current_cell == 0 && alive_neighbours == 3)
                {
                    1
                } else {
                    0
                };

                next_generation.cells[index] = next_state;
            }
        }

        self.cells = next_generation.cells;
    }
}

fn main() {
    let mut generation = Generation::new(170, 170);

    generation.random();

    loop {
        generation.display();
        generation.update();

        for _ in 0..40000000 {}
    }
}
