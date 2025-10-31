#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// ======== ESTRUCTURAS ========

typedef struct Queja {
    int folio;
    char nombre[50];
    char departamento[50];
    char descripcion[100];
    char fecha[20];
    struct Queja *sig;
    struct Queja *ant;
} TQueja;

typedef struct {
    TQueja *tope;
} TPila;


// ======== PROTOTIPOS ========
void agregarQueja(TPila *pila);
void asignarQueja(TPila *pila);
void revisarQuejas(TPila pila);
void quejaSiguiente(TPila pila);
void eliminarPila(TPila *pila);


// ======== FUNCIÓN PRINCIPAL ========

int main() {
      setlocale(LC_ALL, "");
    TPila pila;
    pila.tope = NULL;
    int opcion;

    do {
        printf("\n===== MENÚ DE CAJA DE QUEJAS =====\n");
        printf("1. Agregar una queja\n");
        printf("2. Asignar una queja\n");
        printf("3. Revisar las quejas\n");
        printf("4. Queja siguiente\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch(opcion) {
            case 1: agregarQueja(&pila); break;
            case 2: asignarQueja(&pila); break;
            case 3: revisarQuejas(pila); break;
            case 4: quejaSiguiente(pila); break;
            case 5:
                eliminarPila(&pila);
                printf("\nPrograma finalizado. Todas las quejas fueron eliminadas.\n");
                break;
            default:
                printf("\nOpción no válida.\n");
        }
    } while(opcion != 5);

    return 0;
}


// ======== FUNCIONES ========

void agregarQueja(TPila *pila) {
    TQueja *nueva = (TQueja*) malloc(sizeof(TQueja));
    if (nueva == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return;
    }

    printf("\nIngrese el folio de la queja: ");
    scanf("%d", &nueva->folio);
    getchar();

    printf("Nombre de quien realiza la queja: ");
    fgets(nueva->nombre, 50, stdin);
    nueva->nombre[strcspn(nueva->nombre, "\n")] = '\0';

    printf("Departamento del que se queja: ");
    fgets(nueva->departamento, 50, stdin);
    nueva->departamento[strcspn(nueva->departamento, "\n")] = '\0';

    printf("Descripción de la queja: ");
    fgets(nueva->descripcion, 100, stdin);
    nueva->descripcion[strcspn(nueva->descripcion, "\n")] = '\0';

    printf("Fecha: ");
    fgets(nueva->fecha, 20, stdin);
    nueva->fecha[strcspn(nueva->fecha, "\n")] = '\0';

    // Insertar en la cima (push)
    nueva->sig = pila->tope;
    nueva->ant = NULL;
    if (pila->tope != NULL)
        pila->tope->ant = nueva;
    pila->tope = nueva;

    printf("\nQueja agregada correctamente.\n");
}

void asignarQueja(TPila *pila) {
    if (pila->tope == NULL) {
        printf("\nNo hay quejas en la caja.\n");
        return;
    }

    TQueja *aux = pila->tope;
    printf("\n===== Queja asignada al supervisor =====\n");
    printf("Folio: %d\n", aux->folio);
    printf("Nombre: %s\n", aux->nombre);
    printf("Departamento: %s\n", aux->departamento);
    printf("Descripción: %s\n", aux->descripcion);
    printf("Fecha: %s\n", aux->fecha);

    // Eliminar del tope (pop)
    pila->tope = aux->sig;
    if (pila->tope != NULL)
        pila->tope->ant = NULL;

    free(aux);
    printf("\nLa queja ha sido removida de la caja.\n");
}

void revisarQuejas(TPila pila) {
    if (pila.tope == NULL) {
        printf("\nNo hay quejas registradas.\n");
        return;
    }

    TQueja *aux = pila.tope;
    printf("\n===== LISTA DE QUEJAS =====\n");
    while (aux != NULL) {
        printf("Folio: %d | Nombre: %s | Depto: %s\n", aux->folio, aux->nombre, aux->departamento);
        printf("Descripción: %s\n", aux->descripcion);
        printf("Fecha: %s\n", aux->fecha);
        printf("---------------------------------------\n");
        aux = aux->sig;
    }
}

void quejaSiguiente(TPila pila) {
    if (pila.tope == NULL) {
        printf("\nNo hay quejas en la caja.\n");
        return;
    }

    printf("\n===== Queja en la cima =====\n");
    printf("Folio: %d\n", pila.tope->folio);
    printf("Nombre: %s\n", pila.tope->nombre);
    printf("Departamento: %s\n", pila.tope->departamento);
    printf("Descripción: %s\n", pila.tope->descripcion);
    printf("Fecha: %s\n", pila.tope->fecha);
}

void eliminarPila(TPila *pila) {
    TQueja *aux;
    while (pila->tope != NULL) {
        aux = pila->tope;
        pila->tope = pila->tope->sig;
        free(aux);
    }
}
