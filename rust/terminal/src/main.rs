use rand::Rng;

#[derive(Clone)]
struct Generation<const WIDTH: usize, const HEIGHT: usize> {
    board: [[u8; WIDTH]; HEIGHT],
}

impl<const WIDTH: usize, const HEIGHT: usize> Generation<WIDTH, HEIGHT> {
    fn new() -> Self {
        Generation {
            board: [[0; WIDTH]; HEIGHT],
        }
    }

    fn random(&mut self) {
        let mut rng = rand::thread_rng();

        for row in &mut self.board {
            for cell in row {
                *cell = rng.gen_range(0..2);
            }
        }
    }

    fn display(&self) {
        for row in &self.board {
            for cell in row {
                if *cell == 1 {
                    print!("●");
                } else {
                    print!(" ");
                }
            }

            println!();
        }
    }

    fn calculate_alive_neighbours(&self, ix: usize, iy: usize) -> u8 {
        let mut amount = 0;

        for dy in [HEIGHT - 1, 0, 1].into_iter() {
            for dx in [WIDTH - 1, 0, 1].into_iter() {
                if dx == 0 && dy == 0 {
                    continue;
                }

                let x = (ix + dx) % WIDTH;
                let y = (iy + dy) % HEIGHT;

                amount += self.board[y][x];
            }
        }

        amount
    }

    fn update(&mut self) {
        let mut next = Self::new();

        for (y, (cur_row, next_row)) in (&self.board).into_iter().zip(&mut next.board).enumerate() {
            for (x, (curr_cell, next_cell)) in cur_row.into_iter().zip(next_row).enumerate() {
                let alive_neighbours = self.calculate_alive_neighbours(x, y);

                *next_cell = match *curr_cell {
                    0 => match alive_neighbours {
                        3 => 1,
                        _ => 0,
                    },

                    1 => match alive_neighbours {
                        2 | 3 => 1,
                        _ => 0,
                    },

                    _ => 0,
                };
            }
        }

        self.board = next.board;
    }
}

fn main() {
    let mut generation = Generation::<170, 170>::new();

    generation.random();

    loop {
        generation.display();
        generation.update();
    }
}
