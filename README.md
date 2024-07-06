#include <stdio.h>

// Función para fusionar dos arreglos ordenados usando punteros
void merge(int *arr1, int size1, int *arr2, int size2, int *result) {
    int *p1 = arr1;          // Puntero al inicio de arr1
    int *p2 = arr2;          // Puntero al inicio de arr2
    int *p_result = result;  // Puntero al inicio de result

    // Comparar elementos de ambos arreglos y agregarlos al arreglo resultante
    while (p1 < arr1 + size1 && p2 < arr2 + size2) {
        if (*p1 <= *p2) {
            *p_result++ = *p1++;
        } else {
            *p_result++ = *p2++;
        }
    }

    // Agregar los elementos restantes de arr1, si hay
    while (p1 < arr1 + size1) {
        *p_result++ = *p1++;
    }

    // Agregar los elementos restantes de arr2, si hay
    while (p2 < arr2 + size2) {
        *p_result++ = *p2++;
    }
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result[size1 + size2];

    merge(arr1, size1, arr2, size2, result);

    printf("Array fusionado: ");
    for (int i = 0; i < size1 + size2; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}
/////////////////////////////////////////////////
#include <stdio.h>

// Función para fusionar dos arreglos ordenados
void merge(int arr1[], int size1, int arr2[], int size2, int result[]) {
    int i = 0, j = 0, k = 0;

    // Comparar elementos de ambos arreglos y agregarlos al arreglo resultante
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }

    // Agregar los elementos restantes de arr1, si hay
    while (i < size1) {
        result[k++] = arr1[i++];
    }

    // Agregar los elementos restantes de arr2, si hay
    while (j < size2) {
        result[k++] = arr2[j++];
    }
}

int main() {
    int arr1[] = {1, 3, 5, 7};
    int arr2[] = {2, 4, 6, 8};
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int result[size1 + size2];

    merge(arr1, size1, arr2, size2, result);

    printf("Array fusionado: ");
    for (int i = 0; i < size1 + size2; i++) {
        printf("%d ", result[i]);
    }

    return 0;
}
