#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <iostream>

int main() {
    int quan;
    std::cin >> quan;
    omp_set_num_threads(quan);
    
    int next_to_print = quan - 1;
    
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        
        while (true) {
            bool my_turn = false;
            
            #pragma omp critical
            {
                if (next_to_print == thread_id) {
                    my_turn = true;
                    next_to_print--;
                }
            }
            
            if (my_turn) {
                printf("Thread %d in %d - Hello World\n", thread_id, quan);
                break;
            }
        }
    }
    
    system("pause");
    return 0;
}
