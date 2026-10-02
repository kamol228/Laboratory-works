#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>

int main() {
    int quan;
    std::cin >> quan;
    omp_set_num_threads(quan);
#pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        printf("Thread %d in %d - Hello World\n", thread_id, quan);
    }
    system("pause");
    return 0;
}
