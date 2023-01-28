#include <iostream>

#ifdef _OPENMP
#include <omp.h>
#else
#define omp_get_thread_num() 0
#endif

#define N 24

using namespace std;

int tid;

int main()
{
    cout << "Estableciendo la cantidad de Hilos!\n";

    int nHilos;

    cout << "Cuantos hilos quieres trabajar?: ";
    cin >> nHilos;

#ifdef _OPENMP
    omp_set_num_threads(nHilos);
#endif

#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        cout << "El thread " << tid << " esta en marcha\n"
             << endl;

        cout << "El thread " << tid << " ha terminado\n"
             << endl;
    }
}
