#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inicializar(double **M, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            M[i][j] = rand() % 10;
        }
    }
}

void multiplicar(double **A, double **B, double **C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double suma = 0.0;
            for (int k = 0; k < n; k++) {
                suma += A[i][k] * B[k][j];
            }
            C[i][j] = suma;
        }
    }
}

int main() {
    srand(0);

    int tamanos[] = {100, 500, 1000};
    int num_tamanos = sizeof(tamanos) / sizeof(tamanos[0]);

    printf("%10s %20s\n", "N", "Tiempo (segundos)");
    printf("------------------------------\n");

    for (int t = 0; t < num_tamanos; t++) {
        int n = tamanos[t];

        double **A = (double **)malloc(n * sizeof(double *));
        double **B = (double **)malloc(n * sizeof(double *));
        double **C = (double **)malloc(n * sizeof(double *));
        for (int i = 0; i < n; i++) {
            A[i] = (double *)malloc(n * sizeof(double));
            B[i] = (double *)malloc(n * sizeof(double));
            C[i] = (double *)malloc(n * sizeof(double));
        }

        inicializar(A, n);
        inicializar(B, n);

        clock_t start = clock();
        multiplicar(A, B, C, n);
        clock_t end = clock();

        double tiempo = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%10d %20f\n", n, tiempo);

        for (int i = 0; i < n; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}
