#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ATLETAS 500
#define MAX_CARRERAS 3
#define MAX_CONTACTOS 3

typedef struct { //inicio struct Domicilio
    char calle[50];
    char colonia[50];
    char ciudad[50];
    char estado[50];
} Domicilio; //fin struct Domicilio

typedef struct { //inicio struct ContactoEmergencia
    char nombre[50];
    char telefono[15];
} ContactoEmergencia; //fin struct ContactoEmergencia

typedef struct { //inicio struct Registro
    int numeroRegistro;
    char nombre[50];
    Domicilio domicilio;
    int edad;
    char genero[10];
    ContactoEmergencia contactos[MAX_CONTACTOS];
    int carreras[MAX_CARRERAS];
    int numCarreras;
} Registro; //fin struct Registro

// Prototipos
void menu(); //inicio void
void op_menu(Registro atletas[], int *total); //inicio void
void guardarRegistro(Registro atletas[], int *total); //inicio void
void imprimirTodo(Registro atletas[], int total); //inicio void
void mostrarPorCategoria(Registro atletas[], int total); //inicio void
void mostrarPorNumero(Registro atletas[], int total); //inicio void
void mostrarPorNombre(Registro atletas[], int total); //inicio void

//*****************************************************************
int main() { //inicio main
    setlocale(LC_ALL, "");
    Registro atletas[MAX_ATLETAS] = {0};
    int total = 0;
    op_menu(atletas, &total);
    return 0;
} //fin main

//*****************************************************************
void menu() { //inicio void menu
    printf("\n===== MENÚ PRINCIPAL =====\n");
    printf("1. Guardar registro de atleta\n");
    printf("2. Imprimir todos los registros\n");
    printf("3. Mostrar por categoría (100, 200, 400 m)\n");
    printf("4. Mostrar por número de registro\n");
    printf("5. Mostrar por nombre\n");
    printf("6. Salir\n");
} //fin void menu

//*****************************************************************
void op_menu(Registro atletas[], int *total) { //inicio void op_menu
    int op;
    do { //inicio do
        menu();
        printf("Elige una opción: ");
        scanf("%d", &op);
        getchar();

        switch(op) { //inicio switch
            case 1: guardarRegistro(atletas, total); break;
            case 2: imprimirTodo(atletas, *total); break;
            case 3: mostrarPorCategoria(atletas, *total); break;
            case 4: mostrarPorNumero(atletas, *total); break;
            case 5: mostrarPorNombre(atletas, *total); break;
            case 6: printf("\nSaliendo del programa...\n"); break;
            default: printf("\nOpción inválida, intenta de nuevo.\n");
        } //fin switch
    } while(op != 6); //fin do
} //fin void op_menu

//*****************************************************************
void guardarRegistro(Registro atletas[], int *total) { //inicio void guardarRegistro
    if(*total >= MAX_ATLETAS) {
        printf("\nLímite máximo de atletas alcanzado.\n");
        return;
    }

    Registro *a = &atletas[*total];
    a->numeroRegistro = *total + 1;

    printf("\n=== Registro #%d ===\n", a->numeroRegistro);

    printf("Nombre del atleta: ");
    fflush(stdin);
    gets(a->nombre);
    getchar();

    printf("\n--- Domicilio ---\n");
    printf("Calle: "); fflush(stdin); gets(a->domicilio.calle); getchar();
    printf("Colonia: "); gets(a->domicilio.colonia); getchar();
    printf("Ciudad: "); gets(a->domicilio.ciudad); getchar();
    printf("Estado: "); gets(a->domicilio.estado); getchar();

    do { //inicio do
        printf("Edad (14 a 50): ");
        scanf("%d", &a->edad);
        if(a->edad < 14 || a->edad > 50)
            printf("Edad inválida.\n");
    } while(a->edad < 14 || a->edad > 50); //fin do
    getchar();

    printf("Género (M/F): ");
    fflush(stdin);
    gets(a->genero);
    getchar();

    printf("\n--- Contactos de emergencia ---\n");
    for(int i = 0; i < MAX_CONTACTOS; i++) { //inicio for
        printf("\nContacto #%d\n", i+1);
        printf("Nombre: ");
        fflush(stdin);
        gets(a->contactos[i].nombre);
        getchar();
        printf("Teléfono: ");
        gets(a->contactos[i].telefono);
        getchar();
    } //fin for

    printf("\n--- Carreras disponibles ---\n");
    printf("1. 100 metros\n2. 200 metros\n3. 400 metros\n");
    printf("¿Cuántas carreras desea registrar? (1-3): ");
    scanf("%d", &a->numCarreras);

    if(a->numCarreras < 1) a->numCarreras = 1;
    if(a->numCarreras > 3) a->numCarreras = 3;

    for(int i = 0; i < a->numCarreras; i++) { //inicio for
        printf("Carrera #%d (100, 200 o 400): ", i+1);
        scanf("%d", &a->carreras[i]);
    } //fin for

    (*total)++;
    printf("\nRegistro guardado exitosamente.\n");
    getchar();
} //fin void guardarRegistro

//*****************************************************************
void imprimirTodo(Registro atletas[], int total) { //inicio void imprimirTodo
    if(total == 0) {
        printf("\nNo hay registros aún.\n");
        return;
    }

    for(int i = 0; i < total; i++) { //inicio for
        printf("\n=== Registro #%d ===\n", atletas[i].numeroRegistro);
        printf("Nombre: %s\nEdad: %d\nGénero: %s\n",
               atletas[i].nombre, atletas[i].edad, atletas[i].genero);
        printf("Domicilio: %s, %s, %s, %s\n",
               atletas[i].domicilio.calle, atletas[i].domicilio.colonia,
               atletas[i].domicilio.ciudad, atletas[i].domicilio.estado);

        printf("\nCarreras: ");
        for(int j = 0; j < atletas[i].numCarreras; j++) { //inicio for
            printf("%d m ", atletas[i].carreras[j]);
        } //fin for

        printf("\nContactos de emergencia:\n");
        for(int k = 0; k < MAX_CONTACTOS; k++) { //inicio for
            printf("  %d. %s - %s\n", k+1,
                   atletas[i].contactos[k].nombre,
                   atletas[i].contactos[k].telefono);
        } //fin for
    } //fin for
} //fin void imprimirTodo

//*****************************************************************
void mostrarPorCategoria(Registro atletas[], int total) { //inicio void mostrarPorCategoria
    int cont100 = 0, cont200 = 0, cont400 = 0;

    for(int i = 0; i < total; i++) { //inicio for
        for(int j = 0; j < atletas[i].numCarreras; j++) { //inicio for
            if(atletas[i].carreras[j] == 100) cont100++;
            else if(atletas[i].carreras[j] == 200) cont200++;
            else if(atletas[i].carreras[j] == 400) cont400++;
        } //fin for
    } //fin for

    printf("\nAtletas por categoría:\n");
    printf("100 metros: %d\n", cont100);
    printf("200 metros: %d\n", cont200);
    printf("400 metros: %d\n", cont400);
} //fin void mostrarPorCategoria

//*****************************************************************
void mostrarPorNumero(Registro atletas[], int total) { //inicio void mostrarPorNumero
    int num;
    printf("Ingrese el número de registro: ");
    scanf("%d", &num);

    for(int i = 0; i < total; i++) { //inicio for
        if(atletas[i].numeroRegistro == num) {
            printf("\nRegistro #%d - %s, %d años, %s\n",
                   atletas[i].numeroRegistro, atletas[i].nombre,
                   atletas[i].edad, atletas[i].genero);
            return;
        }
    } //fin for

    printf("No se encontró el registro.\n");
} //fin void mostrarPorNumero

//*****************************************************************
void mostrarPorNombre(Registro atletas[], int total) { //inicio void mostrarPorNombre
    char nombreBuscado[50];
    int encontrado = 0;
    getchar();
    printf("Nombre a buscar: ");
    gets(nombreBuscado);
    getchar();

    for(int i = 0; i < total; i++) { //inicio for
        if(strcmp(atletas[i].nombre, nombreBuscado) == 0) {
            printf("\nRegistro #%d - %s, %d años, %s\n",
                   atletas[i].numeroRegistro, atletas[i].nombre,
                   atletas[i].edad, atletas[i].genero);
            encontrado = 1;
        }
    } //fin for

    if(!encontrado)
        printf("No se encontró ningún atleta con ese nombre.\n");
} //fin void mostrarPorNombre
