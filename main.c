/** Ejercicio 1.12
Desarrollar una función para que, dada una matriz cuadrada de reales de orden N, obtenga la
sumatoria de los elementos que están por encima de la diagonal principal (excluida ésta). Lo mismo
para la diagonal secundaria. Lo mismo incluyendo la diagonal. Lo mismo, con los que están por
debajo de la diagonal.

- crear vector = InicializadorMatriz
- vector lleno = ingresarDatos
- vector vacío = modificarMatriz
- insertar elemento en orden = insertarElemento
- eliminar elemento = eliminarElemento
- destruir vector = liberarMemoria

 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

#define COLUMNA 4
#define FILA 4
#define TODO_OK 1
#define ERR_MEMO 2

typedef struct{

    int *vec;
    int tam;

}Vector;

typedef struct{
    int **matriz;
    int fila;
    int columna;
    int dPrincipal;
    int dSecundaria;
    int dSuperior;
    int dInferior;
}Datos;

int inicializadorMatriz(Datos *mat);
void ingresarDatos(Datos *mat, Vector *vector);
bool _inicializadorVector(Vector *vector);
void mostrarMatriz(Datos *mat);
int modificarMatriz(Datos *mat, int nuevaColumna, int nuevaFila);
void buscarCambiar(Datos *mat, int elem);
void ordenarMatriz(Datos *mat);
void ordenarMatrizSeleccion(Datos *m);
void ordenarMatrizInsercion(Datos *mat);
void sumadorDiagonalP(Datos*mat);
void sumadorDiagonalS(Datos*mat);
void sumadorDiagonalSuperior(Datos*mat,int i);
void liberarMemoria(Datos*mat,Vector *vector);

int main()
{
    Datos mat;
    Vector vector;

    ingresarDatos(&mat,&vector);
    //printf("%lld",sizeof(mat.matriz));
    if(mat.fila==mat.columna){

        sumadorDiagonalP(&mat);
        sumadorDiagonalS(&mat);
    }
    modificarMatriz(&mat,6,6);
    ingresarDatos(&mat,&vector);
    mostrarMatriz(&mat);

    if(mat.fila==mat.columna){

        sumadorDiagonalP(&mat);
        sumadorDiagonalS(&mat);
    }
    liberarMemoria(&mat,&vector);
    return 0;
}
void ordenarMatrizInsercion(Datos *mat) {
    int totalElementos = mat->fila * mat->columna;

    for (int i = 1; i < totalElementos; i++) {
        int row = i / mat->columna;//calculan las coordenadas del elemento actual
        int col = i % mat->columna;
        int key = *(*(mat->matriz + row) + col);//almacena el valor del elemento actual.
        int j = i - 1;// es el índice del elemento anterior al actual.

        int prevRow = j / mat->columna;//calculan las coordenadas del elemento anterior.
        int prevCol = j % mat->columna;

        while (j >= 0 && *(*(mat->matriz + prevRow) + prevCol) > key) {//Compara el key con los elementos en la sublista ordenada (hacia atrás).
            *(*(mat->matriz + (j + 1) / mat->columna) + (j + 1) % mat->columna) = *(*(mat->matriz + prevRow) + prevCol);//Si un elemento en la sublista ordenada es mayor que key, desplaza ese elemento hacia adelante.
            j--;
            prevRow = j / mat->columna;//Actualiza prevRow y prevCol para reflejar las nuevas coordenadas del elemento anterior.
            prevCol = j % mat->columna;
        }
        *(*(mat->matriz + (j + 1) / mat->columna) + (j + 1) % mat->columna) = key;
    }
}

void ordenarMatrizSeleccion(Datos *m) {
    int totalElementos = m->fila * m->columna;

    for (int i = 0; i < totalElementos - 1; i++) {
        int minIndex = i;//Se asume inicialmente que el elemento más pequeño está en la posición i.
        int minRow = minIndex / m->columna;// son las coordenadas de la posición mínima encontrada.
        int minCol = minIndex % m->columna;

        for (int j = i + 1; j < totalElementos; j++) {
            int row = j / m->columna;//son las coordenadas de la posición actual en el bucle interno.
            int col = j % m->columna;

            if (*(*(m->matriz + row) + col) < *(*(m->matriz + minRow) + minCol)) {
                minIndex = j;//Compara el elemento actual con el mínimo y actualiza minIndex si se encuentra un elemento más pequeño.

                minRow = minIndex / m->columna;
                minCol = minIndex % m->columna;
            }
        }

        if (minIndex != i) {//Si se encuentra un nuevo mínimo, se intercambia con el elemento en la posición i.
            int row1 = i / m->columna;
            int col1 = i % m->columna;
            int temp = *(*(m->matriz + row1) + col1);
            *(*(m->matriz + row1) + col1) = *(*(m->matriz + minRow) + minCol);
            *(*(m->matriz + minRow) + minCol) = temp;
        }
    }
}
void ordenarMatriz(Datos *mat){
// SIN PUNTEROS
    int elemento=mat->matriz[0][0];
    int aux;
    for(int i=0;i<mat->fila;i++){
        for(int j=0; j<mat->columna;j++){

            if(elemento>mat->matriz[i][j]){
                aux=elemento;
                elemento=mat->matriz[i][j];
                mat->matriz[i][j]=aux;
            }
        }
    }
// CON PUNTEROS
    int totalElementos = mat->fila * mat->columna;

    for (int i = 0; i < totalElementos - 1; i++) {
        for (int j = 0; j < totalElementos - i - 1; j++) {
            int row1 = j / mat->columna;//si j=5 y columnas=4 => row1=1 porque es entero
            int col1 = j % mat->columna;//si j=5 y columnas=4 => col=1 porque es el resto
            int row2 = (j + 1) / mat->columna;
            int col2 = (j + 1) % mat->columna;

            if (*(*(mat->matriz + row1) + col1) > *(*(mat->matriz + row2) + col2)) {
                int temp = *(*(mat->matriz + row1) + col1);
                *(*(mat->matriz + row1) + col1) = *(*(mat->matriz + row2) + col2);
                *(*(mat->matriz + row2) + col2) = temp;
            }
        }
    }
}
void buscarCambiar(Datos *mat, int elem){
int encontrado = 0;
int nuevoElem;
char siOno;
    for (int i = 0; i < mat->fila; i++) {
        for (int j = 0; j < mat->columna; j++) {
            if (mat->matriz[i][j] == elem) {
                printf("Elemento %d encontrado en la posición (%d, %d)\n", elem, i+1, j+1);
                encontrado = 1;
                printf("\n ¿Desea cambiarlo?");
                do{
                    printf("\t Escriba S o N");
                    scanf("%c",&siOno);
                    siOno=toupper(siOno);
                    fflush(stdin);
                    if(siOno=='S'){
                        printf("\n Ingrese nuevo elemento");
                        scanf("%d",&nuevoElem);
                        mat->matriz[i][j]=nuevoElem;
                    }
                }while(siOno=='S' && siOno=='N');


            }
        }
    }
    if (!encontrado) {
        printf("Elemento %d no encontrado en la matriz.\n", elem);
    }
}
int modificarMatriz(Datos *mat, int nuevaColumna, int nuevaFila){
    //ptr = realloc (ptr,newsize);
    for(int i=0;i<mat->fila;i++){
        mat->matriz[i] = (int*)realloc(mat->matriz[i],nuevaColumna*sizeof(int));
        if(mat->matriz[i]==NULL){
            printf("Error al reasignar memoria a las columnas");
            return ERR_MEMO;
        }

    }
 // Si el número de filas ha cambiado, ajustar el tamaño del array de punteros a las filas
    if (nuevaFila != mat->fila) {
        mat->matriz = (int **)realloc(mat->matriz, nuevaFila * sizeof(int *));
        if (mat->matriz == NULL) {
            printf("Error al reasignar memoria para las filas\n");
            return ERR_MEMO;
        }

        // Inicializar las nuevas filas si estamos aumentando el número de filas
        for (int i = mat->fila; i < nuevaFila; i++) {
            mat->matriz[i] = (int *)malloc(nuevaColumna * sizeof(int));
            if (mat->matriz[i] == NULL) {
                printf("Error al asignar memoria para las nuevas filas\n");
                return ERR_MEMO;
            }
        }
    }
    mat->columna=nuevaColumna;
    mat->fila=nuevaFila;
    return TODO_OK;

}

int inicializadorMatriz(Datos *mat){

    mat->matriz = (int**)malloc(mat->fila*sizeof(int*));
    if(mat->matriz==NULL){
        return ERR_MEMO;
    }
    for(int i=0;i<mat->columna;i++){
        mat->matriz[i]=(int*)malloc(mat->columna*sizeof(int));
    }

return TODO_OK;
}
void ingresarDatos(Datos *mat,Vector *vector){

    char siOno;
    bool asignar=false;
    int *ptr;

    do{
            printf("\n ¿Quiere usar los datos predeterminados? S/N");
            scanf("%c",&siOno);
            siOno=toupper(siOno);
            fflush(stdin);

        }while(siOno != 'S' && siOno != 'N');

    if(siOno == 'S'){
        mat->columna=4;
        mat->fila=4;

        inicializadorMatriz(mat);

        int valores [4][4]={
        {
            1,2,3,4
        },
        {
            5,6,7,8
        },
        {
            9,10,11,12
        },
        {
            13,14,15,16
        },

        };

        for (int i=0;i<mat->columna;i++){
        for(int j=0; j<mat->fila;j++){
            mat->matriz[i][j]= valores[i][j];
            }
        }
    }
    if(siOno == 'N'){
        printf("Ingrese la cantidad de filas que tendra la matriz: ");
        scanf("%d", &mat->fila);
        printf("\nAhora ingrese la cantidad de COLUMNAS que tendra la matriz: ");
        scanf("%d",&mat->columna);

        fflush(stdin);
        inicializadorMatriz(mat);

        vector->tam = mat->fila * mat->columna ;
        //printf("Tamaño del vector: %d \n",vector->tam);
        //int valores[vector->tam];
        printf("\nIngrese datos en orden\n");
        asignar = _inicializadorVector(vector);
        if (asignar == true){
            for(int k=0;k<vector->tam;k++){
                 scanf("%d ",&vector->vec[k]);
                 //vector->vec[k]=valores[k]
            }

        }

       ptr = vector->vec; //puntero ptr a la primera posicion del vector
    for (int i = 0; i < mat->fila; i++) {
        for (int j = 0; j < mat->columna; j++) {
            *(*(mat->matriz + i) + j) = *(ptr++);
            //*(*(mat->matriz + 0) + 0) accede a mat->matriz[0][0]
            //*(ptr++) accede al primer elemento del vector y lo asigna a mat->matriz[0][0]
            //ptr se incrementa para apuntar al segundo elemento del vector.
        }
    }
    }
/**
  for(int i=0;i<mat->fila;i++){
            for(int j=0; j<mat->columna:j++){
                mat->matriz[i][j]=vector->vec[pos]
                pos++;
            }
    }
 */


    mostrarMatriz(mat);
}
bool _inicializadorVector(Vector *vector){

    vector->vec = (int*) malloc (vector->tam * sizeof(int));
    if(vector->vec == NULL){
        return false;
    }
    return true;
}
void mostrarMatriz(Datos *mat){
    int i;
    int j;

        for ( i=0; i<mat->fila; i++){
            for( j=0;j<mat->columna;j++){
                printf("%d\t",mat->matriz[i][j]);
            }
            printf("\n");
        }
    }
void liberarMemoria(Datos*mat, Vector *vector){

     if (vector->vec != NULL) {
        free(vector->vec);
        vector->vec = NULL;
    }

    for (int i=0;i<mat->fila; i++){

        free(mat->matriz[i]);
}
    free(mat->matriz);
    mat->matriz = NULL;  // Buen hábito para evitar punteros colgantes
}
void sumadorDiagonalP(Datos*mat){
    int sumatoria=0;
    mat->dSuperior=0;


    for(int i=0;i<COLUMNA;i++){
       mat->dPrincipal = mat->matriz[i][i];
        printf("\nDiagonal:%d, numero:%d",i,mat->dPrincipal);
       sumatoria+= mat->dPrincipal;
        sumadorDiagonalSuperior(mat,i);

    }

    printf("\n La sumatoria de la diagonal principal es: %d", sumatoria);

}
void sumadorDiagonalSuperior(Datos*mat, int pos){
    //printf("\n MATRIZ= %d",mat->dPrincipal);
    for(int i=0;i<FILA-(pos+1);i++){
        mat->dSuperior += mat->matriz[pos][pos+1+i];
        printf("\n MATRIZ SUPERIOR= %d",mat->dSuperior);
    }
    if(pos==COLUMNA-1){
        printf("\n La sumatoria de la diagonal Superior es: %d",mat->dSuperior);
    }
}

void sumadorDiagonalInferior(Datos*mat){
     mat->dInferior=0;
   for (int i = 1; i < COLUMNA; i++) {
        for (int j = 0; j < i; j++) {
            mat->dInferior += mat->matriz[i][j];
            printf("\n MATRIZ INFERIOR= %d",mat->dInferior);
        }
    }
  printf("\nLa sumatoria de los elementos debajo de la diagonal principal es: %d\n", mat->dInferior);
}

void sumadorDiagonalS(Datos*mat){
    int sumatoria2=0;
    for(int i=0;i<COLUMNA;i++){
       mat->dSecundaria = mat->matriz[i][COLUMNA-i-1];
        printf("\nDiagonal S:%d, numero:%d",i,mat->dSecundaria);
       sumatoria2+= mat->dSecundaria;
    }
    printf("\n La sumatoria de la diagonal secundaria es: %d", sumatoria2);
}
