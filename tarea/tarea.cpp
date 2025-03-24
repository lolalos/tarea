#include <iostream>
#include <omp.h>

#define N 100  // Tamaño del arreglo

int main() {
    int A[N], B[N], C[N];

    // Inicialización de los arreglos A y B
    for (int i = 0; i < N; i++) {
        A[i] = i + 1;  // A = {1, 2, 3, ..., N}
        B[i] = (N - i); // B = {N, N-1, ..., 1}
    }

    // Forzar la ejecución con exactamente 2 hilos
    omp_set_num_threads(2);

    // Paralelización de la suma con OpenMP
#pragma omp parallel
    {
        int id = omp_get_thread_num();
        int num_hilos = omp_get_num_threads();

        if (num_hilos != 2) {
            std::cerr << "Error: No se están ejecutando exactamente 2 hilos." << std::endl;
            exit(1);
        }

        int inicio = id * (N / 2);
        int fin = (id + 1) * (N / 2);

        std::cout << "Hilo " << id << " procesando desde " << inicio << " hasta " << fin - 1 << std::endl;

        for (int i = inicio; i < fin; i++) {
            C[i] = A[i] + B[i];  // Realiza la suma paralela
        }
    }

    // Verificación de la suma correcta
    std::cout << "Primeros 10 valores de C:" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "C[" << i << "] = " << C[i] << " (esperado: " << N + 1 << ")" << std::endl;
    }

    return 0;
}
