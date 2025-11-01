#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct {
    int folio;
    char nombre[50];
    char departamento[50];
    char descripcion[200];
    char fecha[20];
} Queja;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct Nodo {
    Queja queja;
    struct Nodo* anterior;
    struct Nodo* siguiente;
} Nodo;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Nodo* cima = NULL;

//===================== PROTOTIPOS =============================
Nodo* crearQueja();
void apilar(Nodo* nueva);
void asignarQueja();
void revisarQuejas();
void quejaSiguiente();
void vaciarPila();
void menu();
//==============================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Nodo* crearQueja() {
    Nodo* nueva = (Nodo*) malloc(sizeof(Nodo));
    if (!nueva) {
        printf("No hay almacenamiento disponible.\n");
        exit(1);
    }

    printf("\n--- Ingreso de datos de la queja ---\n");

    printf("Folio: ");
    scanf("%d", &nueva->queja.folio);
    getchar();

    printf("Nombre del solicitante: ");
    fgets(nueva->queja.nombre, 50, stdin);
    nueva->queja.nombre[strcspn(nueva->queja.nombre, "\n")] = '\0';

    printf("Departamento que se queja: ");
    fgets(nueva->queja.departamento, 50, stdin);
    nueva->queja.departamento[strcspn(nueva->queja.departamento, "\n")] = '\0';

    printf("Descripcion de la queja: ");
    fgets(nueva->queja.descripcion, 200, stdin);
    nueva->queja.descripcion[strcspn(nueva->queja.descripcion, "\n")] = '\0';

    printf("Fecha (dd/mm/aaaa): ");
    fgets(nueva->queja.fecha, 20, stdin);
    nueva->queja.fecha[strcspn(nueva->queja.fecha, "\n")] = '\0';

    nueva->siguiente = NULL;
    nueva->anterior = NULL;

    return nueva;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void apilar(Nodo* nueva) {
    if (cima == NULL) {
        cima = nueva;
    } else {
        nueva->anterior = cima;
        cima->siguiente = nueva;
        cima = nueva;
    }
    printf("\nQueja agregada correctamente a la caja.\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void asignarQueja() {
    if (cima == NULL) {
        printf("\nNo hay quejas en la caja.\n");
        return;
    }

    Nodo* temp = cima;
    printf("\n--- Queja asignada a supervisor ---\n");
    printf("Folio: %d\n", temp->queja.folio);
    printf("Nombre: %s\n", temp->queja.nombre);
    printf("Departamento: %s\n", temp->queja.departamento);
    printf("Descripcion: %s\n", temp->queja.descripcion);
    printf("Fecha: %s\n", temp->queja.fecha);

    cima = temp->anterior;
    if (cima)
        cima->siguiente = NULL;

    free(temp);
    printf("\nLa queja fue retirada de la caja.\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void revisarQuejas() {
    if (cima == NULL) {
        printf("\nNo hay quejas registradas en la caja.\n");
        return;
    }

    Nodo* actual = cima;
    printf("\n--- Lista de quejas en la caja ---\n");
    while (actual != NULL) {
        printf("\nFolio: %d\nNombre: %s\nDepartamento: %s\n",
               actual->queja.folio, actual->queja.nombre, actual->queja.departamento);
        printf("Descripcion: %s\nFecha: %s\n", actual->queja.descripcion, actual->queja.fecha);
        actual = actual->anterior;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void quejaSiguiente() {
    if (cima == NULL) {
        printf("\nNo hay quejas en la caja.\n");
        return;
    }

    printf("\n--- Queja en la cima ---\n");
    printf("Folio: %d\n", cima->queja.folio);
    printf("Nombre: %s\n", cima->queja.nombre);
    printf("Departamento: %s\n", cima->queja.departamento);
    printf("Descripcion: %s\n", cima->queja.descripcion);
    printf("Fecha: %s\n", cima->queja.fecha);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void vaciarPila() {
    Nodo* actual = cima;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->anterior;
        free(temp);
    }
    cima = NULL;
    printf("\nTodas las quejas han sido eliminadas. Saliendo del sistema...\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void menu() {
    int opcion;
    Nodo* nueva;

    do {
      printf("\n _____________________________________ \n");
        printf("|                                     |\n");
        printf("| --------- Menu de Quejas ---------  |\n");
        printf("|      1: Agregar una queja           |\n");
        printf("|      2: Asignar una queja           |\n");
        printf("|      3: Revisar las quejas          |\n");
        printf("|      4: Queja siguiente             |\n");
        printf("|      5: Salir                       |\n");
        printf("|_____________________________________|\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                nueva = crearQueja();
                apilar(nueva);
                break;
            case 2:
                asignarQueja();
                break;
            case 3:
                revisarQuejas();
                break;
            case 4:
                quejaSiguiente();
                break;
            case 5:
                vaciarPila();
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 5);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    menu();
    return 0;
}
