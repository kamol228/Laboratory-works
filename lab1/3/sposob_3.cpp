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
        
        for (int i = quan - 1; i >= 0; i--) {
            #pragma omp barrier
            if (thread_id == i) {
                printf("Thread %d in %d - Hello World\n", thread_id, quan);
            }
            #pragma omp barrier
        }
    }
    
    system("pause");
    return 0;
}
