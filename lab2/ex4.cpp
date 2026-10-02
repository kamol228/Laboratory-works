#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>
using namespace std;

int row_a, col_a, row_b, col_b;

double** allocate_matrix(int rows, int cols) {
    double** m = new double* [rows];
    for (int i = 0; i < rows; i++) {
        m[i] = new double[cols];
    }
    return m;
}

void free_matrix(double** m, int rows) {
    for (int i = 0; i < rows; i++) delete[] m[i];
    delete[] m;
}

void fill_random(double** m, int rows, int cols,
    mt19937& gen, uniform_real_distribution<>& dis) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m[i][j] = dis(gen);
        }
    }
}

void multiply_serial(double** A, double** B, double** C,
    int ra, int ca, int cb) {
    for (int i = 0; i < ra; i++) {
        for (int j = 0; j < cb; j++) {
            double sum = 0.0;
            for (int k = 0; k < ca; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

void multiply_parallel(double** A, double** B, double** C,
    int ra, int ca, int cb, int num_threads) {
    omp_set_num_threads(num_threads);

#pragma omp parallel for schedule(static)
    for (int i = 0; i < ra; i++) {
        for (int j = 0; j < cb; j++) {
            double sum = 0.0;
            for (int k = 0; k < ca; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
}

int main() {
    cout << "Matrix A rows: ";
    cin >> row_a;
    cout << "Matrix A cols: ";
    cin >> col_a;
    cout << "Matrix B rows: ";
    cin >> row_b;
    cout << "Matrix B cols: ";
    cin >> col_b;
    cout << "Threads: ";
    int num_threads;
    cin >> num_threads;

    if (row_a <= 0 || col_a <= 0 || row_b <= 0 || col_b <= 0) {
        cout << "Sizes must be positive\n";
        system("pause");
        return 1;
    }
    if (col_a != row_b) {
        cout << "col_a must equal row_b\n";
        system("pause");
        return 1;
    }
    if (num_threads <= 0) {
        cout << "Threads must be positive\n";
        system("pause");
        return 1;
    }

    double** A = allocate_matrix(row_a, col_a);
    double** B = allocate_matrix(row_b, col_b);
    double** C_serial = allocate_matrix(row_a, col_b);
    double** C_parallel = allocate_matrix(row_a, col_b);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 10.0);

    fill_random(A, row_a, col_a, gen, dis);
    fill_random(B, row_b, col_b, gen, dis);

    // Последовательная
    double start_serial = omp_get_wtime();
    multiply_serial(A, B, C_serial, row_a, col_a, col_b);
    double end_serial = omp_get_wtime();
    double time_serial = end_serial - start_serial;

    // Параллельная
    double start_parallel = omp_get_wtime();
    multiply_parallel(A, B, C_parallel, row_a, col_a, col_b, num_threads);
    double end_parallel = omp_get_wtime();
    double time_parallel = end_parallel - start_parallel;

    // Вывод
    printf("Serial time:   %.4f sec\n", time_serial);
    printf("Parallel time: %.4f sec\n", time_parallel);

    free_matrix(A, row_a);
    free_matrix(B, row_b);
    free_matrix(C_serial, row_a);
    free_matrix(C_parallel, row_a);

    system("pause");
    return 0;
}
