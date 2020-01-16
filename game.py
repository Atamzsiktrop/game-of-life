#!/usr/bin/env python3

import os
import sys
import time
import random
import numpy

from board import *
from life import *


rows, cols = 40, 80
if rows <= 0 and cols <= 0:
    sys.exit(0)
board = Board(rows, cols)
life = Life(rows, cols)

# TODO: Better output (curses?).
while True:
    os.system("clear")
    board.update(life.get_cells())
    board.show()
    life.count_neighbors()
    life.nextgen()
    time.sleep(1)
