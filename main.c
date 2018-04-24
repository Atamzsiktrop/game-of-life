#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct table_parameters define_table_parameters();
int *initialize_table(int rows, int columns);
void simulate_table();

/****/

/* To make a table we need to know how many rows and columns it should have */
struct table_parameters {
  int rows;
  int columns;
};

struct table_parameters define_table_parameters()
{
  struct table_parameters x;
  printf("How many ROWS and COLUMNS do you want to build? ");
  scanf("%d", &x.rows);
  scanf("%d", &x.columns);

  return x;
}

/****/

/* This function will use the table_parameters struct to create a desired table */
int *initialize_table(int rows, int columns)
{
  /* Initialize random numbers generator */
  srand(time(NULL));

  /* Draw the table and fill with 1s and 0s randomly - 1 is a live cell, 0 is a dead cell */
  int table[rows][columns];
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) table[r][c] = rand() % 2;
  }

  /* Put the table array in a buffer - dynamically allocated memory space */
  int *buffer;
  buffer = (int*) malloc(rows * columns);
  int i = 0;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < columns; c++) {
      buffer[i] = table[r][c];
      i++;
    }
  }

  return buffer;
}

/****/

/* The whole game is simulated in this function that runs in a loop */
void simulate_table()
{
  /* Load the table parameters */
  struct table_parameters table_parameters;
  table_parameters = define_table_parameters();
  int rows = table_parameters.rows;
  int columns = table_parameters.columns;

  /* Access the buffer */
  int *buffer;
  buffer = initialize_table(rows, columns);

  /* Simulation */
  int table[rows][columns];
  while(1) {
    int i = 0;
    int neighbors, alive_neighbors;
    int alive_neighbors_buff[rows * columns]; /* An array to store alive_neighbors relative to buffer[i] */

    /* This is a copy of buffer organized in a 2d array table, used to store the buffer's values
       before we change them and also to print out the table later */
    for (int r = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++, i++) table[r][c] = buffer[i];
    }

    /* Actual simulation loop */
    for (int r = 0, i = 0; r < rows; r++) {
      for (int c = 0; c < columns; c++, i++) {
        /* Determine how many neighbors the cell has - this is a side effect of not being able to
           create an infinite table and cells in extreme rows/columns have to be treated differently */
        if ((r == 0 || r == rows - 1) && (c == 0 || c == columns - 1)) neighbors = 3;
        else if (r == 0 || r == rows - 1 || c == 0 || c == columns - 1) neighbors = 5;
        else neighbors = 8;

        /* Determine how many alive neighbors the cell has in order to change it's state in next
           generation */
        alive_neighbors = 0;
        if (neighbors == 8) {
          /* IF 8 NEIGHBORS */
          if (table[r][c - 1] == 1) alive_neighbors++;
          if (table[r][c + 1] == 1) alive_neighbors++;
          for (int move = -1; move <= 1; move++) {
            if (table[r - 1][c + move] == 1) alive_neighbors++;
            if (table[r + 1][c + move] == 1) alive_neighbors++;
          }
        } else if (neighbors == 5) {
          /* IF 5 NEIGHBORS */
          if (r == 0) {
            if (table[r][c - 1] == 1) alive_neighbors++;
            if (table[r][c + 1] == 1) alive_neighbors++;
            for (int move = -1; move <= 1; move++)
              if (table[r + 1][c + move] == 1) alive_neighbors++;
          } else if (r == rows - 1) {
            if (table[r][c - 1] == 1) alive_neighbors++;
            if (table[r][c + 1] == 1) alive_neighbors++;
            for (int move = -1; move <= 1; move++)
              if (table[r - 1][c + move] == 1) alive_neighbors++;
          } else if (c == 0) {
            if (table[r][c + 1] == 1) alive_neighbors++;
            for (int move = 0; move <= 1; move++) {
              if (table[r - 1][c + move] == 1) alive_neighbors++;
              if (table[r + 1][c + move] == 1) alive_neighbors++;
            }
          } else if (c == columns - 1) {
            if (table[r][c - 1] == 1) alive_neighbors++;
            for (int move = 0; move <= 1; move++) {
              if (table[r - 1][c - move] == 1) alive_neighbors++;
              if (table[r + 1][c - move] == 1) alive_neighbors++;
            }
          }
        } else if (neighbors == 3) {
          /* IF 3 NEIGHBORS */
          if (r == 0 && c == 0) {
            if (table[r][c + 1] == 1) alive_neighbors++;
            for (int move = 0; move <= 1; move++)
              if (table[r + 1][c + move] == 1) alive_neighbors++;
          } else if (r == 0 && c == columns - 1) {
            if (table[r][c - 1] == 1) alive_neighbors++;
            for (int move = 0; move <= 1; move++)
              if (table[r + 1][c - move] == 1) alive_neighbors++;
          } else if (r == rows - 1 && c == 0) {
            if (table[r][c + 1] == 1) alive_neighbors++;
            for (int move = 0; move <= 1; move++)
              if (table[r - 1][c + move] == 1) alive_neighbors++;
          } else if (r == rows - 1 && c == columns - 1) {
            if (table[r][c - 1] == 1) alive_neighbors++;
            for (int move = 0; move <= 1; move++)
              if (table[r - 1][c - move] == 1) alive_neighbors++;
          }
        }

        /* Store alive_neighbors in the array relative to buffer */
        alive_neighbors_buff[i] = alive_neighbors;

        /* Print out the simulation */
        if (table[r][c] == 1) printf("* ");
        else printf("  ");
        if (c == columns - 1) printf("\n");
      }
    }

    /* Determine what will happen to the cell in next generation, based on amount of alive neighbors */
    for (i = 0; i < rows * columns; i++) {
      if (buffer[i] == 1) {
        if (alive_neighbors_buff[i] < 2 || alive_neighbors_buff[i] > 3) buffer[i] = 0;
      } else if (buffer[i] == 0) {
        if (alive_neighbors_buff[i] == 3) buffer[i] = 1;
      }
    }

    /* "Update" method */
    sleep(2);
    system("clear");
  }

  /* Free memory */
  free(buffer);
}

/****/

int main()
{
  simulate_table();

  return 0;
}
