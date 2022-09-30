#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define MAX_STACK_SIZE 100

#define MALLOC(p, s) \
	if( !((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit( EXIT_FAILURE );\
	}

typedef struct {
	short int vert;
	short int horiz;
} offsets;

offsets move[8] = \
{ {.vert = -1, .horiz = 0}, { .vert = -1, .horiz = 1 }, \
{.vert = 0, .horiz = 1}, { .vert = 1, .horiz = 1 }, \
{.vert = 1, .horiz = 0}, { .vert = 1, .horiz = -1 }, \
{.vert = 0, .horiz = -1}, { .vert = -1, .horiz = -1 }};

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;

element stack[MAX_STACK_SIZE];
int top;

short int** maze;
short int** mark;

short int* newptr(int size);

short int exit_row;
short int exit_col;

void push(element item);
element pop();
void path(void);

int main(void)
{
	int row, col;
	FILE* fp = NULL;
	fopen_s(&fp, "input.txt", "r");

	fscanf_s(fp, "%d %d", &row, &col);
	exit_row = row, exit_col = col;

	MALLOC(maze, (row + 2) * sizeof(short int*));
	for (int i = 0; i < row + 2; i++)
	{
		maze[i] = newptr(col + 2);
	}

	MALLOC(mark, (row + 2) * sizeof(short int*));
	for (int i = 0; i < row + 2; i++)
	{
		mark[i] = newptr(col);
	}

	for (int i = 1; i < row + 1; i++)
	{
		short int tmp;
		for (int j = 1; j < col + 1; j++)
		{
			fscanf_s(fp, "%hd", &tmp);
			maze[i][j] = tmp;
		}
	}

	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{

			if (i == 0 || i == row + 1 || j == 0 || j == col + 1)
				maze[i][j] = 1;
		}
	}

	for (int i = 0; i < row + 2; i++)
	{
		for (int j = 0; j < col + 2; j++)
		{
			mark[i][j] = (short int)0;
		}
	}

	path();

	free(maze);
	free(mark);
	fclose(fp);

	return 0;
}

short int* newptr(int size)
{
	short int* new;
	MALLOC(new, size * sizeof(short int));
	return new;
}

void push(element item)
{
	stack[++top].row = item.row;
	stack[top].col = item.col;
	stack[top].dir = item.dir;
}

element pop()
{
	return stack[top--];
}

void path(void)
{
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1;
	top = 0;
	stack[0].row = 1;
	stack[0].col = 1;
	stack[0].dir = 1;
	while (top > -1 && !found)
	{
		position = pop();
		row = position.row;
		col = position.col;
		dir = position.dir;
		while (dir < 8 && !found)
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == exit_row && nextCol == exit_col)
			{
				found = TRUE;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
			{
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found)
	{
		printf("The path is:\n");
		printf("row col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", exit_row, exit_col);
	}
	else printf("The maze does not have a path\n");
}