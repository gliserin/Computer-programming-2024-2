#include <stdio.h>

#define EMPTY 0
#define BLOCKED 9
#define MINE -1
#define MAX 100 // maximum row, col

void do_game();
void opening_dfs(int row, int col, int x, int y);
void make_board(int row, int col, int mines);
void print_board(int scr[MAX][MAX], int row, int col);
int click(int row, int col, int x, int y);
void init_screen(int row, int col);

int board[MAX][MAX];
int screen[MAX][MAX];

int main()
{
    char input;
    do {
        printf("Enter 'e' to exit or 's' to start: \n");
        scanf(" %c", &input);

        if(input == 'e')
        {
            break;
        }
        else if(input == 's')
        {
            do_game();
        }
        else
        {
            printf("Invalid input\n");
        }
    } while(input != 'e');

    return 0;
}

void do_game()
{
    int row, col, mines;

    printf("Enter row, col, mines: ");
    scanf("%d %d %d", &row, &col, &mines);

    if(row >= MAX || col >= MAX)
    {
        printf("Too big row or col\n");
        return;
    }

    make_board(row, col, mines);
    init_screen(row, col);

    // for debugging
    // print_board(board, row, col);
    
    do {
        int x, y, result;

        print_board(screen, row, col);
        printf("Enter x, y: ");
        scanf("%d %d", &x, &y);

        // exit game : x = -1, y = -1
        if(x == -1 && y == -1)
        {
            print_board(board, row, col);
            printf("Game stopped\n");
            break;
        }

        result = click(row, col, x, y);

        if(result == 1)
        {
            printf("Game over\n");
            print_board(board, row, col);
            break;
        }
        else if(result == 0)
        {
            printf("Good job\n");
            if(check_clear(row, col)) 
            {
                print_board(board, row, col);
                printf("Game clear\n");
                printf("Game clear\n");
                printf("Game clear\n");
                printf("Game clear\n");
                printf("Game clear\n");
                break;
            }
        }
        else if(result == -1) 
        {
            printf("Invalid input\n");
        }
        else 
        {
            printf("Unknown error\n");
        }
    } while(1);
}

int click(int row, int col, int x, int y)
{
    // check if x, y is out of bounds
    if(x < 0 || x >= row || y < 0 || y >= col)
    {
        return -1;
    }
    else if(screen[x][y] != BLOCKED)
    {
        return -1;
    }
    else if(board[x][y] == MINE)
    {
        return 1;
    }
    else
    {
        opening_dfs(row, col, x, y);
        return 0;
    }
}

void opening_dfs(int row, int col, int x, int y)
{
    if(x < 0 || x >= row || y < 0 || y >= col)
    {
        return;
    }
    else if(screen[x][y] != BLOCKED)
    {
        return;
    }
    // clicked tile is an empty (opening) -> open all adjacent tiles
    else if(board[x][y] == EMPTY)
    {
        screen[x][y] = board[x][y];

        opening_dfs(row, col, x - 1, y - 1);
        opening_dfs(row, col, x - 1, y);
        opening_dfs(row, col, x - 1, y + 1);
        opening_dfs(row, col, x, y - 1);
        opening_dfs(row, col, x, y + 1);
        opening_dfs(row, col, x + 1, y - 1);
        opening_dfs(row, col, x + 1, y);
        opening_dfs(row, col, x + 1, y + 1);
    }
    // clicked tile is a number -> open only clicked tile
    else if(board[x][y] >= 1 && board[x][y] <= 8)
    {
        screen[x][y] = board[x][y];
    }
}

void make_board(int row, int col, int mines)
{
    int i, j, k, x, y;

    if(mines > row * col)
    {
        printf("Too many mines\n");
        return;
    }

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            board[i][j] = EMPTY;
        }
    }

    for(k = 0; k < mines; k++)
    {
        x = rand() % row;
        y = rand() % col;

        if(board[x][y] == MINE)
        {
            k--;
        }
        else
        {
            board[x][y] = MINE;
        }
    }

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(board[i][j] == MINE)
            {
                for(x = i - 1; x <= i + 1; x++)
                {
                    for(y = j - 1; y <= j + 1; y++)
                    {
                        if(x >= 0 && x < row && y >= 0 && y < col && board[x][y] != MINE)
                        {
                            board[x][y]++;
                        }
                    }
                }
            }
        }
    }
}
void print_board(int scr[MAX][MAX], int row, int col)
{
    int i, j;

    // Print column numbers
    printf("  ");
    for(j = 0; j < col; j++)
    {
        printf("%2d", j);
    }
    printf("\n");

    for(i = 0; i < row; i++)
    {
        // Print row number
        printf("%2d ", i);
        for(j = 0; j < col; j++)
        {
            if(scr[i][j] == BLOCKED)
            {
                printf("# ");
            }
            else if(scr[i][j] == EMPTY)
            {
                printf(". ");
            }
            else if(scr[i][j] == MINE)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", scr[i][j]);
            }
        }
        printf("\n");
    }
}

void init_screen(int row, int col)
{
    int i, j;

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            screen[i][j] = BLOCKED;
        }
    }
}

int check_clear(int row, int col)
{
    int i, j;

    for(i = 0; i < row; i++)
    {
        for(j = 0; j < col; j++)
        {
            if(screen[i][j] == BLOCKED && board[i][j] != MINE)
            {
                return 0;
            }
        }
    }

    return 1;
}