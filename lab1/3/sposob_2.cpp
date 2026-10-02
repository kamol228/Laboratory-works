#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>

int main() {
    int quan;
    std::cin >> quan;
    omp_set_num_threads(quan);
    
    char messages[100][100];
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        sprintf(messages[thread_id], "Thread %d in %d - Hello World\n", 
                thread_id, quan);
    }
    
    for (int i = quan - 1; i >= 0; i--) {
        printf("%s", messages[i]);
    }
    
    system("pause");
    return 0;
}
