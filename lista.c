#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // Para la configuración regional

// Estructura del nodo
typedef struct Nodo {
    int dato;
    struct Nodo *sgt;
} TNodo;

// Estructura de la lista
typedef struct LSE {
    TNodo *pInicio;
    TNodo *fin;
} TLSE;

// Prototipos de funciones
TLSE *crearLista();
void insertarInicio(int dato, TLSE *lista);
void insertarFinal(int dato, TLSE *lista);
void insertarAntes(int dato, TLSE *lista, int X);
void insertarDespues(int dato, TLSE *lista, int X);
void eliminarInicio(TLSE *lista);
void eliminarFinal(TLSE *lista);
void eliminarNodoX(TLSE *lista, int X);
void eliminar_Antes_X(TLSE *lista, int X);
void eliminar_Despues_X(TLSE *lista, int X);
void Imprimir(TLSE *lista);

int main() {
    setlocale(LC_ALL, ""); // Configuración regional para español
    TLSE *lista = crearLista(); // Crear lista vacía
    int opcion, subopcion;
    int dato, X;

    do {
        printf("\n=== Números decimales ===\n");
        printf("Menú de opciones:\n");
        printf("1 - Insertar\n");
        printf("2 - Eliminar\n");
        printf("3 - Mostrar lista\n");
        printf("4 - Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: // Submenú de inserción
                printf("\n-- Submenú de Inserción --\n");
                printf("1 - Insertar al inicio\n");
                printf("2 - Insertar al final\n");
                printf("3 - Insertar antes de un nodo X\n");
                printf("4 - Insertar después de un nodo X\n");
                printf("Seleccione una opción: ");
                scanf("%d", &subopcion);

                printf("Ingrese el número a insertar: ");
                scanf("%d", &dato);

                if(subopcion == 3 || subopcion == 4) {
                    printf("Ingrese el valor de referencia X: ");
                    scanf("%d", &X);
                }

                switch(subopcion) {
                    case 1: insertarInicio(dato, lista); break;
                    case 2: insertarFinal(dato, lista); break;
                    case 3: insertarAntes(dato, lista, X); break;
                    case 4: insertarDespues(dato, lista, X); break;
                    default: printf("Opción no válida.\n");
                }
                break;

            case 2: // Submenú de eliminación
                printf("\n-- Submenú de Eliminación --\n");
                printf("1 - Eliminar inicio\n");
                printf("2 - Eliminar final\n");
                printf("3 - Eliminar nodo X\n");
                printf("4 - Eliminar nodo antes de X\n");
                printf("5 - Eliminar nodo después de X\n");
                printf("Seleccione una opción: ");
                scanf("%d", &subopcion);

                if(subopcion == 3 || subopcion == 4 || subopcion == 5) {
                    printf("Ingrese el valor de referencia X: ");
                    scanf("%d", &X);
                }

                switch(subopcion) {
                    case 1: eliminarInicio(lista); break;
                    case 2: eliminarFinal(lista); break;
                    case 3: eliminarNodoX(lista, X); break;
                    case 4: eliminar_Antes_X(lista, X); break;
                    case 5: eliminar_Despues_X(lista, X); break;
                    default: printf("Opción no válida.\n");
                }
                break;

            case 3:
                printf("Contenido de la lista:\n");
                Imprimir(lista);
                break;

            case 4:
                printf("Saliendo...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while(opcion != 4);

    return 0;
}

// Crear lista vacía
TLSE *crearLista() {
    TLSE *l = (TLSE *)malloc(sizeof(TLSE));
    l->pInicio = NULL;
    l->fin = NULL;
    return l;
}

// Funciones de inserción
void insertarInicio(int dato, TLSE *lista) {
    TNodo *nodo = (TNodo *)malloc(sizeof(TNodo));
    nodo->dato = dato;
    nodo->sgt = lista->pInicio;
    lista->pInicio = nodo;
    if(lista->fin == NULL) lista->fin = nodo;
}

void insertarFinal(int dato, TLSE *lista) {
    TNodo *nodo = (TNodo *)malloc(sizeof(TNodo));
    nodo->dato = dato;
    nodo->sgt = NULL;
    if(lista->pInicio == NULL) {
        lista->pInicio = nodo;
        lista->fin = nodo;
    } else {
        lista->fin->sgt = nodo;
        lista->fin = nodo;
    }
}

void insertarAntes(int dato, TLSE *lista, int X) {
    TNodo *p = lista->pInicio, *ant = NULL;
    while(p != NULL && p->dato != X) {
        ant = p;
        p = p->sgt;
    }
    if(p == NULL) { printf("El nodo de referencia no se encontró.\n"); return; }
    TNodo *nodo = (TNodo *)malloc(sizeof(TNodo));
    nodo->dato = dato;
    nodo->sgt = p;
    if(ant == NULL) lista->pInicio = nodo;
    else ant->sgt = nodo;
}

void insertarDespues(int dato, TLSE *lista, int X) {
    TNodo *p = lista->pInicio;
    while(p != NULL && p->dato != X) p = p->sgt;
    if(p == NULL) { printf("El nodo de referencia no se encontró.\n"); return; }
    TNodo *nodo = (TNodo *)malloc(sizeof(TNodo));
    nodo->dato = dato;
    nodo->sgt = p->sgt;
    p->sgt = nodo;
}

// Funciones de eliminación
void eliminarInicio(TLSE *lista) {
    if(lista->pInicio == NULL) { printf("Lista vacía\n"); return; }
    TNodo *p = lista->pInicio;
    lista->pInicio = p->sgt;
    if(lista->fin == p) lista->fin = NULL;
    free(p);
}

void eliminarFinal(TLSE *lista) {
    if(lista->pInicio == NULL) { printf("Lista vacía\n"); return; }
    TNodo *p = lista->pInicio, *ant = NULL;
    while(p->sgt != NULL) { ant = p; p = p->sgt; }
    if(ant == NULL) lista->pInicio = lista->fin = NULL;
    else { ant->sgt = NULL; lista->fin = ant; }
    free(p);
}

void eliminarNodoX(TLSE *lista, int X) {
    TNodo *p = lista->pInicio, *ant = NULL;
    while(p != NULL && p->dato != X) { ant = p; p = p->sgt; }
    if(p == NULL) { printf("Nodo no encontrado.\n"); return; }
    if(ant == NULL) lista->pInicio = p->sgt;
    else ant->sgt = p->sgt;
    if(lista->fin == p) lista->fin = ant;
    free(p);
}

void eliminar_Antes_X(TLSE *lista, int X) {
    if(lista->pInicio == NULL || lista->pInicio->dato == X) {
        printf("No existe nodo que preceda a %d\n", X); return;
    }
    TNodo *p = lista->pInicio, *ant = NULL, *q = NULL;
    while(p != NULL && p->dato != X) { q = ant; ant = p; p = p->sgt; }
    if(p == NULL) { printf("Nodo de referencia no encontrado\n"); return; }
    if(q == NULL) lista->pInicio = p;
    else q->sgt = p;
    free(ant);
}

void eliminar_Despues_X(TLSE *lista, int X) {
    TNodo *p = lista->pInicio;
    while(p != NULL && p->dato != X) p = p->sgt;
    if(p == NULL) { printf("Nodo de referencia no encontrado\n"); return; }
    if(p->sgt == NULL) { printf("No hay nodo posterior a %d\n", X); return; }
    TNodo *q = p->sgt;
    p->sgt = q->sgt;
    if(lista->fin == q) lista->fin = p;
    free(q);
}

// Función para imprimir lista
void Imprimir(TLSE *lista) {
    TNodo *p = lista->pInicio;
    if(p == NULL) { printf("La lista está vacía.\n"); return; }
    while(p != NULL) {
        printf("%d -> ", p->dato);
        p = p->sgt;
    }
    printf("NULL\n");
}
