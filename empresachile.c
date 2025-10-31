#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// ==================== CONSTANTES ====================
#define CRITERIO_ID 1
#define CRITERIO_NOMBRE 2
#define CRITERIO_DEPARTAMENTO 3

// ==================== ESTRUCTURAS ====================
typedef struct {
    char calle[100];
    char numero[10];
    char colonia[100];
    char codigoPostal[10];
    char ciudad[100];
} Domicilio;

typedef struct {
    int numEmpleado;
    char nombreApellido[100];
    char departamento[50];
    Domicilio domicilio;
    char telefono[20];
    float salarioMensual;
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

// ==================== PROTOTIPOS ====================
void limpiarBuffer();
void capturarDomicilio(Domicilio* dom);
void capturarEmpleado(Empleado* emp);
void mostrarEmpleado(Empleado emp);
Lista* crearLista();
int estaVacia(Lista* lista);
Nodo* buscarPorID(Lista* lista, int id);
void insertarOrdenado(Lista* lista, Empleado emp);
void eliminarPorID(Lista* lista, int id);
void imprimirPorDepto(Lista* lista, const char* depto);
void modificarRegistro(Lista* lista);
void imprimirTodaLaLista(Lista* lista);
void liberarLista(Lista* lista);
void swapDatos(Nodo *a, Nodo *b);
int comparar(Empleado a, Empleado b, int criterio);
void bubbleSortLista(Lista* lista, int criterio);
void shakerSortLista(Lista* lista);
void mostrarMenu();
void menuImprimir(Lista* lista);

// ==================== MAIN ====================
int main() {
    setlocale(LC_ALL, "");
    Lista* empleados = crearLista();
    char opcion;
    int id;
    char depto[50];
    Empleado emp;

    do {
        mostrarMenu();
        scanf(" %c", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 'a': // Altas
                capturarEmpleado(&emp);
                insertarOrdenado(empleados, emp);
                break;
            case 'b': // Bajas
                printf("Ingrese el número de empleado a eliminar: ");
                scanf("%d", &id);
                limpiarBuffer();
                eliminarPorID(empleados, id);
                break;
            case 'c': // Mostrar por departamento
                printf("Ingrese el nombre del departamento: ");
                fgets(depto, 50, stdin);
                depto[strcspn(depto, "\n")] = '\0';
                imprimirPorDepto(empleados, depto);
                break;
            case 'd': // Modificar
                modificarRegistro(empleados);
                break;
            case 'e': // Imprimir (ordenamientos)
                menuImprimir(empleados);
                break;
            case 'f': // Mostrar lista actual
                printf("\n--- Lista actual de empleados ---\n");
                imprimirTodaLaLista(empleados);
                break;
            case '0':
                printf("Saliendo... liberando memoria.\n");
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != '0');

    liberarLista(empleados);
    return 0;
}

// ==================== FUNCIONES GENERALES ====================
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarMenu() {
    printf("\n=== SISTEMA DE GESTIÓN DE EMPLEADOS ===\n");
    printf("a) Altas (Insertar empleado)\n");
    printf("b) Bajas (Eliminar empleado por número)\n");
    printf("c) Mostrar por departamento\n");
    printf("d) Modificar un registro\n");
    printf("e) Imprimir (con opciones de ordenamiento)\n");
    printf("f) Mostrar lista actual (ordenada por número)\n");
    printf("0) Salir\n");
    printf("Seleccione una opción: ");
}

// ==================== CAPTURA Y MUESTRA ====================
void capturarDomicilio(Domicilio* dom) {
    printf("  Calle: ");
    fgets(dom->calle, 100, stdin); dom->calle[strcspn(dom->calle, "\n")] = '\0';
    printf("  Número: ");
    fgets(dom->numero, 10, stdin); dom->numero[strcspn(dom->numero, "\n")] = '\0';
    printf("  Colonia: ");
    fgets(dom->colonia, 100, stdin); dom->colonia[strcspn(dom->colonia, "\n")] = '\0';
    printf("  Código Postal: ");
    fgets(dom->codigoPostal, 10, stdin); dom->codigoPostal[strcspn(dom->codigoPostal, "\n")] = '\0';
    printf("  Ciudad: ");
    fgets(dom->ciudad, 100, stdin); dom->ciudad[strcspn(dom->ciudad, "\n")] = '\0';
}

void capturarEmpleado(Empleado* emp) {
    printf("\n--- Captura de Empleado ---\n");
    printf("Número de empleado: ");
    scanf("%d", &emp->numEmpleado); limpiarBuffer();
    printf("Nombre y apellido: ");
    fgets(emp->nombreApellido, 100, stdin); emp->nombreApellido[strcspn(emp->nombreApellido, "\n")] = '\0';
    printf("Departamento: ");
    fgets(emp->departamento, 50, stdin); emp->departamento[strcspn(emp->departamento, "\n")] = '\0';

    printf("\n--- Domicilio ---\n");
    capturarDomicilio(&emp->domicilio);

    printf("Teléfono: ");
    fgets(emp->telefono, 20, stdin); emp->telefono[strcspn(emp->telefono, "\n")] = '\0';
    printf("Salario mensual: ");
    scanf("%f", &emp->salarioMensual); limpiarBuffer();
}

void mostrarEmpleado(Empleado emp) {
    printf("\n------------------------------\n");
    printf("Número: %d\n", emp.numEmpleado);
    printf("Nombre: %s\n", emp.nombreApellido);
    printf("Departamento: %s\n", emp.departamento);
    printf("Domicilio: %s %s, %s, CP %s, %s\n", emp.domicilio.calle, emp.domicilio.numero,
           emp.domicilio.colonia, emp.domicilio.codigoPostal, emp.domicilio.ciudad);
    printf("Teléfono: %s\n", emp.telefono);
    printf("Salario: $%.2f\n", emp.salarioMensual);
    printf("------------------------------\n");
}

// ==================== LISTA DOBLEMENTE ENLAZADA ====================
Lista* crearLista() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->inicio = lista->fin = NULL;
    return lista;
}

int estaVacia(Lista* lista) {
    return lista->inicio == NULL;
}

Nodo* buscarPorID(Lista* lista, int id) {
    Nodo* actual = lista->inicio;
    while (actual != NULL) {
        if (actual->datos.numEmpleado == id)
            return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void insertarOrdenado(Lista* lista, Empleado emp) {
    if (buscarPorID(lista, emp.numEmpleado)) {
        printf("Error: ya existe un empleado con ese número.\n");
        return;
    }

    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->datos = emp;
    nuevo->siguiente = nuevo->anterior = NULL;

    if (estaVacia(lista)) {
        lista->inicio = lista->fin = nuevo;
        printf("Empleado agregado (lista vacía).\n");
        return;
    }

    if (emp.numEmpleado < lista->inicio->datos.numEmpleado) {
        nuevo->siguiente = lista->inicio;
        lista->inicio->anterior = nuevo;
        lista->inicio = nuevo;
        printf("Empleado agregado (al inicio).\n");
        return;
    }

    Nodo* actual = lista->inicio;
    while (actual->siguiente && actual->siguiente->datos.numEmpleado < emp.numEmpleado)
        actual = actual->siguiente;

    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;
    if (actual->siguiente)
        actual->siguiente->anterior = nuevo;
    else
        lista->fin = nuevo;
    actual->siguiente = nuevo;
    printf("Empleado agregado correctamente.\n");
}

void eliminarPorID(Lista* lista, int id) {
    if (estaVacia(lista)) {
        printf("La lista está vacía.\n");
        return;
    }

    Nodo* actual = buscarPorID(lista, id);
    if (!actual) {
        printf("Empleado no encontrado.\n");
        return;
    }

    if (actual == lista->inicio)
        lista->inicio = actual->siguiente;
    if (actual == lista->fin)
        lista->fin = actual->anterior;
    if (actual->anterior)
        actual->anterior->siguiente = actual->siguiente;
    if (actual->siguiente)
        actual->siguiente->anterior = actual->anterior;

    free(actual);
    printf("Empleado eliminado correctamente.\n");
}

void imprimirPorDepto(Lista* lista, const char* depto) {
    Nodo* actual = lista->inicio;
    int encontrados = 0;
    printf("\n--- Empleados del departamento: %s ---\n", depto);
    while (actual) {
        if (strcmp(actual->datos.departamento, depto) == 0) {
            printf("ID: %d | %s | $%.2f\n", actual->datos.numEmpleado,
                   actual->datos.nombreApellido, actual->datos.salarioMensual);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    if (!encontrados)
        printf("No se encontraron empleados en ese departamento.\n");
}

void modificarRegistro(Lista* lista) {
    int id, op;
    printf("Ingrese el número de empleado a modificar: ");
    scanf("%d", &id); limpiarBuffer();

    Nodo* nodo = buscarPorID(lista, id);
    if (!nodo) {
        printf("Empleado no encontrado.\n");
        return;
    }

    printf("Datos actuales:\n");
    mostrarEmpleado(nodo->datos);

    printf("Campo a modificar:\n");
    printf("1. Nombre y apellido\n2. Departamento\n3. Domicilio\n4. Teléfono\n5. Salario\n0. Cancelar\nOpción: ");
    scanf("%d", &op); limpiarBuffer();

    switch (op) {
        case 1:
            printf("Nuevo nombre y apellido: ");
            fgets(nodo->datos.nombreApellido, 100, stdin);
            nodo->datos.nombreApellido[strcspn(nodo->datos.nombreApellido, "\n")] = '\0';
            break;
        case 2:
            printf("Nuevo departamento: ");
            fgets(nodo->datos.departamento, 50, stdin);
            nodo->datos.departamento[strcspn(nodo->datos.departamento, "\n")] = '\0';
            break;
        case 3:
            printf("Nuevo domicilio:\n");
            capturarDomicilio(&nodo->datos.domicilio);
            break;
        case 4:
            printf("Nuevo teléfono: ");
            fgets(nodo->datos.telefono, 20, stdin);
            nodo->datos.telefono[strcspn(nodo->datos.telefono, "\n")] = '\0';
            break;
        case 5:
            printf("Nuevo salario mensual: ");
            scanf("%f", &nodo->datos.salarioMensual);
            break;
        case 0:
            printf("Modificación cancelada.\n");
            return;
        default:
            printf("Opción no válida.\n");
            return;
    }
    printf("Registro actualizado.\n");
}

void imprimirTodaLaLista(Lista* lista) {
    if (estaVacia(lista)) {
        printf("No hay empleados registrados.\n");
        return;
    }
    Nodo* actual = lista->inicio;
    while (actual) {
        mostrarEmpleado(actual->datos);
        actual = actual->siguiente;
    }
}

void liberarLista(Lista* lista) {
    Nodo* actual = lista->inicio;
    while (actual) {
        Nodo* tmp = actual;
        actual = actual->siguiente;
        free(tmp);
    }
    free(lista);
}

// ==================== ORDENAMIENTO ====================
void swapDatos(Nodo *a, Nodo *b) {
    Empleado tmp = a->datos;
    a->datos = b->datos;
    b->datos = tmp;
}

int comparar(Empleado a, Empleado b, int criterio) {
    switch (criterio) {
        case CRITERIO_ID: return a.numEmpleado - b.numEmpleado;
        case CRITERIO_NOMBRE: return strcmp(a.nombreApellido, b.nombreApellido);
        case CRITERIO_DEPARTAMENTO: return strcmp(a.departamento, b.departamento);
    }
    return 0;
}

void bubbleSortLista(Lista* lista, int criterio) {
    if (estaVacia(lista)) return;
    int cambiado;
    Nodo* fin = NULL;
    do {
        cambiado = 0;
        Nodo* actual = lista->inicio;
        while (actual->siguiente != fin) {
            if (comparar(actual->datos, actual->siguiente->datos, criterio) > 0) {
                swapDatos(actual, actual->siguiente);
                cambiado = 1;
            }
            actual = actual->siguiente;
        }
        fin = actual;
    } while (cambiado);
}

void shakerSortLista(Lista* lista) {
    if (estaVacia(lista)) return;
    int cambiado = 1;
    Nodo* inicio = lista->inicio;
    Nodo* fin = lista->fin;

    while (cambiado) {
        cambiado = 0;
        Nodo* actual = inicio;
        while (actual != fin) {
            if (strcmp(actual->datos.nombreApellido, actual->siguiente->datos.nombreApellido) > 0) {
                swapDatos(actual, actual->siguiente);
                cambiado = 1;
            }
            actual = actual->siguiente;
        }
        fin = actual->anterior;

        if (!cambiado) break;

        cambiado = 0;
        actual = fin;
        while (actual != inicio) {
            if (strcmp(actual->anterior->datos.nombreApellido, actual->datos.nombreApellido) > 0) {
                swapDatos(actual->anterior, actual);
                cambiado = 1;
            }
            actual = actual->anterior;
        }
        inicio = actual->siguiente;
    }
}

void menuImprimir(Lista* lista) {
    int op;
    printf("\n--- Menú de Impresión ---\n");
    printf("1. Ordenar por número de empleado (Burbuja)\n");
    printf("2. Ordenar por nombre (Shaker Sort)\n");
    printf("3. Ordenar por departamento (Burbuja)\n");
    printf("0. Cancelar\nOpción: ");
    scanf("%d", &op); limpiarBuffer();

    if (estaVacia(lista)) {
        printf("No hay empleados registrados.\n");
        return;
    }

    switch (op) {
        case 1:
            bubbleSortLista(lista, CRITERIO_ID);
            imprimirTodaLaLista(lista);
            break;
        case 2:
            shakerSortLista(lista);
            imprimirTodaLaLista(lista);
            break;
        case 3:
            bubbleSortLista(lista, CRITERIO_DEPARTAMENTO);
            imprimirTodaLaLista(lista);
            break;
        case 0:
            return;
        default:
            printf("Opción no válida.\n");
    }

    // Restaurar orden por ID
    bubbleSortLista(lista, CRITERIO_ID);
    printf("\n(La lista ha sido restaurada al orden original por número de empleado)\n");
}
