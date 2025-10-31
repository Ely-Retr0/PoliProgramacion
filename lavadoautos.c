#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// ======== ESTRUCTURAS ========

typedef struct Auto {
    char placas[15];
    char color[20];
    char marca[30];
    char modelo[20];
    char servicio[30]; // tipo de servicio
    struct Auto *sig;
    struct Auto *ant;
} TAuto;

typedef struct {
    TAuto *frente;
    TAuto *final;
} TCola;


// ======== PROTOTIPOS ========
void agregarServicio(TCola *cola);
void asignarServicio(TCola *cola);
void mostrarLista(TCola cola);
void verSiguiente(TCola cola);
void eliminarCola(TCola *cola);


// ======== FUNCIÓN PRINCIPAL ========

int main() {
      setlocale(LC_ALL, "");
    TCola cola;
    cola.frente = cola.final = NULL;
    int opcion;

    do {
        printf("\n===== SISTEMA DE LAVADO DE AUTOS =====\n");
        printf("1. Agregar servicio\n");
        printf("2. Asignación del servicio\n");
        printf("3. Mostrar lista de espera\n");
        printf("4. Ver siguiente\n");
        printf("5. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // limpiar buffer

        switch(opcion) {
            case 1: agregarServicio(&cola); break;
            case 2: asignarServicio(&cola); break;
            case 3: mostrarLista(cola); break;
            case 4: verSiguiente(cola); break;
            case 5:
                eliminarCola(&cola);
                printf("\nPrograma finalizado. La lista de espera ha sido eliminada.\n");
                break;
            default:
                printf("\nOpción no válida.\n");
        }
    } while(opcion != 5);

    return 0;
}


// ======== FUNCIONES ========

void agregarServicio(TCola *cola) {
    TAuto *nuevo = (TAuto*) malloc(sizeof(TAuto));
    if (nuevo == NULL) {
        printf("Error: no se pudo asignar memoria.\n");
        return;
    }

    printf("\nIngrese las placas del auto: ");
    fgets(nuevo->placas, 15, stdin);
    nuevo->placas[strcspn(nuevo->placas, "\n")] = '\0';

    printf("Color del auto: ");
    fgets(nuevo->color, 20, stdin);
    nuevo->color[strcspn(nuevo->color, "\n")] = '\0';

    printf("Marca del auto: ");
    fgets(nuevo->marca, 30, stdin);
    nuevo->marca[strcspn(nuevo->marca, "\n")] = '\0';

    printf("Modelo del auto: ");
    fgets(nuevo->modelo, 20, stdin);
    nuevo->modelo[strcspn(nuevo->modelo, "\n")] = '\0';

    printf("Tipo de servicio (lavado sencillo / lavado con aspirado / lavado premium): ");
    fgets(nuevo->servicio, 30, stdin);
    nuevo->servicio[strcspn(nuevo->servicio, "\n")] = '\0';

    nuevo->sig = NULL;
    nuevo->ant = NULL;

    // Insertar al final de la cola (enqueue)
    if (cola->frente == NULL) {
        cola->frente = cola->final = nuevo;
    } else {
        nuevo->ant = cola->final;
        cola->final->sig = nuevo;
        cola->final = nuevo;
    }

    printf("\nAuto agregado a la lista de espera correctamente.\n");
}

void asignarServicio(TCola *cola) {
    if (cola->frente == NULL) {
        printf("\nNo hay autos en la lista de espera.\n");
        return;
    }

    TAuto *aux = cola->frente;
    printf("\n===== AUTO ASIGNADO A SERVICIO =====\n");
    printf("Placas: %s\n", aux->placas);
    printf("Color: %s\n", aux->color);
    printf("Marca: %s\n", aux->marca);
    printf("Modelo: %s\n", aux->modelo);
    printf("Tipo de servicio: %s\n", aux->servicio);

    // Eliminar del frente de la cola (dequeue)
    cola->frente = aux->sig;
    if (cola->frente != NULL)
        cola->frente->ant = NULL;
    else
        cola->final = NULL;

    free(aux);
    printf("\nEl auto ha sido removido de la lista de espera.\n");
}

void mostrarLista(TCola cola) {
    if (cola.frente == NULL) {
        printf("\nNo hay autos en la lista de espera.\n");
        return;
    }

    TAuto *aux = cola.frente;
    printf("\n===== LISTA DE ESPERA =====\n");
    while (aux != NULL) {
        printf("Placas: %s | Color: %s | Marca: %s | Modelo: %s\n", aux->placas, aux->color, aux->marca, aux->modelo);
        printf("Servicio: %s\n", aux->servicio);
        printf("--------------------------------------\n");
        aux = aux->sig;
    }
}

void verSiguiente(TCola cola) {
    if (cola.frente == NULL) {
        printf("\nNo hay autos en espera.\n");
        return;
    }

    printf("\n===== SIGUIENTE AUTO EN ESPERA =====\n");
    printf("Placas: %s\n", cola.frente->placas);
    printf("Color: %s\n", cola.frente->color);
    printf("Marca: %s\n", cola.frente->marca);
    printf("Modelo: %s\n", cola.frente->modelo);
    printf("Tipo de servicio: %s\n", cola.frente->servicio);
}

void eliminarCola(TCola *cola) {
    TAuto *aux;
    while (cola->frente != NULL) {
        aux = cola->frente;
        cola->frente = cola->frente->sig;
        free(aux);
    }
    cola->final = NULL;
}
