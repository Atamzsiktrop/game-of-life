#!/usr/bin/env python3

import random
import numpy


class Life:

    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.cells = numpy.random.randint(2, size=(rows, cols))
        self.acells = [[0 for c in range(cols)] for r in range(rows)]

    def count_neighbors(self):
        self.acells = self.cells.copy()

        for r in range(len(self.cells)):
            for c in range(len(self.cells[0])):
                alive_neighbors = 0
                for r_move in range(-1, 2):
                    for c_move in range(-1, 2):
                        if not (r + r_move == r and c + c_move == c):
                            r_curr = (r + r_move + self.rows) % self.rows;
                            c_curr = (c + c_move + self.cols) % self.cols;
                            alive_neighbors += self.cells[r_curr][c_curr]
                self.acells[r][c] = alive_neighbors

    def nextgen(self):
        # alive cells with 2 or 3 neighbors lives, else - dies
        # dead cells with 3 neighbors becomes alive

        for r in range(len(self.cells)):
            for c in range(len(self.cells[0])):
                if self.acells[r][c] > 3 or self.acells[r][c] < 2:
                    self.cells[r][c] = 0
                elif self.acells[r][c] == 3:
                    self.cells[r][c] = 1

    def get_cells(self):
        return self.cells

    def get_rows(self):
        return self.rows

    def get_cols(self):
        return self.cols
