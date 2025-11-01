#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char calle[50];
    char numero[10];
    char colonia[50];
    char codigoPostal[10];
    char ciudad[50];
} Domicilio;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct Empleado {
    int numEmpleado;
    char nombre[50];
    char departamento[50];
    Domicilio domicilio;
    char telefono[20];
    float salario;
    struct Empleado* anterior;
    struct Empleado* siguiente;
} Empleado;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Empleado* cabeza = NULL;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Empleado* crearEmpleado() {
    Empleado* nuevo = (Empleado*) malloc(sizeof(Empleado));
    if (!nuevo) {
        printf("No hay almacenamiento\n");
        exit(1);
    }

    printf("\n--- Ingreso de datos del empleado ---\n");
    printf("Numero de empleado: ");
    scanf("%d", &nuevo->numEmpleado,"\n");
    getchar();

    printf("Nombre y apellido: ");
    fgets(nuevo->nombre, 50, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = '\0';

    printf("Departamento: ");
    fgets(nuevo->departamento, 50, stdin);
    nuevo->departamento[strcspn(nuevo->departamento, "\n")] = '\0';

    printf("Calle: ");
    fgets(nuevo->domicilio.calle, 50, stdin);
    nuevo->domicilio.calle[strcspn(nuevo->domicilio.calle, "\n")] = '\0';

    printf("Numero: ");
    fgets(nuevo->domicilio.numero, 10, stdin);
    nuevo->domicilio.numero[strcspn(nuevo->domicilio.numero, "\n")] = '\0';

    printf("Colonia: ");
    fgets(nuevo->domicilio.colonia, 50, stdin);
    nuevo->domicilio.colonia[strcspn(nuevo->domicilio.colonia, "\n")] = '\0';

    printf("Codigo Postal: ");
    fgets(nuevo->domicilio.codigoPostal, 10, stdin);
    nuevo->domicilio.codigoPostal[strcspn(nuevo->domicilio.codigoPostal, "\n")] = '\0';

    printf("Ciudad: ");
    fgets(nuevo->domicilio.ciudad, 50, stdin);
    nuevo->domicilio.ciudad[strcspn(nuevo->domicilio.ciudad, "\n")] = '\0';

    printf("Telefono: ");
    fgets(nuevo->telefono, 20, stdin);
    nuevo->telefono[strcspn(nuevo->telefono, "\n")] = '\0';

    printf("Salario mensual: ");
    scanf("%f", &nuevo->salario);

    nuevo->anterior = nuevo->siguiente = NULL;
    return nuevo;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void insertarOrdenado(Empleado* nuevo) {
    if (cabeza == NULL || nuevo->numEmpleado < cabeza->numEmpleado) {
        nuevo->siguiente = cabeza;
        if (cabeza)
            cabeza->anterior = nuevo;
        cabeza = nuevo;
        return;
    }

    Empleado* actual = cabeza;
    while (actual->siguiente != NULL && actual->siguiente->numEmpleado < nuevo->numEmpleado)
        actual = actual->siguiente;

    nuevo->siguiente = actual->siguiente;
    nuevo->anterior = actual;
    if (actual->siguiente)
        actual->siguiente->anterior = nuevo;
    actual->siguiente = nuevo;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void eliminarEmpleado(int numero) {
    if (cabeza == NULL) {
        printf("La lista esta vacia.\n");
        return;
    }

    Empleado* actual = cabeza;
    while (actual != NULL && actual->numEmpleado != numero)
        actual = actual->siguiente;

    if (actual == NULL) {
        printf("Empleado no encontrado.\n");
        return;
    }

    if (actual->anterior)
        actual->anterior->siguiente = actual->siguiente;
    else
        cabeza = actual->siguiente;

    if (actual->siguiente)
        actual->siguiente->anterior = actual->anterior;

    free(actual);
    printf("Empleado eliminado correctamente.\n");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mostrarEmpleados() {
    if (cabeza == NULL) {
        printf("No hay empleados registrados.\n");
        return;
    }

    Empleado* actual = cabeza;
    printf("\n--- Lista de empleados ---\n");
    while (actual != NULL) {
        printf("\nNumero: %d\nNombre: %s\nDepartamento: %s\n", actual->numEmpleado, actual->nombre, actual->departamento);
        printf("Domicilio: %s %s, %s, Codigo postal %s, %s\n", actual->domicilio.calle, actual->domicilio.numero,
               actual->domicilio.colonia, actual->domicilio.codigoPostal, actual->domicilio.ciudad);
        printf("Telefono: %s\nSalario: %.2f\n", actual->telefono, actual->salario);
        actual = actual->siguiente;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void menu() {
    int opcion, numero;
    Empleado* nuevo;

    do {
        printf(" _____________________________________ \n");
        printf("|                                     |\n");
        printf("| --------- Menu de opciones -------- |\n");
        printf("|      1: Insertar empleado           |\n");
        printf("|      2: Eliminar empleado           |\n");
        printf("|      3: Mostrar empleados           |\n");
        printf("|      4: Salir                       |\n");
        printf("|_____________________________________|\n\n");

        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                nuevo = crearEmpleado();
                insertarOrdenado(nuevo);
                break;
            case 2:
                printf("Ingrese numero de empleado a eliminar: ");
                scanf("%d", &numero);
                eliminarEmpleado(numero);
                break;
            case 3:
                mostrarEmpleados();
                break;
            case 4:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion no valida.\n");
        }
    } while (opcion != 4);
}
// ======== PROTOTIPOS  ========
Empleado* crearEmpleado();
void insertarOrdenado(Empleado* nuevo);
void eliminarEmpleado(int numero);
void mostrarEmpleados();
void menu();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main() {
    menu();
    return 0;
}

