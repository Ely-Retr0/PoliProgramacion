#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para strcmp() y strcspn()

/*
===================================================================
 1. CONSTANTES Y DEFINICIÓN DE ESTRUCTURAS
 (Lo que estaría en empleado.h)
===================================================================
*/

// Constantes para los criterios de ordenamiento
#define CRITERIO_ID 1
#define CRITERIO_NOMBRE 2
#define CRITERIO_DEPARTAMENTO 3

typedef struct {
    char calle[100];
    int numero;
    char colonia[100];
    char cp[6];
    char ciudad[100];
} Domicilio;

typedef struct {
    int numEmpleado; // Llave primaria
    char nombreApellido[100];
    char departamento[50];
    Domicilio domicilio;
    char telefono[15];
    double salarioMensual;
} Empleado;

typedef struct Nodo {
    Empleado datos;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* inicio;
    Nodo* fin;
} Lista;


/*
===================================================================
 2. PROTOTIPOS DE FUNCIONES
 (Lo que estaría en empleado.h, lista.h, ordenamiento.h)
===================================================================
*/

// --- Funciones de Utilidad y Empleado ---
void limpiarBuffer();
void capturarDomicilio(Domicilio* dom);
void capturarEmpleado(Empleado* emp);
void mostrarEmpleado(Empleado emp);

// --- Funciones de Lista ---
Lista* crearLista();
int estaVacia(Lista* lista);
void insertarOrdenado(Lista* lista, Empleado emp);
void eliminarPorID(Lista* lista, int id);
Nodo* buscarPorID(Lista* lista, int id);
void modificarRegistro(Lista* lista);
void imprimirPorDepto(Lista* lista, const char* depto);
void imprimirTodaLaLista(Lista* lista);
void liberarLista(Lista* lista);

// --- Funciones de Ordenamiento ---
void swapDatos(Nodo *a, Nodo *b);
int comparar(Empleado a, Empleado b, int criterio);
void bubbleSortLista(Lista* lista, int criterio);
void shakerSortLista(Lista* lista);

// --- Funciones de Main (Menús) ---
void mostrarMenu();
void menuImprimir(Lista* lista);

/*
===================================================================
 3. IMPLEMENTACIÓN: MAIN Y MENÚS
 (Lo que estaría en main.c)
===================================================================
*/
int main() {
    Lista* miLista = crearLista();
    char opcion; // Usamos char para leer a, b, c, 0
    int id;
    char depto[50];
    Empleado emp;

    do {
        mostrarMenu();
        scanf(" %c", &opcion); // Espacio antes de %c para consumir newlines
        limpiarBuffer();

        switch (opcion) {
            case 'a': // a) Altas
                capturarEmpleado(&emp);
                insertarOrdenado(miLista, emp);
                break;
            case 'b': // b) Bajas
                printf("Ingrese el ID del empleado a eliminar: ");
                scanf("%d", &id); limpiarBuffer();
                eliminarPorID(miLista, id);
                break;
            case 'c': // c) Mostrar por departamento
                printf("Ingrese el nombre del departamento: ");
                fgets(depto, 50, stdin); depto[strcspn(depto, "\n")] = 0;
                imprimirPorDepto(miLista, depto);
                break;
            case 'd': // d) Modificar
                modificarRegistro(miLista);
                break;
            case 'e': // e) Imprimir (con ordenamiento)
                menuImprimir(miLista);
                break;
            case 'f': // Opción extra para ver la lista (ordenada por ID)
                printf("\n--- Lista Actual (Ordenada por ID) ---\n");
                imprimirTodaLaLista(miLista);
                break;
            case '0':
                printf("Saliendo... liberando memoria.\n");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                break;
        }

    } while (opcion != '0');

    liberarLista(miLista);
    return 0;
}

void mostrarMenu() {
    printf("\n--- SISTEMA DE GESTION DE EMPLEADOS (Lista Doble) ---\n");
    printf("a) Altas (Insertar empleado ordenado por ID)\n");
    printf("b) Bajas (Eliminar empleado por ID)\n");
    printf("c) Mostrar por departamento\n");
    printf("d) Modificar un Registro\n");
    printf("e) Imprimir (con opciones de ordenamiento)\n");
    printf("f) Imprimir Lista (Actual, ordenada por ID)\n");
    printf("0) Salir\n");
    printf("Seleccione una opcion: ");
}

void menuImprimir(Lista* lista) {
    int opcion;
    printf("\n--- Menu de Impresion ---\n");
    printf("1. Ordenado por Numero de empleado (Burbuja)\n");
    printf("2. Ordenado por Nombre (Shaker Sort)\n");
    printf("3. Ordenado por Departamento (Burbuja)\n");
    printf("0. Cancelar\n");
    printf("Opcion: ");
    scanf("%d", &opcion); limpiarBuffer();

    if (estaVacia(lista)) {
        printf("La lista esta vacia. Nada que imprimir.\n");
        return;
    }

    switch (opcion) {
        case 1:
            printf("Ordenando por ID (Burbuja)...\n");
            bubbleSortLista(lista, CRITERIO_ID);
            imprimirTodaLaLista(lista);
            break;
        case 2:
            printf("Ordenando por Nombre (Shaker)...\n");
            shakerSortLista(lista);
            imprimirTodaLaLista(lista);
            break;
        case 3:
            printf("Ordenando por Departamento (Burbuja)...\n");
            bubbleSortLista(lista, CRITERIO_DEPARTAMENTO);
            imprimirTodaLaLista(lista);
            break;
        case 0:
            return;
        default:
            printf("Opcion no valida.\n");
            break;
    }

    // Restaurar el orden principal (por ID)
    bubbleSortLista(lista, CRITERIO_ID);
    printf("\n(La lista ha sido restaurada a su orden por ID)\n");
}


/*
===================================================================
 4. IMPLEMENTACIÓN: EMPLEADO Y UTILIDADES
 (Lo que estaría en empleado.c)
===================================================================
*/

// Helper para limpiar el buffer de entrada (stdin)
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void capturarDomicilio(Domicilio* dom) {
    printf("  Calle: ");
    fgets(dom->calle, 100, stdin); dom->calle[strcspn(dom->calle, "\n")] = 0;
    printf("  Numero: ");
    scanf("%d", &dom->numero); limpiarBuffer();
    printf("  Colonia: ");
    fgets(dom->colonia, 100, stdin); dom->colonia[strcspn(dom->colonia, "\n")] = 0;
    printf("  Codigo Postal: ");
    fgets(dom->cp, 6, stdin); dom->cp[strcspn(dom->cp, "\n")] = 0; limpiarBuffer();
    printf("  Ciudad: ");
    fgets(dom->ciudad, 100, stdin); dom->ciudad[strcspn(dom->ciudad, "\n")] = 0;
}

void capturarEmpleado(Empleado* emp) {
    printf("--- Capturando Empleado ---\n");
    printf("Numero de empleado: ");
    scanf("%d", &emp->numEmpleado); limpiarBuffer();
    printf("Nombre y Apellido: ");
    fgets(emp->nombreApellido, 100, stdin); emp->nombreApellido[strcspn(emp->nombreApellido, "\n")] = 0;
    printf("Departamento: ");
    fgets(emp->departamento, 50, stdin); emp->departamento[strcspn(emp->departamento, "\n")] = 0;

    printf("--- Domicilio ---\n");
    capturarDomicilio(&emp->domicilio);

    printf("Telefono: ");
    fgets(emp->telefono, 15, stdin); emp->telefono[strcspn(emp->telefono, "\n")] = 0;
    printf("Salario Mensual: ");
    scanf("%lf", &emp->salarioMensual); limpiarBuffer();
    printf("-----------------------------\n");
}

void mostrarEmpleado(Empleado emp) {
    printf("-----------------------------\n");
    printf("ID: %d\n", emp.numEmpleado);
    printf("Nombre: %s\n", emp.nombreApellido);
    printf("Depto: %s\n", emp.departamento);
    printf("Salario: $%.2f\n", emp.salarioMensual);
    printf("Tel: %s\n", emp.telefono);
    printf("Domicilio: %s %d, %s, C.P. %s, %s\n",
           emp.domicilio.calle, emp.domicilio.numero, emp.domicilio.colonia,
           emp.domicilio.cp, emp.domicilio.ciudad);
    printf("-----------------------------\n");
}

/*
===================================================================
 5. IMPLEMENTACIÓN: LISTA
 (Lo que estaría en lista.c)
===================================================================
*/

Lista* crearLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    if (lista == NULL) {
        printf("Error: No se pudo asignar memoria para la lista.\n");
        exit(1);
    }
    lista->inicio = NULL;
    lista->fin = NULL;
    return lista;
}

int estaVacia(Lista* lista) {
    return lista->inicio == NULL;
}

// a) Altas: Insertar ordenado por numEmpleado
void insertarOrdenado(Lista* lista, Empleado emp) {
    // Validar duplicados
    if (buscarPorID(lista, emp.numEmpleado) != NULL) {
        printf("Error: Ya existe un empleado con el ID %d.\n", emp.numEmpleado);
        return;
    }

    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->datos = emp;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;

    // Caso 1: Lista vacía
    if (estaVacia(lista)) {
        lista->inicio = nuevoNodo;
        lista->fin = nuevoNodo;
        printf("Empleado (ID %d) agregado (lista vacia).\n", emp.numEmpleado);
        return;
    }

    // Caso 2: Insertar al inicio
    if (emp.numEmpleado < lista->inicio->datos.numEmpleado) {
        nuevoNodo->siguiente = lista->inicio;
        lista->inicio->anterior = nuevoNodo;
        lista->inicio = nuevoNodo;
        printf("Empleado (ID %d) agregado (al inicio).\n", emp.numEmpleado);
        return;
    }

    // Caso 3: Insertar en medio o al final
    Nodo* actual = lista->inicio;
    while (actual != NULL && actual->datos.numEmpleado < emp.numEmpleado) {
        actual = actual->siguiente;
    }

    if (actual == NULL) { // Insertar al final
        lista->fin->siguiente = nuevoNodo;
        nuevoNodo->anterior = lista->fin;
        lista->fin = nuevoNodo;
        printf("Empleado (ID %d) agregado (al final).\n", emp.numEmpleado);
    } else { // Insertar en medio (antes de 'actual')
        nuevoNodo->siguiente = actual;
        nuevoNodo->anterior = actual->anterior;
        actual->anterior->siguiente = nuevoNodo;
        actual->anterior = nuevoNodo;
        printf("Empleado (ID %d) agregado (en medio).\n", emp.numEmpleado);
    }
}

// b) Bajas: Eliminar por ID
void eliminarPorID(Lista* lista, int id) {
    if (estaVacia(lista)) {
        printf("La lista esta vacia.\n");
        return;
    }

    Nodo* nodoAEliminar = buscarPorID(lista, id);
    if (nodoAEliminar == NULL) {
        printf("Empleado con ID %d no encontrado.\n", id);
        return;
    }

    // Caso 1: Es el único nodo
    if (nodoAEliminar == lista->inicio && nodoAEliminar == lista->fin) {
        lista->inicio = NULL;
        lista->fin = NULL;
    }
    // Caso 2: Es el nodo de inicio
    else if (nodoAEliminar == lista->inicio) {
        lista->inicio = nodoAEliminar->siguiente;
        lista->inicio->anterior = NULL;
    }
    // Caso 3: Es el nodo final
    else if (nodoAEliminar == lista->fin) {
        lista->fin = nodoAEliminar->anterior;
        lista->fin->siguiente = NULL;
    }
    // Caso 4: Es un nodo intermedio
    else {
        nodoAEliminar->anterior->siguiente = nodoAEliminar->siguiente;
        nodoAEliminar->siguiente->anterior = nodoAEliminar->anterior;
    }

    free(nodoAEliminar);
    printf("Empleado con ID %d eliminado exitosamente.\n", id);
}

Nodo* buscarPorID(Lista* lista, int id) {
    Nodo* actual = lista->inicio;
    while (actual != NULL) {
        if (actual->datos.numEmpleado == id) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return NULL; // No encontrado
}

// c) Mostrar por departamento
void imprimirPorDepto(Lista* lista, const char* depto) {
    Nodo* actual = lista->inicio;
    int encontrados = 0;
    printf("--- Empleados del Departamento: %s ---\n", depto);
    while (actual != NULL) {
        // Usamos strcmp para comparar cadenas
        if (strcmp(actual->datos.departamento, depto) == 0) {
            printf("  ID: %d, Nombre: %s, Salario: $%.2f\n",
                   actual->datos.numEmpleado,
                   actual->datos.nombreApellido,
                   actual->datos.salarioMensual);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    if (encontrados == 0) {
        printf("No se encontraron empleados en ese departamento.\n");
    }
    printf("-----------------------------------------\n");
}

// d) Modificar un Registro
void modificarRegistro(Lista* lista) {
    int id;
    printf("Ingrese el ID del empleado a modificar: ");
    scanf("%d", &id); limpiarBuffer();

    Nodo* nodo = buscarPorID(lista, id);
    if (nodo == NULL) {
        printf("Empleado con ID %d no encontrado.\n", id);
        return;
    }

    printf("Datos actuales del empleado:\n");
    mostrarEmpleado(nodo->datos);

    int opcion;
    printf("Que campo desea modificar?\n");
    printf("1. Nombre y Apellido\n");
    printf("2. Departamento\n");
    printf("3. Domicilio\n");
    printf("4. Telefono\n");
    printf("5. Salario Mensual\n");
    printf("0. Cancelar\n");
    printf("Opcion: ");
    scanf("%d", &opcion); limpiarBuffer();

    switch (opcion) {
        case 1:
            printf("Nuevo Nombre y Apellido: ");
            fgets(nodo->datos.nombreApellido, 100, stdin); nodo->datos.nombreApellido[strcspn(nodo->datos.nombreApellido, "\n")] = 0;
            break;
        case 2:
            printf("Nuevo Departamento: ");
            fgets(nodo->datos.departamento, 50, stdin); nodo->datos.departamento[strcspn(nodo->datos.departamento, "\n")] = 0;
            break;
        case 3:
            printf("Nuevo Domicilio:\n");
            capturarDomicilio(&nodo->datos.domicilio);
            break;
        case 4:
            printf("Nuevo Telefono: ");
            fgets(nodo->datos.telefono, 15, stdin); nodo->datos.telefono[strcspn(nodo->datos.telefono, "\n")] = 0;
            break;
        case 5:
            printf("Nuevo Salario Mensual: ");
            scanf("%lf", &nodo->datos.salarioMensual); limpiarBuffer();
            break;
        case 0:
            printf("Modificacion cancelada.\n");
            return;
        default:
            printf("Opcion no valida.\n");
            return;
    }
    printf("Registro actualizado.\n");
}

// Función auxiliar para e) Imprimir
void imprimirTodaLaLista(Lista* lista) {
    if (estaVacia(lista)) {
        printf("La lista esta vacia.\n");
        return;
    }
    Nodo* actual = lista->inicio;
    while (actual != NULL) {
        mostrarEmpleado(actual->datos);
        actual = actual->siguiente;
    }
}

void liberarLista(Lista* lista) {
    Nodo* actual = lista->inicio;
    while (actual != NULL) {
        Nodo* temporal = actual;
        actual = actual->siguiente;
        free(temporal);
    }
    free(lista);
}

/*
===================================================================
 6. IMPLEMENTACIÓN: ORDENAMIENTO
 (Lo que estaría en ordenamiento.c)
===================================================================
*/

// Función auxiliar para intercambiar los *datos* de dos nodos
void swapDatos(Nodo *a, Nodo *b) {
    Empleado temp = a->datos;
    a->datos = b->datos;
    b->datos = temp;
}

// Función auxiliar para comparar empleados según un criterio
int comparar(Empleado a, Empleado b, int criterio) {
    switch (criterio) {
        case CRITERIO_ID:
            if (a.numEmpleado > b.numEmpleado) return 1;
            if (a.numEmpleado < b.numEmpleado) return -1;
            return 0;
        case CRITERIO_NOMBRE:
            return strcmp(a.nombreApellido, b.nombreApellido);
        case CRITERIO_DEPARTAMENTO:
            return strcmp(a.departamento, b.departamento);
    }
    return 0;
}

// e) Imprimir: Implementación de Bubble Sort (Burbuja)
void bubbleSortLista(Lista* lista, int criterio) {
    if (estaVacia(lista) || lista->inicio->siguiente == NULL) return;

    int intercambiado;
    Nodo *finDelSort = NULL;

    do {
        intercambiado = 0;
        Nodo *actual = lista->inicio;

        while (actual->siguiente != finDelSort) {
            if (comparar(actual->datos, actual->siguiente->datos, criterio) > 0) {
                swapDatos(actual, actual->siguiente);
                intercambiado = 1;
            }
            actual = actual->siguiente;
        }
        finDelSort = actual;

    } while (intercambiado);
}

// e) Imprimir: Implementación de Shaker Sort (Bidireccional)
void shakerSortLista(Lista* lista) {
    if (estaVacia(lista) || lista->inicio->siguiente == NULL) return;

    int intercambiado = 1;
    Nodo* inicioRango = lista->inicio;
    Nodo* finRango = NULL;

    while (intercambiado) {
        intercambiado = 0;
        Nodo* actual = inicioRango;

        // Pasada hacia el final (Bubble)
        while (actual->siguiente != finRango) {
            if (strcmp(actual->datos.nombreApellido, actual->siguiente->datos.nombreApellido) > 0) {
                swapDatos(actual, actual->siguiente);
                intercambiado = 1;
            }
            actual = actual->siguiente;
        }
        if (!intercambiado) break;
        finRango = actual;

        intercambiado = 0;
        actual = finRango->anterior;

        // Pasada hacia el inicio (Sink)
        // Cuidado con los punteros nulos en listas doblemente enlazadas
        while (actual != NULL && actual != inicioRango->anterior) {
             if (strcmp(actual->datos.nombreApellido, actual->siguiente->datos.nombreApellido) > 0) {
                swapDatos(actual, actual->siguiente);
                intercambiado = 1;
            }
            if(actual->anterior == NULL) break;
            actual = actual->anterior;
        }
        inicioRango = (actual == NULL) ? lista->inicio : actual->siguiente;
    }
}
