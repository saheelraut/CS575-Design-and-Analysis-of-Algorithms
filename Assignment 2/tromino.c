#include <stdio.h>
#include <stdlib.h>

int **tilematrix;

void tromino            /* function to do tiling */
    (int x_board,       /* x coordinate of board */
     int y_board,       /* y coordinate of board */
     int x_missing,     /* x coordinate of missing square */
     int y_missing,     /* y coordinate of missing square */
     int board_size,    /* The size of board to be operated on*/
     int **tilematrix); /* size of board, which is a power of 2*/

void tromino           /* function to do tiling */
    (int x_board,      /* x coordinate of board */
     int y_board,      /* y coordinate of board */
     int x_missing,    /* x coordinate of missing square */
     int y_missing,    /* y coordinate of missing square */
     int board_size,   /* The size of board to be operated on */
     int **tilematrix) /* size of board, which is a power of 2*/
{
    int x_center;
    int y_center;
    int x_upper_left;
    int y_upper_left;
    int x_upper_right;
    int y_upper_right;
    int x_lower_left;
    int y_lower_left;
    int x_lower_right;
    int y_lower_right;
    int half_size;
    half_size = board_size / 2;
    if (board_size == 2)
    {
        int i, j;
        for (i = x_board; i < (x_board + board_size); i++)
        {
            for (j = y_board; j < (y_board + board_size); j++)
            {
                if (!(i == x_missing && j == y_missing))
                {

                    if (x_missing == x_board && y_missing == y_board)
                    {
                        tilematrix[i][j] = 4; // Upper Right Position
                    }
                    else if (x_missing == (x_board + 1) && y_missing == y_board)
                    {
                        tilematrix[i][j] = 3; // Upper Left Position
                    }
                    else if (x_missing == (x_board + 1) && y_missing == (y_board + 1))
                    {
                        tilematrix[i][j] = 2; // Lower Left Postion
                    }
                    else if (x_missing == x_board && y_missing == (y_board + 1))
                    {
                        tilematrix[i][j] = 1; // Lower Right Postion
                    }
                }
            }
        }
        return;
    }

    x_center = x_board + half_size;
    y_center = y_board + half_size;

    if (x_missing < x_center && y_missing < y_center)
    {
        tilematrix[x_center - 1][y_center] = tilematrix[x_center][y_center] = tilematrix[x_center][y_center - 1] = 4;

        x_upper_left = x_missing;
        y_upper_left = y_missing;

        x_upper_right = x_center - 1;
        y_upper_right = y_center;

        x_lower_left = x_center;
        y_lower_left = y_center - 1;

        x_lower_right = x_center;
        y_lower_right = y_center;
    }
    else if (x_missing < x_center && y_missing >= y_center)
    {
        tilematrix[x_center - 1][y_center - 1] = tilematrix[x_center][y_center] = tilematrix[x_center][y_center - 1] = 1;

        x_upper_left = x_center - 1;
        y_upper_left = y_center - 1;

        x_upper_right = x_missing;
        y_upper_right = y_missing;

        x_lower_left = x_center;
        y_lower_left = y_center - 1;

        x_lower_right = x_center;
        y_lower_right = y_center;
    }
    else if (x_missing >= x_center && y_missing < y_center)
    {
        tilematrix[x_center - 1][y_center - 1] = tilematrix[x_center - 1][y_center] = tilematrix[x_center][y_center] = 3;

        x_upper_left = x_center - 1;
        y_upper_left = y_center - 1;

        x_upper_right = x_center - 1;
        y_upper_right = y_center;

        x_lower_left = x_missing;
        y_lower_left = y_missing;

        x_lower_right = x_center;
        y_lower_right = y_center;
    }
    else if (x_missing >= x_center && y_missing >= y_center)
    {
        tilematrix[x_center - 1][y_center - 1] = tilematrix[x_center - 1][y_center] = tilematrix[x_center][y_center - 1] = 2;

        x_upper_left = x_center - 1;
        y_upper_left = y_center - 1;

        x_upper_right = x_center - 1;
        y_upper_right = y_center;

        x_lower_left = x_center;
        y_lower_left = y_center - 1;

        x_lower_right = x_missing;
        y_lower_right = y_missing;
    }
    tromino(x_board, y_board, x_upper_left, y_upper_left, half_size, tilematrix);
    tromino(x_board, y_board + half_size, x_upper_right, y_upper_right, half_size, tilematrix);
    tromino(x_board + half_size, y_board, x_lower_left, y_lower_left, half_size, tilematrix);
    tromino(x_board + half_size, y_board + half_size, x_lower_right, y_lower_right, half_size, tilematrix);
}

void printtilematrix(int boardsize, int **matrix)
{
    int i, j;
    for (j = (boardsize - 1); j >= 0; j--)
    {
        for (i = 0; i < boardsize; i++)
        {
            if (tilematrix[i][j] == (-1))
            {
                printf("MS \t");
            }
            else if (tilematrix[i][j] == 1)
            {
                printf("LR \t");
            }
            else if (tilematrix[i][j] == 2)
            {
                printf("LL \t");
            }
            else if (tilematrix[i][j] == 3)
            {
                printf("UL \t");
            }
            else if (tilematrix[i][j] == 4)
            {
                printf("UR \t");
            }
        }
        printf("\n");
    }
}

int main()
{
    int board_size;
    int x_missing;
    int y_missing;
    int i, j;
    printf("Please enter size of board (Must be power of 2) (0 to quit): ");
    scanf("%d", &board_size);
    if ((board_size != 0) && ((board_size &(board_size - 1)) == 0))
    {
        printf("Please enter coordinates of missing square (separate by a space): ");
        scanf("%d%d", &x_missing, &y_missing);

        tilematrix = (int **)malloc(sizeof(int *) * board_size);
        for (i = 0; i < board_size; i++)
        {
            tilematrix[i] = malloc(board_size * sizeof *tilematrix[i]);
        }
        for (i = 0; i < board_size; i++)
        {
            for (j = 0; j < board_size; j++)
            {
                tilematrix[i][j] = 0;
            }
        }
        tilematrix[x_missing][y_missing] = -1;
        tromino(0, 0, x_missing, y_missing, board_size, tilematrix);
        printtilematrix(board_size, tilematrix);

        for (i = 0; i < board_size; i++)
        {
            free(tilematrix[i]);
        }
        free(tilematrix);
    }
    else
    {
        printf("The number entered is O or not power of 2 \nTerminating\n");
        return 0;
    }
}
