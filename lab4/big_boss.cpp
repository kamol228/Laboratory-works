#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<double> x, y, z;
int N;

double global_sum = 0.0;


void sum_x_func() {
    double local_sum = 0.0;
    for (int i = 0; i < N; i++) {
        local_sum += x[i];
    }
    #pragma omp critical
    {
        global_sum += local_sum;
    }
}


void sum_y_func() {
    double local_sum = 0.0;
    for (int i = 0; i < N; i++) {
        local_sum += y[i];
    }
    #pragma omp critical
    {
        global_sum += local_sum;
    }
}


void sum_z_func() {
    double local_sum = 0.0;
    for (int i = 0; i < N; i++) {
        local_sum += z[i];
    }
    #pragma omp critical
    {
        global_sum += local_sum;
    }
}

int main() {
    ifstream file("points.txt");
    if (!file.is_open()) {
        cout << "Cannot open points.txt\n";
        system("pause");
        return 1;
    }

    double a, b, c;
    while (file >> a >> b >> c) {
        x.push_back(a);
        y.push_back(b);
        z.push_back(c);
    }
    file.close();

    N = x.size();
    if (N == 0) {
        cout << "File is empty\n";
        system("pause");
        return 1;
    }

    cout << "Points: " << N << "\n";

    double start = omp_get_wtime();


    #pragma omp parallel sections
    {
        #pragma omp section
        { sum_x_func(); }

        #pragma omp section
        { sum_y_func(); }

        #pragma omp section
        { sum_z_func(); }
    }

    double end = omp_get_wtime();

    // Формула: (Σx + Σy + Σz) / (3N)
    double result = global_sum / (3.0 * N);

    printf("Global sum: %.4f\n", global_sum);
    printf("Result:     %.4f\n", result);
    printf("Time:       %.6f sec\n", end - start);

    system("pause");
    return 0;
}
