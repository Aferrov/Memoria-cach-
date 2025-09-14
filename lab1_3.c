#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

void llenar(double *M, int n) {
    for (int i = 0; i < n * n; i++) {
        M[i] = (double)rand() / RAND_MAX;
    }
}

void ceros(double *M, int n) {
    for (int i = 0; i < n * n; i++) {
        M[i] = 0.0;
    }
}

void mult_clasica(double *A, double *B, double *C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i*n + j] += A[i*n + k] * B[k*n + j];
            }
        }
    }
}

void mult_bloque(double *A, double *B, double *C, int n, int Bsize) {
    for (int ii = 0; ii < n; ii += Bsize) {
        for (int jj = 0; jj < n; jj += Bsize) {
            for (int kk = 0; kk < n; kk += Bsize) {

                int i_max = min(ii + Bsize, n);
                int j_max = min(jj + Bsize, n);
                int k_max = min(kk + Bsize, n);

                for (int i = ii; i < i_max; i++) {
                    for (int j = jj; j < j_max; j++) {
                        for (int k = kk; k < k_max; k++) {
                            C[i*n + j] += A[i*n + k] * B[k*n + j];
                        }
                    }
                }
            }
        }
    }
}

double tiempo_transcurrido(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main() {
    srand(time(NULL));

    int n = 2000;      
    int Bsize = 64;

    double *A = malloc(n * n * sizeof(double));
    double *B = malloc(n * n * sizeof(double));
    double *C = malloc(n * n * sizeof(double));

    llenar(A, n);
    llenar(B, n);

    struct timespec start, end;

    ceros(C, n);
    clock_gettime(CLOCK_MONOTONIC, &start);
    mult_clasica(A, B, C, n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Clasica: %.6f segundos\n", tiempo_transcurrido(start, end));

    ceros(C, n);
    clock_gettime(CLOCK_MONOTONIC, &start);
    mult_bloque(A, B, C, n, Bsize);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Por bloques: %.6f segundos\n", Bsize, tiempo_transcurrido(start, end));

    free(A);
    free(B);
    free(C);

    return 0;
}
