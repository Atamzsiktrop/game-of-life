#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

struct board_parameters define_board_parameters();
int *initialize_board_buffer(int rows, int columns);
void next_generation(int alive_neighbors_array[],
                     int *board_buffer, int size);
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

/* This function will use the board_parameters struct to allocate space
   in memory for future board creation and also initialize live cells */
int *initialize_board_buffer(int rows, int columns)
{
  /* Initialize random numbers generator */
  srand(time(NULL));

  /*? Separate function ?*/
  /* Draw the board and fill it with 1s and 0s randomly
     1 is a live cell, 0 is a dead cell */
  int board[rows][columns];
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < columns; c++)
      board[r][c] = rand() % 2;

  /* Put the board array in a board_buffer - dynamically allocated memory space */
  int *board_buffer;
  int size = rows * columns;
  board_buffer = (int*) malloc(size);
  int i = 0;
  for (int r = 0; r < rows; r++)
    for (int c = 0; c < columns; c++, i++) 
      board_buffer[i] = board[r][c];

  return board_buffer;
}

/****/

/* Determine what will happen to the cell in next generation
   based on amount of alive neighbors and rules of the game */
void next_generation(int alive_neighbors_array[],
                     int *board_buffer, int size)
{
  for (int i = 0; i < size; i++)
    {
      if (board_buffer[i] == 1)
        {
          if (alive_neighbors_array[i] < 2 || alive_neighbors_array[i] > 3)
            board_buffer[i] = 0;
        }
      else if (board_buffer[i] == 0)
        {
          if (alive_neighbors_array[i] == 3)
            board_buffer[i] = 1;
        }
    }
}

/****/

/* The whole game is simulated in this function that runs in a loop */
void simulate_board()
{
  /* Load the board parameters and initialize it */
  struct board_parameters board_parameters;
  board_parameters = define_board_parameters();
  int rows = board_parameters.rows;
  int columns = board_parameters.columns;
  int board[rows][columns];

  /* Access the board_board_buffer */
  int *board_buffer;
  int size = rows * columns;
  board_buffer = initialize_board_buffer(rows, columns);

  /* An array that will hold alive_neighbors relative to board_buffer[i] */
  int alive_neighbors_array[size];

  /*? Find a decent exit condition. As of right now, Ctrl+C ?*/
  while(1)
    {
      int i = 0;
      int alive_neighbors;

      /* This is a copy of board_buffer organized in a 2d array board,
         used to store the board_buffer's value before we change them
         and also to print out the board later */
      for (int r = 0; r < rows; r++) 
        for (int c = 0; c < columns; c++, i++) 
          board[r][c] = board_buffer[i];

      /* Actual simulation loop */
      for (int r = 0, i = 0; r < rows; r++)
        {
        for (int c = 0; c < columns; c++, i++)
          {
            /*? Separate function ?*/
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

            /* Store alive_neighbors in alive_neighbors_array relative to board_buffer */
            alive_neighbors_array[i] = alive_neighbors;

            /* Print out the simulation */
            if (board[r][c] == 1)
              printf("* ");
            else
              printf("  ");
            if (c == columns - 1)
              printf("\n");
          }
        }

      /* Simulate next generation */
      next_generation(alive_neighbors_array,
                      board_buffer, size);

      /* "Update" method */
      /*? Eventually will move to GUI ?*/
      sleep(2);
      system("clear");
    }

  /* Free memory */
  free(board_buffer);
}

/****/
