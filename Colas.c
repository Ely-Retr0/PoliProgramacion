#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
===================================================================
 1. DEFINICIÓN DE ESTRUCTURAS
===================================================================
*/

// Usamos un enum para manejar de forma segura los tipos de servicio
typedef enum {
    SENCILLO,
    ASPIRADO,
    PREMIUM
} TipoServicio;

typedef struct {
    char placas[10];
    char color[30];
    char marca[50];
    char modelo[50];
    TipoServicio servicio;
} Auto;

typedef struct Nodo {
    Auto datos;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

// La "Cola" es la estructura que gestiona la LDE
typedef struct {
    Nodo* frente; // Apunta al "inicio" de la LDE (para Dequeue)
    Nodo* fin;    // Apunta al "fin" de la LDE (para Enqueue)
} Cola;

/*
===================================================================
 2. PROTOTIPOS DE FUNCIONES
===================================================================
*/

// Funciones de utilidad
void limpiarBuffer();
void pausarSistema();
const char* servicioAString(TipoServicio s); // Helper para imprimir

// Funciones auxiliares de Auto
void capturarAuto(Auto* a);
void mostrarAuto(Auto a);

// Funciones de gestión de la Cola (LDE)
Cola* crearCola();
int estaVacia(Cola* cola);

// Funciones del Menú
void agregarServicio(Cola* cola);    // Opción 1: Enqueue
void asignarServicio(Cola* cola);   // Opción 2: Dequeue
void mostrarListaDeEspera(Cola* cola); // Opción 3: Print
void verSiguiente(Cola* cola);       // Opción 4: Peek/Front
void salirYLiberar(Cola* cola);     // Opción 5: Free

/*
===================================================================
 3. FUNCIÓN PRINCIPAL (main)
===================================================================
*/

int main() {
    Cola* filaLavado = crearCola();
    char opcion;

    do {
        printf("\n--- LAVADO DE AUTOS (Cola con LDE) ---\n");
        printf("1. Agregar servicio (auto)\n");
        printf("2. Asignacion del servicio (lavar)\n");
        printf("3. Mostrar lista de espera\n");
        printf("4. Ver siguiente auto\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");

        scanf(" %c", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case '1':
                agregarServicio(filaLavado);
                break;
            case '2':
                asignarServicio(filaLavado);
                break;
            case '3':
                mostrarListaDeEspera(filaLavado);
                break;
            case '4':
                verSiguiente(filaLavado);
                break;
            case '5':
                salirYLiberar(filaLavado);
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
 4. IMPLEMENTACIÓN DE FUNCIONES DE COLA (LDE)
===================================================================
*/

Cola* crearCola() {
    Cola* nuevaCola = (Cola*)malloc(sizeof(Cola));
    if (nuevaCola == NULL) {
        printf("Error de memoria.\n");
        exit(1);
    }
    nuevaCola->frente = NULL;
    nuevaCola->fin = NULL;
    return nuevaCola;
}

int estaVacia(Cola* cola) {
    return (cola->frente == NULL);
}

/**
 * Opción 1: Agregar servicio (ENQUEUE)
 * Implementado como "Insertar al Final" en la LDE.
 */
void agregarServicio(Cola* cola) {
    // 1. Crear el nodo
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) {
        printf("Error: No se pudo asignar memoria para el auto.\n");
        return;
    }

    // 2. Capturar los datos
    printf("\n--- Nuevo Auto ---\n");
    capturarAuto(&nuevoNodo->datos);

    // 3. Configurar punteros del nuevo nodo
    nuevoNodo->siguiente = NULL; // Siempre es el último
    nuevoNodo->anterior = cola->fin; // Se conecta al que era el último

    // 4. Conectar la LDE
    if (estaVacia(cola)) {
        // Si la cola estaba vacía, el nuevo nodo es Frente y Fin
        cola->frente = nuevoNodo;
    } else {
        // Si no, el antiguo nodo "fin" debe apuntar (siguiente) al nuevo
        cola->fin->siguiente = nuevoNodo;
    }

    // 5. Mover el puntero Fin
    cola->fin = nuevoNodo;

    printf("\n[Exito] Auto con placas %s agregado a la fila.\n", nuevoNodo->datos.placas);
}

/**
 * Opción 2: Asignación del servicio (DEQUEUE)
 * Implementado como "Eliminar al Inicio" en la LDE.
 */
void asignarServicio(Cola* cola) {
    printf("\n--- Asignar Auto para Lavado ---\n");
    if (estaVacia(cola)) {
        printf("La fila esta vacia. No hay autos para lavar.\n");
        return;
    }

    // 1. Identificar el nodo a eliminar (el frente)
    Nodo* nodoAsignado = cola->frente;

    // 2. Mostrar el auto que se va a asignar
    printf("Asignando el siguiente auto al empleado:\n");
    mostrarAuto(nodoAsignado->datos);

    // 3. Re-conectar la LDE
    if (cola->frente == cola->fin) {
        // Era el único nodo en la cola
        cola->frente = NULL;
        cola->fin = NULL;
    } else {
        // Hay más nodos
        cola->frente = nodoAsignado->siguiente; // Mover el frente al siguiente
        cola->frente->anterior = NULL;          // El nuevo frente no tiene anterior
    }

    // 4. Liberar la memoria
    free(nodoAsignado);
    printf("\n[Exito] Auto enviado al area de servicio y eliminado de la fila.\n");
}

/**
 * Opción 3: Mostrar lista de espera (PRINT)
 * Implementado como un recorrido de la LDE (Frente -> Fin).
 */
void mostrarListaDeEspera(Cola* cola) {
    printf("\n--- Autos en la Lista de Espera ---\n");
    if (estaVacia(cola)) {
        printf("La fila esta vacia.\n");
        return;
    }

    Nodo* actual = cola->frente;
    printf("(FRENTE DE LA FILA)\n");
    printf(" V\n");
    while (actual != NULL) {
        mostrarAuto(actual->datos);
        if(actual->siguiente != NULL) {
            printf(" V\n"); // Flecha hacia el siguiente
        }
        actual = actual->siguiente;
    }
    printf("(FIN DE LA FILA)\n");
}

/**
 * Opción 4: Ver siguiente (PEEK / FRONT)
 * Implementado como "Mostrar el Inicio" de la LDE.
 */
void verSiguiente(Cola* cola) {
    printf("\n--- Proximo Auto por Atender ---\n");
    if (estaVacia(cola)) {
        printf("La fila esta vacia.\n");
        return;
    }

    printf("El auto proximo a pasar al area de servicio es:\n");
    mostrarAuto(cola->frente->datos);
}

/**
 * Opción 5: Salir (FREE)
 * Recorre y libera toda la LDE.
 */
void salirYLiberar(Cola* cola) {
    printf("\n--- Saliendo y Vaciando la Fila ---\n");
    if (estaVacia(cola)) {
        printf("La fila ya estaba vacia.\n");
    } else {
        Nodo* actual = cola->frente;
        while (actual != NULL) {
            Nodo* temporal = actual;
            actual = actual->siguiente;
            printf("Eliminando auto [Placas: %s] de la lista...\n", temporal->datos.placas);
            free(temporal);
        }
    }

    // Liberar la estructura Cola
    free(cola);
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

// Helper para convertir el Enum TipoServicio a un string legible
const char* servicioAString(TipoServicio s) {
    switch (s) {
        case SENCILLO: return "Lavado Sencillo";
        case ASPIRADO: return "Lavado con Aspirado";
        case PREMIUM:  return "Lavado Premium";
        default:       return "Desconocido";
    }
}

void capturarAuto(Auto* a) {
    printf("Placas: ");
    fgets(a->placas, 10, stdin);
    a->placas[strcspn(a->placas, "\n")] = 0;
    limpiarBuffer();

    printf("Marca: ");
    fgets(a->marca, 50, stdin);
    a->marca[strcspn(a->marca, "\n")] = 0;

    printf("Modelo: ");
    fgets(a->modelo, 50, stdin);
    a->modelo[strcspn(a->modelo, "\n")] = 0;

    printf("Color: ");
    fgets(a->color, 30, stdin);
    a->color[strcspn(a->color, "\n")] = 0;

    int tipo;
    do {
        printf("Tipo de Servicio (1=Sencillo, 2=Aspirado, 3=Premium): ");
        scanf("%d", &tipo);
        limpiarBuffer();
        if(tipo < 1 || tipo > 3) {
            printf("Opcion invalida. Intente de nuevo.\n");
        }
    } while (tipo < 1 || tipo > 3);

    // Asignar el enum basado en la entrada (1-based a 0-based)
    a->servicio = (TipoServicio)(tipo - 1);
}

void mostrarAuto(Auto a) {
    printf("------------------------------------\n");
    printf("  Placas:   %s\n", a.placas);
    printf("  Vehiculo: %s %s, Color %s\n", a.marca, a.modelo, a.color);
    printf("  Servicio: %s\n", servicioAString(a.servicio));
    printf("------------------------------------\n");
}
