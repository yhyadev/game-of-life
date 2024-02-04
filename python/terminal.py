import random


class Generation:
    def __init__(self, width: int, height: int):
        self.cells = [[0 for _ in range(width)] for _ in range(height)]

        self.width = width
        self.height = height

    def display(self):
        for y in range(self.height):
            for x in range(self.width):
                print("●" if self.cells[y][x] else " ", end="")

            print()

    def random(self):
        for y in range(self.height):
            for x in range(self.width):
                if random.random() > 0.90:
                    self.cells[y][x] = 1

    def calculate_alive_neigbours(self, ix: int, iy: int):
        amount = 0

        for dy in range(-1, 2):
            for dx in range(-1, 2):
                if dx == 0 and dy == 0:
                    continue

                x = (ix + dx) % self.width
                y = (iy + dy) % self.height

                if self.cells[y][x]:
                    amount += 1

        return amount

    def update(self):
        next_gen = self.__class__(self.width, self.height)

        for y in range(self.height):
            for x in range(self.width):
                alive_neighbours = self.calculate_alive_neigbours(x, y)

                current_cell = self.cells[y][x]

                if (
                    current_cell and (alive_neighbours == 2 or alive_neighbours == 3)
                ) or (not current_cell and alive_neighbours == 3):
                    next_state = 1
                else:
                    next_state = 0

                next_gen.cells[y][x] = next_state

        self.cells = next_gen.cells


def play():
    generation = Generation(170, 170)
    generation.random()

    while True:
        generation.display()
        generation.update()


play()
