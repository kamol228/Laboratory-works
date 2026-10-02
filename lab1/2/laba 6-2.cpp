// laba 6-2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <stdlib.h>
#include <omp.h>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int N;
    cout << "Enter size of array";
    cin >> N;
    if (N < 2) {
        cerr << "N must be >= 2" << endl;
        return 1;
    }
    vector<double> a(N);
    vector<double> b(N);
    for (int i = 0; i < N; i++) {
        a[i] = i;
    }
    b[0] = (a[0] + a[1]) / 3.0;
    b[N - 1] = (a[N - 1] + a[N - 2]) / 3.0;
    int num;
    cout << "Enter number of threads";
    cin >> num;
    omp_set_num_threads(num);
    double time = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 1; i < N - 1; i++) {
        b[i] = (a[i - 1] + a[i] + a[i + 1]) / 3.0;
    }
    double end_time = omp_get_wtime();
    printf("Time to exe - %f\n", end_time - time);
    return 0;
    
}
