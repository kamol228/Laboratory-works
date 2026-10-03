#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ifstream file("points.txt");
    if (!file.is_open()) {
        cout << "Cannot open points.txt\n";
        system("pause");
        return 1;
    }

    vector<double> x, y, z;
    double a, b, c;
    while (file >> a >> b >> c) {
        x.push_back(a);
        y.push_back(b);
        z.push_back(c);
    }
    file.close();

    int N = x.size();
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

    #pragma omp parallel for reduction(+:sum_x, sum_y, sum_z) schedule(static)
    for (int i = 0; i < N; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_z += z[i];
    }

    double end = omp_get_wtime();

    double cx = sum_x / N;
    double cy = sum_y / N;
    double cz = sum_z / N;

    printf("Points: %d\n", N);
    printf("Center: (%.4f, %.4f, %.4f)\n", cx, cy, cz);
    printf("Time: %.4f sec\n", end - start);

    system("pause");
    return 0;
}

