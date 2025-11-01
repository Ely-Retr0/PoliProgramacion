#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct {
    char placas[15];
    char color[20];
    char marca[30];
    char modelo[30];
    char tipoServicio[30];
} Auto;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct Nodo {
    Auto autoInfo;
    struct Nodo* anterior;
    struct Nodo* siguiente;
} Nodo;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Nodo* frente = NULL;
Nodo* final = NULL;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Nodo* crearAuto();
void encolar(Nodo* nuevo);
void asignarServicio();
void mostrarListaEspera();
void verSiguiente();
void vaciarCola();
void menu();
void menuTipoServicio(char servicio[30]);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void menuTipoServicio(char servicio[30]) {
    int opcion;
    do {
        printf("\n _____________________________________ \n");
        printf("|                                     |\n");
        printf("| -------- Tipo de Servicio ----------|\n");
        printf("|      1: Lavado sencillo             |\n");
        printf("|      2: Lavado con aspirado         |\n");
        printf("|      3: Lavado premium              |\n");
        printf("|_____________________________________|\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch(opcion) {
            case 1:
                strcpy(servicio, "Lavado sencillo");
                break;
            case 2:
                strcpy(servicio, "Lavado con aspirado");
                break;
            case 3:
                strcpy(servicio, "Lavado premium");
                break;
            default:
                printf("Opcion no valida. Intente de nuevo.\n");
                opcion = 0;
        }
    } while(opcion < 1 || opcion > 3);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Nodo* crearAuto() {
    Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (!nuevo) {
        printf("No hay almacenamiento disponible.\n");
        exit(1);
    }

    printf("\n--- Ingreso de datos del auto ---\n");

    printf("Placas: ");
    fgets(nuevo->autoInfo.placas, 15, stdin);
    nuevo->autoInfo.placas[strcspn(nuevo->autoInfo.placas, "\n")] = '\0';

    printf("Color: ");
    fgets(nuevo->autoInfo.color, 20, stdin);
    nuevo->autoInfo.color[strcspn(nuevo->autoInfo.color, "\n")] = '\0';

    printf("Marca: ");
    fgets(nuevo->autoInfo.marca, 30, stdin);
    nuevo->autoInfo.marca[strcspn(nuevo->autoInfo.marca, "\n")] = '\0';

    printf("Modelo: ");
    fgets(nuevo->autoInfo.modelo, 30, stdin);
    nuevo->autoInfo.modelo[strcspn(nuevo->autoInfo.modelo, "\n")] = '\0';

    menuTipoServicio(nuevo->autoInfo.tipoServicio);

    nuevo->anterior = NULL;
    nuevo->siguiente = NULL;

    return nuevo;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void encolar(Nodo* nuevo) {
    if (frente == NULL) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        nuevo->anterior = final;
        final = nuevo;
    }
    printf("\nAuto agregado a la lista de espera correctamente.\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void asignarServicio() {
    if (frente == NULL) {
        printf("\nNo hay autos en la lista de espera.\n");
        return;
    }

    Nodo* temp = frente;
    printf("\n--- Asignación del servicio ---\n");
    printf("Placas: %s\n", temp->autoInfo.placas);
    printf("Color: %s\n", temp->autoInfo.color);
    printf("Marca: %s\n", temp->autoInfo.marca);
    printf("Modelo: %s\n", temp->autoInfo.modelo);
    printf("Tipo de servicio: %s\n", temp->autoInfo.tipoServicio);

    frente = frente->siguiente;
    if (frente)
        frente->anterior = NULL;
    else
        final = NULL;

    free(temp);
    printf("\nEl auto fue retirado de la lista de espera.\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mostrarListaEspera() {
    if (frente == NULL) {
        printf("\nNo hay autos en la lista de espera.\n");
        return;
    }

    Nodo* actual = frente;
    printf("\n--- Lista de espera de autos ---\n");
    while (actual != NULL) {
        printf("\nPlacas: %s\nColor: %s\nMarca: %s\nModelo: %s\nTipo de servicio: %s\n",
               actual->autoInfo.placas, actual->autoInfo.color,
               actual->autoInfo.marca, actual->autoInfo.modelo,
               actual->autoInfo.tipoServicio);
        actual = actual->siguiente;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void verSiguiente() {
    if (frente == NULL) {
        printf("\nNo hay autos en la lista de espera.\n");
        return;
    }

    printf("\n--- Auto siguiente en pasar al área de servicio ---\n");
    printf("Placas: %s\n", frente->autoInfo.placas);
    printf("Color: %s\n", frente->autoInfo.color);
    printf("Marca: %s\n", frente->autoInfo.marca);
    printf("Modelo: %s\n", frente->autoInfo.modelo);
    printf("Tipo de servicio: %s\n", frente->autoInfo.tipoServicio);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void vaciarCola() {
    Nodo* actual = frente;
    while (actual != NULL) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    frente = final = NULL;
    printf("\nTodos los autos han sido eliminados de la lista de espera. Saliendo del sistema...\n");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void menu() {
    int opcion;
    Nodo* nuevo;

    do {
        printf("\n _____________________________________ \n");
        printf("|                                     |\n");
        printf("| ------ Menu Lista de Espera --------|\n");
        printf("|      1: Agregar servicio            |\n");
        printf("|      2: Asignación del servicio     |\n");
        printf("|      3: Mostrar lista de espera     |\n");
        printf("|      4: Ver siguiente               |\n");
        printf("|      5: Salir                       |\n");
        printf("|_____________________________________|\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                nuevo = crearAuto();
                encolar(nuevo);
                break;
            case 2:
                asignarServicio();
                break;
            case 3:
                mostrarListaEspera();
                break;
            case 4:
                verSiguiente();
                break;
            case 5:
                vaciarCola();
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 5);
}
//===================== PROTOTIPOS =============================
Nodo* crearAuto();
void encolar(Nodo* nuevo);
void asignarServicio();
void mostrarListaEspera();
void verSiguiente();
void vaciarCola();
void menu();
void menuTipoServicio(char servicio[30]);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    menu();
    return 0;
}


