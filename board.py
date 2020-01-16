#!/usr/bin/env python3

class Board:

    def __init__(self, rows, cols):
        self.rows = rows
        self.cols = cols
        self.board = [[" " for c in range((cols + 2))] for r in range(rows + 2)]

        # Initialize board borders:
        self.borders = [ "─", "│", "┌", "┐", "└", "┘" ]
        self.cstart, self.cend = 1, len(self.board[0]) - 1
        self.rstart, self.rend = 1, len(self.board) - 1
        # Horizontal
        for c in range(self.cstart, self.cend):
            self.board[0][c] = "─"
            self.board[self.rend][c] = "─"
        # Vertical
        for r in range(self.rstart, self.rend):
            self.board[r][0] = "│"
            self.board[r][self.cend] = "│"
        # Corners
        self.board[0][0] = "┌"                  # upper-left
        self.board[0][self.cend] = "┐"          # upper-right
        self.board[self.rend][0] = "└"          # lower-left
        self.board[self.rend][self.cend] = "┘"  # lower-right

    def show(self):
        """ Print out the board. """

        for r in range(len(self.board)):
            for c in range(len(self.board[0])):
                if self.board[r][c] in self.borders:
                    print(self.board[r][c], end="")
                elif self.board[r][c] == 0:
                    print(" ", end="")
                else:
                    print("*", end="")
            print("")

    def update(self, cells):
        """ Update board cells. Ignores borders. """

        for r in range(self.rstart, self.rend):
            for c in range(self.cstart, self.cend):
                self.board[r][c] = cells[r - 1][c - 1]

    def get_board(self):
        return self.board

    def get_rows(self):
        return self.rows

    def get_cols(self):
        return self.cols
