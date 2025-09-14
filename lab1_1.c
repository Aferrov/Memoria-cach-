#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

int main() {
    static double A[MAX][MAX];
    static double x[MAX], y[MAX];
    int i, j;

    for (i = 0; i < MAX; i++) {
        x[i] = 1.0; 
        for (j = 0; j < MAX; j++) {
            A[i][j] = (double)(i + j);
        }
    }

    for (i = 0; i < MAX; i++) {
        y[i] = 0.0;
    }

    clock_t start1 = clock();
    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    clock_t end1 = clock();

    printf("Tiempo: %f segundos para primeros bucles(fila-columna)\n",
           (double)(end1 - start1) / CLOCKS_PER_SEC);

    for (i = 0; i < MAX; i++) {
        y[i] = 0.0;
    }

    clock_t start2 = clock();
    for (j = 0; j < MAX; j++) {
        for (i = 0; i < MAX; i++) {
            y[i] += A[i][j] * x[j];
        }
    }
    clock_t end2 = clock();

    printf("Tiempo: %f segundos para segundos bucles(columna-fila)\n",
           (double)(end2 - start2) / CLOCKS_PER_SEC);

    return 0;
}
