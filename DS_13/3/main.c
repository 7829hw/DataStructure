#include <stdio.h>
#include <stdlib.h>

#define ROW 8 // Number of run
#define COL 10 // Number of data of each run
#define WINNER_SIZE 16 // ROW * 2

int main(void)
{
    int run[ROW][COL];
    int winner[2 * ROW];
    int sorted[ROW * COL];
    int index[ROW] = { 0 };
    FILE* fp = NULL;
    fopen_s(&fp, "input.txt", "r");
    printf("<<<<<<<<<<<<< run data >>>>>>>>>>>>>>\n");

    // Get data from input.txt and put to run[][]
    for (int i = 0; i < ROW; i++) {
        printf("\n%d-th run\n", i + 1);
        for (int j = 0; j < COL; j++) {
            fscanf_s(fp, "%d", &run[i][j]);
            printf("%5d", run[i][j]);
        }
    }

    for (int i = 0; i < ROW; i++) { // Put data from run[][]
        winner[ROW + i] = run[i][index[i]];
    }

    for (int i = 0; i < ROW * COL; i++) {

        int depth = ROW;
        while (depth > 1) {
            depth /= 2;
            for (int j = depth; j < 2 * depth; j++) {
                winner[j] = winner[2 * j] < winner[2 * j + 1] ? winner[2 * j] : winner[2 * j + 1];
            }
        }
        for (int j = 0; j < ROW; j++) {
            if (winner[1] == run[j][index[j]]) {
                index[j]++;
                if (index[j] >= COL) // If index[j] over COL, put max value(9999)
                    winner[ROW + j] = 9999;
                else
                    winner[ROW + j] = run[j][index[j]];
                break;
            }
        }
        sorted[i] = winner[1];

        if (i == 0) { // Print only once
            printf("\n\nLevel-order traversal for initial min-winner tree\n");
            for (int i = 1; i < 2 * ROW; i++) {
                printf("%d ", winner[i]);
            }
        }
    }

    printf("\n\nsorting with min-winner tree...\n");
    printf("\nsorted result\n");
    for (int i = 0; i < ROW * COL; i++) {
        printf("%3d ", sorted[i]);
        if (i % 8 == 7)
            printf("\n");
    }
}