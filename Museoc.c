#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_DIAS 31
#define MAX_MES_LEN 20

void MostrarMenu();
void ProcesarOpcion(int opcionMenu, int diasMaximos, int registroVisitas[], char nombreMes[]);
void RegistrarDia(int diasMaximos, int registroVisitas[]);
void MostrarRegistro(int diasMaximos, int registroVisitas[], char nombreMes[]);
void ConsultarDia(int diasMaximos, int registroVisitas[]);
void GenerarInforme(int diasMaximos, int registroVisitas[]);
void ObtenerDiaMayor(int diasMaximos, int registroVisitas[]);
void ObtenerDiaMenor(int diasMaximos, int registroVisitas[]);
void CalcularTotal(int diasMaximos, int registroVisitas[]);
void CalcularPromedio(int diasMaximos, int registroVisitas[]);

int main() {
    int registroVisitas[MAX_DIAS] = {0};
    char nombreMes[MAX_MES_LEN];
    int opcionMenu = 0;
    int diasMaximos = 0;
    int i;

    printf("--- GESTIÓN DE VISITAS ---\n");
    printf("Ingrese el nombre del mes que va a registrar (Ej: Enero, Febrero, Abril): ");

    fgets(nombreMes, MAX_MES_LEN, stdin);
    nombreMes[strcspn(nombreMes, "\n")] = 0;

    for (i = 0; nombreMes[i]; i++) {
        nombreMes[i] = tolower((unsigned char)nombreMes[i]);
    }

    if (strstr(nombreMes, "enero") || strstr(nombreMes, "marzo") || strstr(nombreMes, "mayo") ||
        strstr(nombreMes, "julio") || strstr(nombreMes, "agosto") || strstr(nombreMes, "octubre") ||
        strstr(nombreMes, "diciembre")) {
        diasMaximos = 31;
    } else if (strstr(nombreMes, "abril") || strstr(nombreMes, "junio") ||
               strstr(nombreMes, "septiembre") || strstr(nombreMes, "noviembre")) {
        diasMaximos = 30;
    } else if (strstr(nombreMes, "febrero")) {
        diasMaximos = 28;
    } else {
        printf("El mes ingresado no es valido. Saliendo...\n");
        diasMaximos = 0;
    }

    if (diasMaximos > 0) {
        do {
            MostrarMenu();
            printf("Selecciona una opcion: ");

            if (scanf("%d", &opcionMenu) != 1) {
                printf("Entrada invalida. Por favor, intente de nuevo.\n");
                opcionMenu = 0;
            }
            while (getchar() != '\n');

            ProcesarOpcion(opcionMenu, diasMaximos, registroVisitas, nombreMes);

        } while (opcionMenu != 5);
    }

    return 0;
}

void MostrarMenu() {
    printf("\n--- MENU PRINCIPAL ---\n");
    printf("1. Registro diario\n");
    printf("2. Imprimir todo el registro\n");
    printf("3. Mostrar visitas por dia\n");
    printf("4. Informe de resultados\n");
    printf("5. Salir\n");
}

void ProcesarOpcion(int opcionMenu, int diasMaximos, int registroVisitas[], char nombreMes[]) {
    switch (opcionMenu) {
        case 1:
            RegistrarDia(diasMaximos, registroVisitas);
            break;
        case 2:
            MostrarRegistro(diasMaximos, registroVisitas, nombreMes);
            break;
        case 3:
            ConsultarDia(diasMaximos, registroVisitas);
            break;
        case 4:
            GenerarInforme(diasMaximos, registroVisitas);
            break;
        case 5:
            printf("Programa finalizado. ¡Vuelva pronto! 👋\n");
            break;
        default:
            printf("Opcion no reconocida. Intente de nuevo.\n");
            break;
    }
}

void RegistrarDia(int diasMaximos, int registroVisitas[]) {
    int diaElegido;
    int cantidadVisitantes;

    printf("--- NUEVO REGISTRO ---\n");

    do {
        printf("Dia del mes a registrar (1 a %d): ", diasMaximos);
        if (scanf("%d", &diaElegido) != 1) {
            printf("ERROR: Entrada no valida.\n");
            diaElegido = 0;
        }
        while (getchar() != '\n');

        if (diaElegido < 1 || diaElegido > diasMaximos) {
            printf("ERROR: El dia no existe en este mes.\n");
        }
    } while (diaElegido < 1 || diaElegido > diasMaximos);

    do {
        printf("Cantidad de visitantes para el Dia %d (0 o mas): ", diaElegido);
        if (scanf("%d", &cantidadVisitantes) != 1) {
            printf("ERROR: Entrada no valida.\n");
            cantidadVisitantes = -1;
        }
        while (getchar() != '\n');

        if (cantidadVisitantes < 0) {
            printf("ERROR: La cantidad debe ser cero o positiva.\n");
        }
    } while (cantidadVisitantes < 0);

    registroVisitas[diaElegido - 1] = cantidadVisitantes;

    printf("Los datos han sido almacenado correctamente\n");
}

void MostrarRegistro(int diasMaximos, int registroVisitas[], char nombreMes[]) {
    int i;
    nombreMes[0] = toupper((unsigned char)nombreMes[0]);

    printf("--- REGISTRO DEL MES DE %s ---\n", nombreMes);
    printf("\n");

    for (i = 0; i < diasMaximos; i++) {
        if (registroVisitas[i] > 0) {
            printf("Dia %d: %d visitantes\n", i + 1, registroVisitas[i]);
        }
    }
}



void ConsultarDia(int diasMaximos, int registroVisitas[]) {
    int diaElegido;

    printf("--- CONSULTAR DIA ---\n");

    do {
        printf("Dia a consultar (1 a %d): ", diasMaximos);
        if (scanf("%d", &diaElegido) != 1) {
            printf("ERROR: Entrada no valida.\n");
            diaElegido = 0;
        }
        while (getchar() != '\n');

        if (diaElegido < 1 || diaElegido > diasMaximos) {
            printf("ERROR: El dia no existe en este mes.\n");
        }
    } while (diaElegido < 1 || diaElegido > diasMaximos);

    if (registroVisitas[diaElegido - 1] > 0) {
        printf("El Dia %d tuvo %d visitantes.\n", diaElegido, registroVisitas[diaElegido - 1]);
    } else {
        printf("El Dia %d no tiene datos registrados (o tuvo 0 visitas).\n", diaElegido);
    }
}


void GenerarInforme(int diasMaximos, int registroVisitas[]) {
    int opcionInforme;

    printf("\n--- SUBMENU DE INFORMES ---\n");
    printf("1. Dia de mayor cantidad de usuarios\n");
    printf("2. Dia de menor cantidad de usuarios\n");
    printf("3. Promedio mensual\n");
    printf("4. Cantidad de usuarios durante el mes\n");
    printf("Seleccione una opcion: ");

    if (scanf("%d", &opcionInforme) != 1) {
        printf("Opcion no reconocida.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    switch (opcionInforme) {
        case 1:
            ObtenerDiaMayor(diasMaximos, registroVisitas);
            break;
        case 2:
            ObtenerDiaMenor(diasMaximos, registroVisitas);
            break;
        case 3:
            CalcularPromedio(diasMaximos, registroVisitas);
            break;
        case 4:
            CalcularTotal(diasMaximos, registroVisitas);
            break;
        default:
            printf("Opcion no reconocida.\n");
            break;
    }
}

void ObtenerDiaMayor(int diasMaximos, int registroVisitas[]) {
    int i;
    int maximo = INT_MIN;
    int diaMayor = 0;

    for (i = 0; i < diasMaximos; i++) {
        if (registroVisitas[i] > maximo) {
            maximo = registroVisitas[i];
            diaMayor = i + 1;
        }
    }

    if (diaMayor > 0) {
        printf("El dia con MAS usuarios fue el Dia %d con %d visitas.\n", diaMayor, maximo);
    } else {
        printf("No hay dias con datos capturados.\n");
    }
}

void ObtenerDiaMenor(int diasMaximos, int registroVisitas[]) {
    int i;
    int minimo = INT_MAX;
    int diaMenor = 0;
    int datosCapturados = 0;

    for (i = 0; i < diasMaximos; i++) {
        if (registroVisitas[i] > 0) {
            datosCapturados = 1;
            if (registroVisitas[i] < minimo) {
                minimo = registroVisitas[i];
                diaMenor = i + 1;
            }
        }
    }

    if (datosCapturados) {
        printf("El dia con MENOS usuarios fue el Dia %d con %d visitas.\n", diaMenor, minimo);
    } else {
        printf("No hay dias con datos capturados.\n");
    }
}

void CalcularTotal(int diasMaximos, int registroVisitas[]) {
    int i;
    int totalVisitas = 0;

    for (i = 0; i < diasMaximos; i++) {
        totalVisitas = totalVisitas + registroVisitas[i];
    }
    printf("El total de usuarios durante el mes fue de: %d\n", totalVisitas);
}

void CalcularPromedio(int diasMaximos, int registroVisitas[]) {
    int i;
    int totalVisitas = 0;
    int diasRegistrados = 0;
    float promedioDiario;

    for (i = 0; i < diasMaximos; i++) {
        totalVisitas = totalVisitas + registroVisitas[i];
        if (registroVisitas[i] > 0) {
            diasRegistrados = diasRegistrados + 1;
        }
    }

    if (diasRegistrados > 0) {
        promedioDiario = (float)totalVisitas / diasRegistrados;
        printf("El promedio diario de visitas (basado en %d dias) es: %.2f\n", diasRegistrados, promedioDiario);
    } else {
        printf("No se puede calcular el promedio. No hay dias registrados.\n");
    }
}
