#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define MAX_ATLETAS 100
#define NUM_CONTACTOS 3

// Estructura para el domicilio
typedef struct {
char calle[50];
int numeroExterior;
char estado[30];
} Domicilio;

// Estructura para contactos de emergencia
typedef struct {
char nombre[30];
char apellidoP[30];
char apellidoM[30];
char telefono[15];
} ContactoEmergencia;

// Estructura principal del registro
typedef struct {
int id;
char nombre[30];
char apellidoP[30];
char apellidoM[30];
Domicilio domicilio;
int tipoCarrera; // 100, 200 o 400 mts
ContactoEmergencia contactos[NUM_CONTACTOS];
} Registro;

// Prototipos de funciones
void capturarRegistro(Registro *r, int id);
void mostrarRegistro(Registro r);
void imprimirTodos(Registro atletas[], int total);
void mostrarPorCategoria(Registro atletas[], int total);
void mostrarPorNumero(Registro atletas[], int total, int id);
void mostrarPorNombre(Registro atletas[], int total, char nombre[]);

// Función principal
int main() {
Registro atletas[MAX_ATLETAS];
int total = 0, opcion, idAuto = 1;
char nombreBuscado[30];

do {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1.- Guardar\n");
    printf("2.- Imprimir datos\n");
    printf("3.- Mostrar x categoria\n");
    printf("4.- Mostrar x numero de registro\n");
    printf("5.- Mostrar registro x nombre\n");
    printf("6.- Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    getchar(); // limpiar buffer

    switch (opcion) {
        case 1:
            if (total < MAX_ATLETAS) {
                printf("\n--- Registrar atleta #%d ---\n", idAuto);
                capturarRegistro(&atletas[total], idAuto);
                total++;
                idAuto++;
            } else {
                printf("No se pueden registrar mas atletas.\n");
            }
            break;

        case 2:
            imprimirTodos(atletas, total);
            break;

        case 3:
            mostrarPorCategoria(atletas, total);
            break;

        case 4: {
            int idBuscar;
            printf("Ingrese el numero de registro a buscar: ");
            scanf("%d", &idBuscar);
            getchar();
            mostrarPorNumero(atletas, total, idBuscar);
            break;
        }

        case 5:
            printf("Ingrese el nombre del atleta a buscar: ");
            fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
            nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';
            mostrarPorNombre(atletas, total, nombreBuscado);
            break;

        case 6:
            printf("Saliendo del programa...\n");
            break;

        default:
            printf("Opcion no valida. Intente de nuevo.\n");
    }

} while (opcion != 6);

return 0;

}

// --- FUNCIONES ---

void capturarRegistro(Registro *r, int id) {
r->id = id;
printf("ID auto-incrementable: %d\n", id);

printf("Nombre: ");
fgets(r->nombre, sizeof(r->nombre), stdin);
r->nombre[strcspn(r->nombre, "\n")] = '\0';

printf("Apellido paterno: ");
fgets(r->apellidoP, sizeof(r->apellidoP), stdin);
r->apellidoP[strcspn(r->apellidoP, "\n")] = '\0';

printf("Apellido materno: ");
fgets(r->apellidoM, sizeof(r->apellidoM), stdin);
r->apellidoM[strcspn(r->apellidoM, "\n")] = '\0';

printf("\n=== Domicilio ===\n");
printf("Calle: ");
fgets(r->domicilio.calle, sizeof(r->domicilio.calle), stdin);
r->domicilio.calle[strcspn(r->domicilio.calle, "\n")] = '\0';

printf("Numero exterior: ");
scanf("%d", &r->domicilio.numeroExterior);
getchar();

printf("Estado: ");
fgets(r->domicilio.estado, sizeof(r->domicilio.estado), stdin);
r->domicilio.estado[strcspn(r->domicilio.estado, "\n")] = '\0';

printf("\nTipo de carrera (100, 200 o 400 mts): ");
scanf("%d", &r->tipoCarrera);
getchar();

printf("\n=== Contactos de emergencia ===\n");
for (int i = 0; i < NUM_CONTACTOS; i++) {
    printf("\nContacto #%d\n", i + 1);
    printf("Nombre: ");
    fgets(r->contactos[i].nombre, sizeof(r->contactos[i].nombre), stdin);
    r->contactos[i].nombre[strcspn(r->contactos[i].nombre, "\n")] = '\0';

    printf("Apellido paterno: ");
    fgets(r->contactos[i].apellidoP, sizeof(r->contactos[i].apellidoP), stdin);
    r->contactos[i].apellidoP[strcspn(r->contactos[i].apellidoP, "\n")] = '\0';

    printf("Apellido materno: ");
    fgets(r->contactos[i].apellidoM, sizeof(r->contactos[i].apellidoM), stdin);
    r->contactos[i].apellidoM[strcspn(r->contactos[i].apellidoM, "\n")] = '\0';

    printf("Telefono: ");
    fgets(r->contactos[i].telefono, sizeof(r->contactos[i].telefono), stdin);
    r->contactos[i].telefono[strcspn(r->contactos[i].telefono, "\n")] = '\0';
}

printf("\nRegistro guardado correctamente.\n");

}

void mostrarRegistro(Registro r) {
printf("\nID: %d\n", r.id);
printf("Nombre completo: %s %s %s\n", r.nombre, r.apellidoP, r.apellidoM);
printf("Domicilio: %s, No. %d, %s\n", r.domicilio.calle, r.domicilio.numeroExterior, r.domicilio.estado);
printf("Tipo de carrera: %d mts\n", r.tipoCarrera);

printf("Contactos de emergencia:\n");
for (int i = 0; i < NUM_CONTACTOS; i++) {
    printf("  #%d %s %s %s - Tel: %s\n", i + 1,
           r.contactos[i].nombre, r.contactos[i].apellidoP,
           r.contactos[i].apellidoM, r.contactos[i].telefono);
}

}

void imprimirTodos(Registro atletas[], int total) {
if (total == 0) {
printf("No hay registros.\n");
return;
}

printf("\n=== Lista de atletas registrados ===\n");
for (int i = 0; i < total; i++) {
    mostrarRegistro(atletas[i]);
}

}

void mostrarPorCategoria(Registro atletas[], int total) {
int cont100 = 0, cont200 = 0, cont400 = 0;

for (int i = 0; i < total; i++) {
    if (atletas[i].tipoCarrera == 100)
        cont100++;
    else if (atletas[i].tipoCarrera == 200)
        cont200++;
    else if (atletas[i].tipoCarrera == 400)
        cont400++;
}

printf("\n=== Total de participantes por categoria ===\n");
printf("100 mts: %d\n", cont100);
printf("200 mts: %d\n", cont200);
printf("400 mts: %d\n", cont400);

}

void mostrarPorNumero(Registro atletas[], int total, int id) {
for (int i = 0; i < total; i++) {
if (atletas[i].id == id) {
mostrarRegistro(atletas[i]);
return;
}
}
printf("No se encontro ningun atleta con ese numero de registro.\n");
}

void mostrarPorNombre(Registro atletas[], int total, char nombre[]) {
int encontrado = 0;
for (int i = 0; i < total; i++) {
if (strcasecmp(atletas[i].nombre, nombre) == 0) {
mostrarRegistro(atletas[i]);
encontrado = 1;
}
}
if (!encontrado)
printf("No se encontro ningun atleta con ese nombre.\n");
}

