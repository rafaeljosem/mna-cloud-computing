#include <iostream>
#include <omp.h>

int main(int argc, char *argv[])

{
    std::cout << "Regiones paralelas!\n";
    int hilos, tid;

#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        std::cout << "Trabajando en el thread: " << tid << std::endl;
        if (tid == 0)
        {
            hilos = omp_get_num_threads();
            std::cout << "Numero de threads es: " << hilos << std::endl;
        }
    }
}