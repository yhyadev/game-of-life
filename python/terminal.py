import random

from typing import Self


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

    def swap(self, other_gen: Self):
        self.cells = other_gen.cells

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

                match self.cells[y][x]:
                    case 0:
                        if alive_neighbours == 3:
                            new_state = 1
                        else:
                            new_state = 0
                    case 1:
                        if alive_neighbours == 2 or alive_neighbours == 3:
                            new_state = 1
                        else:
                            new_state = 0
                    case _:
                        new_state = 0

                next_gen.cells[y][x] = new_state

        self.swap(next_gen)


def play():
    generation = Generation(150, 150)
    generation.random()

    while True:
        generation.display()
        generation.update()


play()
