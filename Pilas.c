#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
===================================================================
 1. DEFINICIÓN DE ESTRUCTURAS
===================================================================
*/

typedef struct {
    int folio;
    char nombreQueja[100];
    char departamento[100];
    char descripcion[256];
    char fecha[11]; // Formato dd/mm/aaaa
} Queja;

typedef struct Nodo {
    Queja datos;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// La "Pila" es la estructura que gestiona la LDE
typedef struct {
    Nodo* cima; // Apunta al "inicio" de la LDE (Top)
    Nodo* base; // Apunta al "fin" de la LDE (Bottom)
} Pila;

/*
===================================================================
 2. PROTOTIPOS DE FUNCIONES
===================================================================
*/

// Funciones de utilidad
void limpiarBuffer();
void pausarSistema();

// Funciones auxiliares de Queja
void capturarQueja(Queja* q);
void mostrarQueja(Queja q);

// Funciones de gestión de la Pila (LDE)
Pila* crearPila();
int estaVacia(Pila* pila);

// Funciones del Menú
void agregarQueja(Pila* pila);    // Opción 1: Push
void asignarQueja(Pila* pila);   // Opción 2: Pop
void revisarQuejas(Pila* pila);  // Opción 3: Print
void quejaSiguiente(Pila* pila); // Opción 4: Peek/Top
void salirYLiberar(Pila* pila); // Opción 5: Free

/*
===================================================================
 3. FUNCIÓN PRINCIPAL (main)
===================================================================
*/

int main() {
    Pila* cajaDeQuejas = crearPila();
    char opcion;

    do {
        printf("\n--- CAJA DE QUEJAS (Pila con LDE) ---\n");
        printf("1. Agregar una queja\n");
        printf("2. Asignar una queja (resolver)\n");
        printf("3. Revisar las quejas pendientes\n");
        printf("4. Ver queja siguiente (en la cima)\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");

        scanf(" %c", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case '1':
                agregarQueja(cajaDeQuejas);
                break;
            case '2':
                asignarQueja(cajaDeQuejas);
                break;
            case '3':
                revisarQuejas(cajaDeQuejas);
                break;
            case '4':
                quejaSiguiente(cajaDeQuejas);
                break;
            case '5':
                salirYLiberar(cajaDeQuejas);
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }

        if (opcion != '5') {
            pausarSistema();
        }

    } while (opcion != '5');

    return 0;
}

/*
===================================================================
 4. IMPLEMENTACIÓN DE FUNCIONES DE PILA (LDE)
===================================================================
*/

Pila* crearPila() {
    Pila* nuevaPila = (Pila*)malloc(sizeof(Pila));
    if (nuevaPila == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }
    nuevaPila->cima = NULL;
    nuevaPila->base = NULL;
    return nuevaPila;
}

int estaVacia(Pila* pila) {
    return (pila->cima == NULL);
}

/**
 * Opción 1: Agregar una queja (PUSH)
 * Implementado como "Insertar al Inicio" en la LDE.
 */
void agregarQueja(Pila* pila) {
    // 1. Crear el nodo
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para la queja.\n");
        return;
    }

    // 2. Capturar los datos
    printf("\n--- Nueva Queja ---\n");
    capturarQueja(&nuevoNodo->datos);

    // 3. Configurar punteros del nuevo nodo
    nuevoNodo->anterior = NULL;
    nuevoNodo->siguiente = pila->cima; // Apunta al que era el primero

    // 4. Conectar la LDE
    if (estaVacia(pila)) {
        // Si la pila estaba vacía, el nuevo nodo es Cima y Base
        pila->base = nuevoNodo;
    } else {
        // Si no, el antiguo nodo "cima" debe apuntar (anterior) al nuevo
        pila->cima->anterior = nuevoNodo;
    }

    // 5. Mover la Cima
    pila->cima = nuevoNodo;

    printf("\n[Exito] Queja con folio %d agregada a la cima de la caja.\n", nuevoNodo->datos.folio);
}

/**
 * Opción 2: Asignar una queja (POP)
 * Implementado como "Eliminar al Inicio" en la LDE.
 */
void asignarQueja(Pila* pila) {
    printf("\n--- Asignar Queja (Resolver) ---\n");
    if (estaVacia(pila)) {
        printf("La caja esta vacia. No hay quejas para asignar.\n");
        return;
    }

    // 1. Identificar el nodo a eliminar (la cima)
    Nodo* nodoAsignado = pila->cima;

    // 2. Mostrar la queja que se va a asignar
    printf("Asignando la siguiente queja al supervisor:\n");
    mostrarQueja(nodoAsignado->datos);

    // 3. Re-conectar la LDE
    if (pila->cima == pila->base) {
        // Era el único nodo
        pila->cima = NULL;
        pila->base = NULL;
    } else {
        // Hay más nodos
        pila->cima = nodoAsignado->siguiente; // Mover la cima al siguiente
        pila->cima->anterior = NULL;          // El nuevo nodo cima no tiene anterior
    }

    // 4. Liberar la memoria
    free(nodoAsignado);
    printf("\n[Exito] Queja asignada y eliminada de la pila.\n");
}

/**
 * Opción 3: Revisar las quejas (PRINT)
 * Implementado como un recorrido de la LDE (Cima -> Base).
 */
void revisarQuejas(Pila* pila) {
    printf("\n--- Quejas Pendientes en la Caja ---\n");
    if (estaVacia(pila)) {
        printf("La caja esta vacia.\n");
        return;
    }

    Nodo* actual = pila->cima;
    printf("(CIMA)\n");
    printf(" V\n");
    while (actual != NULL) {
        mostrarQueja(actual->datos);
        printf(" V\n");
        actual = actual->siguiente;
    }
    printf("(BASE)\n");
}

/**
 * Opción 4: Queja siguiente (PEEK / TOP)
 * Implementado como "Mostrar el Inicio" de la LDE.
 */
void quejaSiguiente(Pila* pila) {
    printf("\n--- Siguiente Queja por Asignar ---\n");
    if (estaVacia(pila)) {
        printf("La caja esta vacia.\n");
        return;
    }

    printf("La queja en la cima de la pila (la proxima a resolver) es:\n");
    mostrarQueja(pila->cima->datos);
}

/**
 * Opción 5: Salir (FREE)
 * Recorre y libera toda la LDE.
 */
void salirYLiberar(Pila* pila) {
    printf("\n--- Saliendo y Vaciando la Caja ---\n");
    if (estaVacia(pila)) {
        printf("La caja ya estaba vacia.\n");
    } else {
        Nodo* actual = pila->cima;
        while (actual != NULL) {
            Nodo* temporal = actual;
            actual = actual->siguiente;
            printf("Eliminando queja con folio %d...\n", temporal->datos.folio);
            free(temporal);
        }
    }

    // Liberar la estructura Pila
    free(pila);
    printf("Memoria liberada. Adios.\n");
}

/*
===================================================================
 5. IMPLEMENTACIÓN DE FUNCIONES AUXILIARES
===================================================================
*/

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausarSistema() {
    printf("\nPresione Enter para continuar...");
    limpiarBuffer();
}

void capturarQueja(Queja* q) {
    printf("Folio: ");
    scanf("%d", &q->folio);
    limpiarBuffer();

    printf("Nombre de quien realiza la queja: ");
    fgets(q->nombreQueja, 100, stdin);
    q->nombreQueja[strcspn(q->nombreQueja, "\n")] = 0; // Quitar newline

    printf("Departamento del que se queja: ");
    fgets(q->departamento, 100, stdin);
    q->departamento[strcspn(q->departamento, "\n")] = 0;

    printf("Descripcion de la queja: ");
    fgets(q->descripcion, 256, stdin);
    q->descripcion[strcspn(q->descripcion, "\n")] = 0;

    printf("Fecha (dd/mm/aaaa): ");
    fgets(q->fecha, 11, stdin);
    q->fecha[strcspn(q->fecha, "\n")] = 0;
    limpiarBuffer(); // Consumir newline si la fecha fue < 10 chars
}

void mostrarQueja(Queja q) {
    printf("------------------------------------\n");
    printf("  Folio:        %d\n", q.folio);
    printf("  Fecha:        %s\n", q.fecha);
    printf("  Reporta:      %s\n", q.nombreQueja);
    printf("  Departamento: %s\n", q.departamento);
    printf("  Descripcion:  %s\n", q.descripcion);
    printf("------------------------------------\n");
}
