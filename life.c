#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* This is a normal comment, usually explaining technical stuff. */
/*? This type of a comment is my development thoughts. ?*/
/****/ /* This is used to separate functions. */

struct board_parameters define_board_parameters();
int *allocate_board_buffer(int size);
int *count_alive_neighbors(int *board_buffer,
                           int rows, int columns, int size);
void next_generation(int *alive_neighbors_buffer,
                     int *board_buffer, int size);
void print_board(int *board_buffer, int rows, int columns);
void game_loop();

int main()
{
  game_loop();

  return 0;
}

/****/

/* To make the game board we need to know it's parameters. */
struct board_parameters { int rows, columns; };

/* Collect user input on the board's size. */
struct board_parameters define_board_parameters()
{
  struct board_parameters x;
  printf("How many ROWS and COLUMNS do you want to build? ");
  scanf("%d", &x.rows);
  scanf("%d", &x.columns);

  return x;
}

/****/

/*
 * This function will use the board_parameters struct to allocate space
 * in memory for future board creation and also initialize live cells.
 */
int *allocate_board_buffer(int size)
{
  int *board_buffer;
  board_buffer = malloc(sizeof(int) * size);

  /*
   * Initialize random numbers generator and fill the board_buffer
   * with random 0s and 1s.
   */
  srand(time(NULL));
  for (int i = 0; i < size; i++)
    board_buffer[i] = rand() % 2;

  return board_buffer;
}

/****/

/*
 * Counts alive neighbors of a cell, then passes the values to a function
 * that will determine what happens to the cell in the next generation.
 */
int *count_alive_neighbors(int *board_buffer,
                           int rows, int columns, int size)
{
  /*
   * This is a copy of board_buffer organized in a 2d array board,
   * used to store the board_buffer[i] value before we change them
   * and also to print out the board later.
   * This is necessary now and not in the next loop cause we need
   * to know values of the whole buffer ahead of the r,c loop.
   */
  int board[rows][columns], i;
  for (int r = 0, i = 0; r < rows; r++)
    for (int c = 0; c < columns; c++, i++)
      board[r][c] = board_buffer[i];

  /*
   * Buffer that will hold alive neighbors count relative to the cell.
   * This is later used to compare the values for next generation calculation.
   */
  int *alive_neighbors_buffer;
  alive_neighbors_buffer = malloc(sizeof(int) * size);

  for (int r = 0, i = 0; r < rows; r++)
    {
      for (int c = 0; c < columns; c++, i++)
        {
          /*
           * Count how many alive neighbors the cell has in order to
           * change it's state in next generation.
           * This is done by comparing adjacent rows and columns to 1.
           */
          int alive_neighbors = 0;
          for (int r_move = -1; r_move <= 1; r_move++)
            for (int c_move = -1; c_move <= 1; c_move++)
              if (!(r + r_move == r && c + c_move == c)
                  && (r + r_move >= 0 && r + r_move <= rows - 1)
                  && (c + c_move >= 0 && c + c_move <= columns - 1)
                  && board[r + r_move][c + c_move] == 1)
                alive_neighbors++;

          /*
           * Store alive_neighbors in alive_neighbors_buffer
           * relative to board_buffer[i].
           */
          alive_neighbors_buffer[i] = alive_neighbors;
        }
    }

  return alive_neighbors_buffer;
}

/****/

/*
 * Determine what will happen to the cell in next generation
 * based on amount of alive neighbors and rules of the game.
 */
void next_generation(int *alive_neighbors_buffer,
                     int *board_buffer, int size)
{
  for (int i = 0; i < size; i++)
    {
      if (board_buffer[i] == 1)
        {
          if (alive_neighbors_buffer[i] < 2 || alive_neighbors_buffer[i] > 3)
            board_buffer[i] = 0;
        }
      else if (board_buffer[i] == 0)
        {
          if (alive_neighbors_buffer[i] == 3)
            board_buffer[i] = 1;
        }
    }

  /* Free memory. */
  free(alive_neighbors_buffer);
}

/****/

/*? Make this function work with only board_buffer. ?*/
/*? Make a graphical version, move away from terminal. ?*/
/* Print the board/simulation. */
void print_board(int *board_buffer, int rows, int columns)
{
  int board[rows][columns], i;
  for (int r = 0, i = 0; r < rows; r++)
    for (int c = 0; c < columns; c++, i++)
      {
        board[r][c] = board_buffer[i];
        if (board[r][c] == 1)
          printf("* ");
        else
          printf("  ");
        if (c == columns - 1)
          printf("\n");
      }

  sleep(1);
  system("clear");
}

/****/

/* The game runs in this function. */
void game_loop()
{
  /* Access the board_parameters struct. */
  struct board_parameters board_parameters;
  board_parameters = define_board_parameters();
  int rows = board_parameters.rows;
  int columns = board_parameters.columns;
  int size = rows * columns;

  /* Access the board_buffer. */
  int *board_buffer;
  board_buffer = allocate_board_buffer(size);

  /*? Find a decent exit condition. As of right now, Ctrl+C. ?*/
  /* Simulation loop. */
  while(1)
    {
      print_board(board_buffer, rows, columns);
      next_generation(count_alive_neighbors(board_buffer,
                                            rows, columns, size),
                      board_buffer, size);
    }

  /* Free memory. */
  free(board_buffer);
}

/****/
