#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct board_parameters define_board_parameters();
int *initialize_board(int rows, int columns);
void simulate_board();

int main()
{
  simulate_board();

  return 0;
}

/****/

/* To make the board we need to know how many rows and columns it should have */
struct board_parameters { int rows, columns; };

struct board_parameters define_board_parameters()
{
  struct board_parameters x;
  printf("How many ROWS and COLUMNS do you want to build? ");
  scanf("%d", &x.rows);
  scanf("%d", &x.columns);

  return x;
}

/****/

/* This function will use the board_parameters struct to create a desired board */
int *initialize_board(int rows, int columns)
{
  /* Initialize random numbers generator */
  srand(time(NULL));

  /* Draw the board and fill it with 1s and 0s randomly
     1 is a live cell, 0 is a dead cell */
  int board[rows][columns];
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < columns; c++)
      board[r][c] = rand() % 2;

  /* Put the board array in a buffer - dynamically allocated memory space */
  int *buffer;
  buffer = (int*) malloc(rows * columns);
  int i = 0;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < columns; c++, i++) 
      buffer[i] = board[r][c];

  return buffer;
}

/****/

/* The whole game is simulated in this function that runs in a loop */
void simulate_board()
{
  /* Load the board parameters */
  struct board_parameters board_parameters;
  board_parameters = define_board_parameters();
  int rows = board_parameters.rows;
  int columns = board_parameters.columns;

  /* Access the buffer */
  int *buffer;
  buffer = initialize_board(rows, columns);

  /* Simulation */
  int board[rows][columns];
  while(1)
    {
      int i = 0;
      int neighbors, alive_neighbors;
      /* An array to store alive_neighbors relative to buffer[i] */
      int alive_neighbors_buff[rows * columns]; 

      /* This is a copy of buffer organized in a 2d array board,
         used to store the buffer's value before we change them
         and also to print out the board later */
      for (int r = 0; r < rows; r++) 
        for (int c = 0; c < columns; c++, i++) 
          board[r][c] = buffer[i];

      /* Actual simulation loop */
      for (int r = 0, i = 0; r < rows; r++)
        {
        for (int c = 0; c < columns; c++, i++)
          {
            /* Determine how many alive neighbors the cell has in order to
               change it's state in next generation.
               This is done by comparing adjacent rows and columns to 1 */
            alive_neighbors = 0;
            for (int r_move = -1; r_move <= 1; r_move++)
                for (int c_move = -1; c_move <= 1; c_move++)
                    if (!(r + r_move == r && c + c_move == c)
                        && (r + r_move >= 0 && r + r_move <= rows - 1)
                        && (c + c_move >= 0 && c + c_move <= columns - 1)
                        && board[r + r_move][c + c_move] == 1)
                      alive_neighbors++;

            /* Store alive_neighbors in the array relative to buffer */
            alive_neighbors_buff[i] = alive_neighbors;

            /* Print out the simulation */
            if (board[r][c] == 1)
              printf("* ");
            else
              printf("  ");
            if (c == columns - 1)
              printf("\n");
          }
        }

      /* Determine what will happen to the cell in next generation
         based on amount of alive neighbors */
      for (i = 0; i < rows * columns; i++)
        {
          if (buffer[i] == 1)
            {
              if (alive_neighbors_buff[i] < 2 || alive_neighbors_buff[i] > 3)
                buffer[i] = 0;
            }
          else if (buffer[i] == 0)
            {
              if (alive_neighbors_buff[i] == 3)
                buffer[i] = 1;
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
