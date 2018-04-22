#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct grid_parameters define_grid_parameters();
int *initialize_grid(int rows, int columns);
void simulate_grid();

/* To make a grid we need to know how many rows and columns it should have */
struct grid_parameters {
  int rows;
  int columns;
};

struct grid_parameters define_grid_parameters()
{
  struct grid_parameters x;
  printf("How many ROWS and COLUMNS do you want to build? ");
  scanf("%d", &x.rows);
  scanf("%d", &x.columns);

  return x;
}

/****/

/* This function will use the grid_parameters struct to create a desired grid */
int *initialize_grid(int rows, int columns)
{
  /* Initialize random numbers generator */
  srand(time(NULL));

  /* Draw the grid and fill with 1s and 0s randomly - 1 is a live cell, 0 is a dead cell */
  int grid[rows][columns];
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      //if (r == 0 || r == rows - 1 || c == 0 || c == columns - 1) grid[r][c] = 2;
      // ELSE:
      grid[r][c] = rand() % 2;
    }
  }

  /* Put the grid array in a buffer */
  int *buffer;
  buffer = (int*) malloc(rows * columns);
  int i = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      buffer[i] = grid[r][c];
      i++;
    }
  }

  return buffer;
}

/****/

/* The whole game is simulated in this function that runs in a loop */
void simulate_grid()
{
  /* Load the grid parameters */
  struct grid_parameters grid_parameters;
  grid_parameters = define_grid_parameters();
  int rows = grid_parameters.rows;
  int columns = grid_parameters.columns;

  /* Access the buffer */
  int *buffer;
  buffer = initialize_grid(rows, columns);

  /* Print the grid using a 2d array */
  /* For testing!
  int grid[rows][columns];
  int i = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
        grid[r][c] = buffer[i];
        printf("%d ", grid[r][c]);
        if (c == columns - 1) printf("\n");
        i++;
      }
  }
  */

  /* Simulation */
  int grid[rows][columns];
  int space_between = rows - 3;
  /*while(1) {*/
    sleep(2);
    int i = 0;
    int neighbors = 0;
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++) {
        grid[r][c] = buffer[i];
        if ((r == 0 || r == rows - 1) && (c == 0 || c == columns - 1)) neighbors = 3;
        else if (r == 0 || r == rows - 1 || c == 0 || c == columns - 1) neighbors = 5;
        else neighbors = 8;
        printf("%d ", grid[r][c]);
        if (c == columns - 1) printf("\n");
        i++;
      }
    }
    /*}*/

  /* Free memory */
  free(buffer);
}

/*
Game of Life rules:
Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

/****/

int main()
{
  simulate_grid();

  return 0;
}
