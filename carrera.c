#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ATLETAS 500
#define MAX_CARRERAS 3
#define MAX_CONTACTOS 3

typedef struct {
    char calle[50];
    char colonia[50];
    char ciudad[50];
    char estado[50];
} Domicilio;

typedef struct {
    char nombre[50];
    char telefono[15];
} ContactoEmergencia;

typedef struct {
    int numeroRegistro;
    char nombre[50];
    Domicilio domicilio;
    int edad;
    char genero[10];
    ContactoEmergencia contactos[MAX_CONTACTOS];
    int carreras[MAX_CARRERAS];
    int numCarreras;
} Registro;

// Prototipos
void menu();
void op_menu(Registro atletas[], int *total);
void guardarRegistro(Registro atletas[], int *total);
void imprimirTodo(Registro atletas[], int total);
void mostrarPorCategoria(Registro atletas[], int total);
void mostrarPorNumero(Registro atletas[], int total);
void mostrarPorNombre(Registro atletas[], int total);
void limpiarBuffer();

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    setlocale(LC_ALL, "");
    Registro atletas[MAX_ATLETAS] = {0};
    int total = 0;
    op_menu(atletas, &total);
    return 0;
}

void menu() {
    printf("\n===== MENÚ PRINCIPAL =====\n");
    printf("1. Guardar registro de atleta\n");
    printf("2. Imprimir todos los registros\n");
    printf("3. Mostrar por categoría (100, 200, 400 m)\n");
    printf("4. Mostrar por número de registro\n");
    printf("5. Mostrar por nombre\n");
    printf("6. Salir\n");
}

void op_menu(Registro atletas[], int *total) {
    int op;
    do {
        menu();
        printf("Elige una opción: ");
        if (scanf("%d", &op) != 1) {
            printf("\nEntrada inválida. Intente de nuevo.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer(); // limpia salto de línea

        switch(op) {
            case 1: guardarRegistro(atletas, total); break;
            case 2: imprimirTodo(atletas, *total); break;
            case 3: mostrarPorCategoria(atletas, *total); break;
            case 4: mostrarPorNumero(atletas, *total); break;
            case 5: mostrarPorNombre(atletas, *total); break;
            case 6: printf("\nSaliendo del programa...\n"); break;
            default: printf("\nOpción inválida, intenta de nuevo.\n");
        }
    } while(op != 6);
}

void guardarRegistro(Registro atletas[], int *total) {
    if(*total >= MAX_ATLETAS) {
        printf("\nLímite máximo de atletas alcanzado.\n");
        return;
    }

    Registro *a = &atletas[*total];
    a->numeroRegistro = *total + 1;

    printf("\n=== Registro #%d ===\n", a->numeroRegistro);

    printf("Nombre del atleta: ");
    fgets(a->nombre, sizeof(a->nombre), stdin);
    a->nombre[strcspn(a->nombre, "\n")] = 0;

    printf("\n--- Domicilio ---\n");
    printf("Calle: ");
    fgets(a->domicilio.calle, sizeof(a->domicilio.calle), stdin);
    a->domicilio.calle[strcspn(a->domicilio.calle, "\n")] = 0;

    printf("Colonia: ");
    fgets(a->domicilio.colonia, sizeof(a->domicilio.colonia), stdin);
    a->domicilio.colonia[strcspn(a->domicilio.colonia, "\n")] = 0;

    printf("Ciudad: ");
    fgets(a->domicilio.ciudad, sizeof(a->domicilio.ciudad), stdin);
    a->domicilio.ciudad[strcspn(a->domicilio.ciudad, "\n")] = 0;

    printf("Estado: ");
    fgets(a->domicilio.estado, sizeof(a->domicilio.estado), stdin);
    a->domicilio.estado[strcspn(a->domicilio.estado, "\n")] = 0;

    // Validar edad
    do {
        printf("Edad (14 a 50): ");
        if (scanf("%d", &a->edad) != 1) {
            printf("Entrada inválida.\n");
            limpiarBuffer();
            continue;
        }
        if(a->edad < 14 || a->edad > 50)
            printf("Edad fuera del rango permitido.\n");
    } while(a->edad < 14 || a->edad > 50);
    limpiarBuffer();

    printf("Género (M/F): ");
    fgets(a->genero, sizeof(a->genero), stdin);
    a->genero[strcspn(a->genero, "\n")] = 0;

    printf("\n--- Contactos de emergencia ---\n");
    for(int i = 0; i < MAX_CONTACTOS; i++) {
        printf("\nContacto #%d\n", i + 1);
        printf("Nombre: ");
        fgets(a->contactos[i].nombre, sizeof(a->contactos[i].nombre), stdin);
        a->contactos[i].nombre[strcspn(a->contactos[i].nombre, "\n")] = 0;

        printf("Teléfono: ");
        fgets(a->contactos[i].telefono, sizeof(a->contactos[i].telefono), stdin);
        a->contactos[i].telefono[strcspn(a->contactos[i].telefono, "\n")] = 0;
    }

    printf("\n--- Carreras disponibles ---\n");
    printf("1. 100 metros\n2. 200 metros\n3. 400 metros\n");

    do {
        printf("¿Cuántas carreras desea registrar? (1-3): ");
        if (scanf("%d", &a->numCarreras) != 1) {
            printf("Entrada inválida.\n");
            limpiarBuffer();
            continue;
        }
        if(a->numCarreras < 1 || a->numCarreras > 3)
            printf("Número inválido, intente nuevamente.\n");
    } while(a->numCarreras < 1 || a->numCarreras > 3);

    for(int i = 0; i < a->numCarreras; i++) {
        do {
            printf("Carrera #%d (100, 200 o 400): ", i + 1);
            if (scanf("%d", &a->carreras[i]) != 1) {
                printf("Entrada inválida.\n");
                limpiarBuffer();
                continue;
            }
            if(a->carreras[i] != 100 && a->carreras[i] != 200 && a->carreras[i] != 400)
                printf("Valor inválido. Solo 100, 200 o 400.\n");
        } while(a->carreras[i] != 100 && a->carreras[i] != 200 && a->carreras[i] != 400);
    }

    (*total)++;
    printf("\nRegistro guardado exitosamente.\n");
    limpiarBuffer();
}

void imprimirTodo(Registro atletas[], int total) {
    if(total == 0) {
        printf("\nNo hay registros aún.\n");
        return;
    }

    for(int i = 0; i < total; i++) {
        printf("\n=== Registro #%d ===\n", atletas[i].numeroRegistro);
        printf("Nombre: %s\nEdad: %d\nGénero: %s\n",
               atletas[i].nombre, atletas[i].edad, atletas[i].genero);
        printf("Domicilio: %s, %s, %s, %s\n",
               atletas[i].domicilio.calle, atletas[i].domicilio.colonia,
               atletas[i].domicilio.ciudad, atletas[i].domicilio.estado);

        printf("Carreras: ");
        for(int j = 0; j < atletas[i].numCarreras; j++)
            printf("%d m ", atletas[i].carreras[j]);
        printf("\n");

        printf("Contactos de emergencia:\n");
        for(int k = 0; k < MAX_CONTACTOS; k++)
            printf("  %d. %s - %s\n", k + 1,
                   atletas[i].contactos[k].nombre,
                   atletas[i].contactos[k].telefono);
    }
}

void mostrarPorCategoria(Registro atletas[], int total) {
    int cont100 = 0, cont200 = 0, cont400 = 0;

    for(int i = 0; i < total; i++) {
        for(int j = 0; j < atletas[i].numCarreras; j++) {
            if(atletas[i].carreras[j] == 100) cont100++;
            else if(atletas[i].carreras[j] == 200) cont200++;
            else if(atletas[i].carreras[j] == 400) cont400++;
        }
    }

    printf("\nAtletas por categoría:\n");
    printf("100 m: %d\n200 m: %d\n400 m: %d\n", cont100, cont200, cont400);
}

void mostrarPorNumero(Registro atletas[], int total) {
    int num;
    printf("Ingrese el número de registro: ");
    if (scanf("%d", &num) != 1) {
        printf("Entrada inválida.\n");
        limpiarBuffer();
        return;
    }

    for(int i = 0; i < total; i++) {
        if(atletas[i].numeroRegistro == num) {
            printf("\nRegistro #%d - %s, %d años, %s\n",
                   atletas[i].numeroRegistro, atletas[i].nombre,
                   atletas[i].edad, atletas[i].genero);
            return;
        }
    }
    printf("No se encontró el registro.\n");
}

void mostrarPorNombre(Registro atletas[], int total) {
    char nombreBuscado[50];
    int encontrado = 0;

    limpiarBuffer();
    printf("Nombre a buscar: ");
    fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
    nombreBuscado[strcspn(nombreBuscado, "\n")] = 0;

    for(int i = 0; i < total; i++) {
        if(strcmp(atletas[i].nombre, nombreBuscado) == 0) {
            printf("\nRegistro #%d - %s, %d años, %s\n",
                   atletas[i].numeroRegistro, atletas[i].nombre,
                   atletas[i].edad, atletas[i].genero);
            encontrado = 1;
        }
    }

    if(!encontrado)
        printf("No se encontró ningún atleta con ese nombre.\n");
}
