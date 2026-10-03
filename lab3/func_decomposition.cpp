#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

vector<double> x, y, z;
int N;


double sum_x_func() {
    double sum = 0;
    for (int i = 0; i < N; i++) sum += x[i];
    return sum;
}


double sum_y_func() {
    double sum = 0;
    for (int i = 0; i < N; i++) sum += y[i];
    return sum;
}


double sum_z_func() {
    double sum = 0;
    for (int i = 0; i < N; i++) sum += z[i];
    return sum;
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

    int num_threads;
    cout << "Threads: ";
    cin >> num_threads;
    omp_set_num_threads(num_threads);

    double sum_x = 0, sum_y = 0, sum_z = 0;

    double start = omp_get_wtime();

 
#pragma omp parallel sections
    {
#pragma omp section
        { sum_x = sum_x_func(); }

#pragma omp section
        { sum_y = sum_y_func(); }

#pragma omp section
        { sum_z = sum_z_func(); }
    }

    double end = omp_get_wtime();

    double cx = sum_x / N;
    double cy = sum_y / N;
    double cz = sum_z / N;

    printf("quan: %d\n", N);
    printf("decide: (%.4f, %.4f, %.4f)\n", cx, cy, cz);
    printf("Vremya: %.4f sec\n", end - start);

    system("pause");
    return 0;
}
