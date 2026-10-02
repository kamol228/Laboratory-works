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
        #pragma omp for ordered
        for (int i = 0; i < quan; i++) {
            #pragma omp ordered
            printf("Thread %d in %d - Hello World\n", quan - 1 - i, quan);
        }
    }
    
    system("pause");
    return 0;
}
