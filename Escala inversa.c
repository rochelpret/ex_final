import numpy as np

def escalar_sumar(arr1, arr2):
    n = len(arr1)
    for i in range(n):
        if arr2[i] != 0:
            arr2[i] = (arr1[i] / arr2[i]) + arr2[i]
        else:
            arr2[i] = float('inf')  # evitar división entre 0
    return arr2

if __name__ == "__main__":
    arr1 = np.array([float(i+1) for i in range(16)], dtype=np.float64)
    arr2 = np.array([float(i+5) for i in range(16)], dtype=np.float64)

    print("Antes:")
    print("arr1:", arr1)
    print("arr2:", arr2)

    resultado = escalar_sumar(arr1, arr2)

    print("Después:")
    print("arr2:", resultado)



//escalar sumar.c

#include <stddef.h>

void escalar_sumar(double* arr1, double* arr2, int n) {
    for (int i = 0; i < n; i++) {
        if (arr2[i] != 0.0) {
            arr2[i] = (arr1[i] / arr2[i]) + arr2[i];
        } else {
            arr2[i] = 1e9; // equivalente a infinito
        }
    }
}



//////ctypes
import ctypes
from ctypes import c_double, POINTER, c_int

# Cargar la biblioteca
lib = ctypes.CDLL('./libescalar.so')

# Firma de la función
lib.escalar_sumar.argtypes = [POINTER(c_double), POINTER(c_double), c_int]
lib.escalar_sumar.restype = None

def llamar_c(arr1, arr2):
    n = len(arr1)
    arr1_c = arr1.ctypes.data_as(POINTER(c_double))
    arr2_c = arr2.ctypes.data_as(POINTER(c_double))
    lib.escalar_sumar(arr1_c, arr2_c, n)
    return arr2

# Ejemplo de prueba
arr1 = np.array([float(i+1) for i in range(16)], dtype=np.float64)
arr2 = np.array([float(i+5) for i in range(16)], dtype=np.float64)

print("Llamando desde C...")
llamar_c(arr1, arr2)
print("Resultado desde C:", arr2)
