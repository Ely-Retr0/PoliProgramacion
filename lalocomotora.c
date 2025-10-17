#include <stdio.h>
#include <string.h>

#define MAX_PARTICIPANTES 1
#define MAX_CONTACTOS 3

//********************************************************
struct nombre {
    char nombres[20];
    char apellidoP[20];
    char apellidoM[20];
};
//*********************************************************
struct domicilio {
    char calle[30];
    char colonia[20];
    char estado[20];
    char municipio[20];
    int codigoP;
    int numExt;
};
//********************************************************
struct contactos {
    char nom[40];
    char telefono[20];
};
//********************************************************
typedef struct corredor {
    int numRegistro;
    struct nombre cornom;
    struct domicilio cordom;
    int edad;
    char genero[10];
    struct contactos corcon[MAX_CONTACTOS];
    int carreras[3]; // 100, 200, 400
} corre;

//****************** PROTOTIPOS *********************************
void menu();
void op_menu(corre lista[]);
void registrar(corre lista[], int i);
void imprimir(corre lista[], int total);
void mostrar_categoria(corre lista[], int total);
void mostrar_registro(corre lista[], int total);
void mostrar_nombre(corre lista[], int total);

//********************* MAIN **********************************
int main() {
    corre lista[MAX_PARTICIPANTES];
    op_menu(lista);
    return 0;
}

//**********************************************************
void menu() {
    printf("\n==== MENU ====\n");
    printf("1. Guardar registro\n");
    printf("2. Imprimir todo\n");
    printf("3. Mostrar por categoria\n");
    printf("4. Mostrar por numero de registro\n");
    printf("5. Mostrar por nombre\n");
    printf("6. Salir\n");
}

//**********************************************************
void op_menu(corre lista[]) {
    int opcion;
    int total = 0;

    do {
        menu();
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrar(lista, total);
                total++;
                break;
            case 2:
                imprimir(lista, total);
                break;
            case 3:
                mostrar_categoria(lista, total);
                break;
            case 4:
                mostrar_registro(lista, total);
                break;
            case 5:
                mostrar_nombre(lista, total);
                break;
            case 6:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 6);
}

//**********************************************************
void registrar(corre lista[], int i) {
    lista[i].numRegistro = i + 1; // autoincremental

    printf("\n=== Registro #%d ===\n", lista[i].numRegistro);

    printf("Nombre: ");
    scanf(" %[^\n]", lista[i].cornom.nombres);

    printf("Apellido paterno: ");
    scanf(" %[^\n]", lista[i].cornom.apellidoP);

    printf("Apellido materno: ");
    scanf(" %[^\n]", lista[i].cornom.apellidoM);

    printf("Edad: ");
    scanf("%d", &lista[i].edad);

    if (lista[i].edad < 14 || lista[i].edad > 50) {
        printf("Edad no permitida (14-50).\n");
        return;
    }

    printf("Genero: ");
    scanf(" %[^\n]", lista[i].genero);

    printf("Calle: ");
    scanf(" %[^\n]", lista[i].cordom.calle);

    printf("Colonia: ");
    scanf(" %[^\n]", lista[i].cordom.colonia);

    printf("Municipio: ");
    scanf(" %[^\n]", lista[i].cordom.municipio);

    printf("Estado: ");
    scanf(" %[^\n]", lista[i].cordom.estado);

    printf("Codigo Postal: ");
    scanf("%d", &lista[i].cordom.codigoP);

    printf("Numero exterior: ");
    scanf("%d", &lista[i].cordom.numExt);

    printf("\n--- Contactos de emergencia ---\n");
    for (int j = 0; j < MAX_CONTACTOS; j++) {
        printf("Contacto %d - Nombre: ", j + 1);
        scanf(" %[^\n]", lista[i].corcon[j].nom);
        printf("Telefono: ");
        scanf(" %[^\n]", lista[i].corcon[j].telefono);
    }

    printf("\n--- Tipo de carrera (1 = sí, 0 = no) ---\n");
    printf("100 metros: "); scanf("%d", &lista[i].carreras[0]);
    printf("200 metros: "); scanf("%d", &lista[i].carreras[1]);
    printf("400 metros: "); scanf("%d", &lista[i].carreras[2]);

    printf("\nRegistro guardado con exito.\n");
}

//**********************************************************
void imprimir(corre lista[], int total) {
    if (total == 0) {
        printf("\nNo hay registros guardados.\n");
        return;
    }

    printf("\n=== LISTA DE PARTICIPANTES ===\n");
    for (int i = 0; i < total; i++) {
        printf("\nRegistro #%d\n", lista[i].numRegistro);
        printf("Nombre: %s %s %s\n", lista[i].cornom.nombres, lista[i].cornom.apellidoP, lista[i].cornom.apellidoM);
        printf("Edad: %d\n", lista[i].edad);
        printf("Genero: %s\n", lista[i].genero);
        printf("Direccion: %s, %s, %s, %s, CP %d, No.%d\n",
               lista[i].cordom.calle, lista[i].cordom.colonia,
               lista[i].cordom.municipio, lista[i].cordom.estado,
               lista[i].cordom.codigoP, lista[i].cordom.numExt);
        printf("Carreras: ");
        if (lista[i].carreras[0]) printf("100m ");
        if (lista[i].carreras[1]) printf("200m ");
        if (lista[i].carreras[2]) printf("400m ");
        printf("\n");
    }
}

//**********************************************************
void mostrar_categoria(corre lista[], int total) {
    if (total == 0) {
        printf("\nNo hay registros.\n");
        return;
    }

    int cat;
    int cont = 0;

    printf("\nElige categoria:\n1. 100m\n2. 200m\n3. 400m\n");
    scanf("%d", &cat);

    printf("\n=== Participantes en ");
    if (cat == 1) printf("100m ===\n");
    else if (cat == 2) printf("200m ===\n");
    else if (cat == 3) printf("400m ===\n");
    else {
        printf("Categoria no valida.\n");
        return;
    }

    for (int i = 0; i < total; i++) {
        if (lista[i].carreras[cat - 1]) {
            printf("%d. %s %s %s\n", lista[i].numRegistro,
                   lista[i].cornom.nombres,
                   lista[i].cornom.apellidoP,
                   lista[i].cornom.apellidoM);
            cont++;
        }
    }

    printf("\nTotal de participantes en esa categoria: %d\n", cont);
}

//**********************************************************
void mostrar_registro(corre lista[], int total) {
    if (total == 0) {
        printf("\nNo hay registros.\n");
        return;
    }

    int num;
    printf("Ingrese numero de registro: ");
    scanf("%d", &num);

    for (int i = 0; i < total; i++) {
        if (lista[i].numRegistro == num) {
            printf("\nRegistro #%d encontrado\n", lista[i].numRegistro);
            printf("Nombre: %s %s %s\n", lista[i].cornom.nombres, lista[i].cornom.apellidoP, lista[i].cornom.apellidoM);
            printf("Edad: %d\n", lista[i].edad);
            printf("Genero: %s\n", lista[i].genero);
            printf("Direccion: %s, %s, %s, %s, CP %d, No.%d\n",
                   lista[i].cordom.calle, lista[i].cordom.colonia,
                   lista[i].cordom.municipio, lista[i].cordom.estado,
                   lista[i].cordom.codigoP, lista[i].cordom.numExt);
            printf("Carreras: ");
            if (lista[i].carreras[0]) printf("100m ");
            if (lista[i].carreras[1]) printf("200m ");
            if (lista[i].carreras[2]) printf("400m ");
            printf("\n");
            return;
        }
    }

    printf("Registro no encontrado.\n");
}

//**********************************************************
void mostrar_nombre(corre lista[], int total) {
    if (total == 0) {
        printf("\nNo hay registros.\n");
        return;
    }

    char buscar[20];
    printf("Ingrese el nombre del atleta: ");
    scanf(" %[^\n]", buscar);

    int encontrado = 0;
    for (int i = 0; i < total; i++) {
        if (strcasecmp(lista[i].cornom.nombres, buscar) == 0) {
            printf("\nRegistro #%d\n", lista[i].numRegistro);
            printf("Nombre: %s %s %s\n", lista[i].cornom.nombres, lista[i].cornom.apellidoP, lista[i].cornom.apellidoM);
            printf("Edad: %d\n", lista[i].edad);
            printf("Genero: %s\n", lista[i].genero);
            printf("Direccion: %s, %s, %s, %s, CP %d, No.%d\n",
                   lista[i].cordom.calle, lista[i].cordom.colonia,
                   lista[i].cordom.municipio, lista[i].cordom.estado,
                   lista[i].cordom.codigoP, lista[i].cordom.numExt);
            printf("Carreras: ");
            if (lista[i].carreras[0]) printf("100m ");
            if (lista[i].carreras[1]) printf("200m ");
            if (lista[i].carreras[2]) printf("400m ");
            printf("\n");
            encontrado = 1;
        }
    }

    if (!encontrado)
        printf("No se encontro ningun atleta con ese nombre.\n");
}
