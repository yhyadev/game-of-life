package main

import (
	"fmt"
	"math/rand"
)

type Generation struct {
	cells  []int8
	width  int64
	height int64
}

func NewGeneration(width int64, height int64) Generation {
	cells := make([]int8, width*height)

	return Generation{
		cells,
		width,
		height,
	}
}

func (gen *Generation) randomize() {
	for y := range gen.height {
		for x := range gen.width {
			index := x + y*gen.width

			gen.cells[index] = int8(rand.Intn(2))
		}
	}
}

func (gen Generation) display() {
	for y := range gen.height {
		for x := range gen.width {
			index := x + y*gen.width

			if gen.cells[index] == 0 {
				fmt.Print(" ")
			} else {
				fmt.Print("●")
			}
		}

		fmt.Println()
	}
}

func (gen Generation) calculate_alive_neighbours(ix int64, iy int64) int8 {
	var amount int8 = 0

	for _, dy := range []int64{gen.height - 1, 0, 1} {
		for _, dx := range []int64{gen.width - 1, 0, 1} {
			if dx == 0 && dy == 0 {
				continue
			}

			x := (ix + dx) % gen.width
			y := (iy + dy) % gen.height

			index := x + y*gen.width

			amount += gen.cells[index]
		}
	}

	return amount
}

func (gen *Generation) update() {
	next_gen := NewGeneration(gen.width, gen.height)

	for y := range gen.height {
		for x := range gen.width {
			alive_neighbours := gen.calculate_alive_neighbours(x, y)

			index := x + y*gen.width

			current_cell := gen.cells[index]

			if (current_cell == 1 && (alive_neighbours == 2 || alive_neighbours == 3)) ||
				(current_cell == 0 && alive_neighbours == 3) {
				next_gen.cells[index] = 1
			} else {
				next_gen.cells[index] = 0
			}
		}
	}

	*gen = next_gen
}

func main() {
	gen := NewGeneration(170, 170)

	gen.randomize()

	for {
		gen.display()
		gen.update()
	}
}
