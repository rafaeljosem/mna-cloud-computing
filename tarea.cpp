#include <iostream>
#include <omp.h>

#define N 1000   // Tamaño de los arreglos
#define CHUNK 10 // Tamaño de los arreglos que serán distribuidos a los diferentes hilos
#define SHOW 10  // Cantidad de resultados a mostrar

// Declaración de la función que imprimirá los valores de cada arreglo
void printArray(float *d);

int main()
{
    printf("Sumando arreglos en paralelo! \nLos arreglos tienen tamaño de %d que se distribuirán en %d pedazos. \n\n", N, CHUNK);
    float a[N], b[N], c[N]; // Definición de los arreglos
    int i;                  // Variable de iteración

    // En este bloque se llenan los arreglos a y b con valores arbitrarios
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        b[i] = (i + 3) * 3.7;
    }

    int pieces = CHUNK;

/** En la siguiente sección se hace lo siguiente:
 * 1. Se define una región paralela con la directiva omp parallel
 *
 * 2. Se especifica que habrá un bucle for, para que el trabajo de
 * este bucle se divida en sub procesos
 *
 * 3. Se especifica que las variables a, b, c y pieces debe compartirse entre los subprocesos.
 * para esto se usa la cláusula shared
 *
 * 4. la cláusula private indica que la variabe i es privada. Esto evita que
 * los diferentes hilos accedan a la misma variable.
 *
 * 5. Con schedule se asigna la cantidad de iteraciones que debe ejecutar el bucle.
 * Dentro de la cláusula schedule se especifica el método static. Esto indica que la distribución
 * de los pedazos (chunks) se hace en orden (por ej. los primeros 10 van al hilo 0, los siguientes 10 al hilo 1, etc)
 *
 */
#pragma omp parallel for shared(a, b, c, pieces) private(i) \
    schedule(static, pieces)

    // Se realiza la suma de los arreglos
    for (i = 0; i < N; i++)
    {

        printf("El hilo %d está corriendo la iteración %d \n", omp_get_thread_num(), i);
        c[i] = a[i] + b[i];
    }

    // Se imprimen los resultados
    std::cout << "\nImprimiendo los primeros " << SHOW << " valores del arreglo a: " << std::endl;
    printArray(a);
    std::cout << "Imprimiendo los primeros " << SHOW << " valores del arreglo b: " << std::endl;
    printArray(b);
    std::cout << "Imprimiendo los primeros " << SHOW << " valores del arreglo c: " << std::endl;
    printArray(c);
}

void printArray(float *d)
{
    // Itera sobre cada arreglo e imprime el resultado de cada elemento
    for (int i = 0; i < SHOW; i++)
    {
        std::cout << d[i] << " - ";
        std::cout << std::endl;
    }
}