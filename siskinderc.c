 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define tam 98
#define maxnom 20
#define capalm 2000

void VerMenu();
void OpMenu(int op, int edad[], int height[], int iNom[], char almNom[], int tMax, int *cNin, int *pNom);
void GuardarDatNi(int edad[], int height[], int iNom[], char almNom[], int tMax, int *cNin, int *pNom);
void ImprDatN(int edad[], int height[], int iNom[], char almNom[], int cNin);
void BuscN(int edad[], int height[], int iNom[], char almNom[], int cNin);
void BuscE(int edad[], int height[], int iNom[], char almNom[], int cNin);
void BuscEs(int edad[], int height[], int iNom[], char almNom[], int cNin);
void ModificarDatos(int edad[], int height[], int iNom[], char almNom[], int cNin, int *pNom);

int compNomIgual(const char *s1, const char *s2);

int main() {
    int op;
    int cNin = 0;
    int pNom = 0;
    int edad[tam] = {0};
    int height[tam] = {0};
    int iNom[tam] = {0};
    char almNom[capalm] = {0};

    do {
        VerMenu();
        if (scanf("%i", &op) != 1) {
            printf("\nERROR: Ingrese solo numeros. Saliendo...\n");
            op = 7;
        }
        while(getchar() != '\n');

        OpMenu(op, edad, height, iNom, almNom, tam, &cNin, &pNom);
    } while (op != 7);

    return 0;
}

int compNomIgual(const char *s1, const char *s2) {
    if (!s1 || !s2) return 0;
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }
    return (*s1 == *s2);
}

void VerMenu() {
    printf("--- ELIJA UNA OPCION: ---\n");
    printf("1. Guardar Datos de los Ninos\n");
    printf("2. Imprimir todos los datos de los ninos\n");
    printf("3. Buscar por Nombre\n");
    printf("4. Buscar por Edad\n");
    printf("5. Buscar por Estatura\n");
    printf("6. Modificar datos\n");
    printf("7. SALIR\n");
}

void OpMenu(int op, int edad[], int height[], int iNom[], char almNom[], int tMax, int *cNin, int *pNom) {
    switch (op) {
        case 1:
            GuardarDatNi(edad, height, iNom, almNom, tMax, cNin, pNom);
            break;
        case 2:
            ImprDatN(edad, height, iNom, almNom, *cNin);
            break;
        case 3:
            BuscN(edad, height, iNom, almNom, *cNin);
            break;
        case 4:
            BuscE(edad, height, iNom, almNom, *cNin);
            break;
        case 5:
            BuscEs(edad, height, iNom, almNom, *cNin);
            break;
        case 6:
            ModificarDatos(edad, height, iNom, almNom, *cNin, pNom);
            break;
        case 7:
            printf("Saliendo...\n");
            break;
        default:
            printf("Opcion no valida. Intente de nuevo.\n");
            break;
    }
}

void GuardarDatNi(int edad[], int height[], int iNom[], char almNom[], int tMax, int *cNin, int *pNom) {
    int i;
    char nomTemp[maxnom];

    printf("\n--- GUARDAR DATOS ---\n");

    if (*cNin >= tMax) {
        printf("¡ERROR! Capacidad maxima alcanzada (%d).\n", tMax);
        return;
    }

    for (i = *cNin; i < tMax; i++) {

        printf("\nIngresa los datos del Nino #%d:\n", i + 1);

        printf("Ingresa el Nombre (Max %d chars): ", maxnom - 1);
        while(getchar() != '\n');
        fgets(nomTemp, maxnom, stdin);
        nomTemp[strcspn(nomTemp, "\n")] = 0;

        if (*pNom + strlen(nomTemp) + 1 >= capalm) {
            printf("ERROR: No queda espacio para mas nombres en el almacenamiento principal.\n");
            break;
        }

        iNom[i] = *pNom;

        strcpy(&almNom[*pNom], nomTemp);
        *pNom += strlen(nomTemp) + 1;

        do {
            printf("Ingresa la Edad (De 3 a 6 Anos): ");
            if (scanf("%i", &edad[i]) != 1) {
                printf("ERROR, EDAD NO VALIDA (Debe ser un numero).\n");
                while(getchar() != '\n');
                edad[i] = 0;
                continue;
            }
            if (edad[i] < 3 || edad[i] > 6) {
                printf("ERROR, EDAD NO VALIDA.\n");
            } else {
                printf("Edad Valida :)\n");
            }
        } while (edad[i] < 3 || edad[i] > 6);

        do {
            printf("Ingresa la estatura en cm (Min 30cm - Max 110cm): ");
            if (scanf("%i", &height[i]) != 1) {
                printf("ERROR, ENTRADA NO VALIDA (Debe ser un numero).\n");
                while(getchar() != '\n');
                height[i] = 0;
                continue;
            }
            if (height[i] < 30 || height[i] > 110) {
                printf("ERROR, ALTURA NO VALIDA.\n");
            } else {
                printf("Altura Valida :)\n");
            }
        } while (height[i] < 30 || height[i] > 110);

        (*cNin)++;

        char resp;
        printf("\n¿Desea ingresar otro nino? (s/n): ");
        while(getchar() != '\n');
        if (scanf(" %c", &resp) != 1 || (resp != 's' && resp != 'S')) {
            break;
        }
    }

    printf("\nSe guardaron %d datos (Max. %d).\n", *cNin, tMax);
}

void ImprDatN(int edad[], int height[], int iNom[], char almNom[], int cNin) {
    int i;
    printf("\n=== DATOS REGISTRADOS (%d ninos) ===\n", cNin);
    if (cNin == 0) {
        printf("No hay datos para mostrar.\n");
    } else {
        for (i = 0; i < cNin; i++) {
            printf("Nino #%d: Nombre: %s, Edad: %d, Estatura: %dcm\n",
                   i + 1, &almNom[iNom[i]], edad[i], height[i]);
        }
    }
}

void BuscN(int edad[], int height[], int iNom[], char almNom[], int cNin) {
    char nomTemp[maxnom];
    int encontrado = 0;
    int i;

    printf("\n=== BUSCAR POR NOMBRE ===\n");
    if (cNin == 0) {
        printf("No hay datos.\n");
        return;
    }

    printf("Nombre a buscar: ");
    while(getchar() != '\n');
    fgets(nomTemp, maxnom, stdin);
    nomTemp[strcspn(nomTemp, "\n")] = 0;

    for (i = 0; i < cNin; i++) {
        const char *currentName = &almNom[iNom[i]];
        if (compNomIgual(currentName, nomTemp)) {
            printf("ENCONTRADO en posicion %d: Nombre: %s, Edad: %d, Estatura: %dcm\n",
                   i + 1, currentName, edad[i], height[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nombre no encontrado.\n");
    }
}

void BuscE(int edad[], int height[], int iNom[], char almNom[], int cNin) {
    int edadBuscada;
    int encontrado = 0;
    int i;

    printf("\n=== BUSCAR POR EDAD ===\n");
    if (cNin == 0) {
        printf("No hay datos.\n");
        return;
    }

    printf("Edad a buscar: ");
    if (scanf("%i", &edadBuscada) != 1) {
        printf("ERROR, entrada no valida.\n");
        while(getchar() != '\n');
        return;
    }

    for (i = 0; i < cNin; i++) {
        if (edad[i] == edadBuscada) {
            const char *currentName = &almNom[iNom[i]];
            printf("ENCONTRADO en posicion %d: Nombre: %s, Edad: %d, Estatura: %dcm\n",
                   i + 1, currentName, edad[i], height[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Edad no encontrada.\n");
    }
}

void BuscEs(int edad[], int height[], int iNom[], char almNom[], int cNin) {
    int estBuscada;
    int encontrado = 0;
    int i;

    printf("\n=== BUSCAR POR ESTATURA ===\n");
    if (cNin == 0) {
        printf("No hay datos.\n");
        return;
    }

    printf("Estatura a buscar (cm): ");
    if (scanf("%i", &estBuscada) != 1) {
        printf("ERROR, entrada no valida.\n");
        while(getchar() != '\n');
        return;
    }

    for (i = 0; i < cNin; i++) {
        if (height[i] == estBuscada) {
            const char *currentName = &almNom[iNom[i]];
            printf("ENCONTRADO en posicion %d: Nombre: %s, Edad: %d, Estatura: %dcm\n",
                   i + 1, currentName, edad[i], height[i]);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Estatura no encontrada.\n");
    }
}

void ModificarDatos(int edad[], int height[], int iNom[], char almNom[], int cNin, int *pNom) {
    char nomTemp[maxnom];
    int i;
    int posMod = -1;
    int opMod;

    printf("\n=== MODIFICAR DATOS ===\n");
    if (cNin == 0) {
        printf("No hay datos para modificar.\n");
        return;
    }

    printf("Nombre del nino a modificar: ");
    while(getchar() != '\n');
    fgets(nomTemp, maxnom, stdin);
    nomTemp[strcspn(nomTemp, "\n")] = 0;

    for (i = 0; i < cNin; i++) {
        const char *currentName = &almNom[iNom[i]];
        if (compNomIgual(currentName, nomTemp)) {
            posMod = i;
            break;
        }
    }

    if (posMod != -1) {
        const char *currentName = &almNom[iNom[posMod]];
        printf("Nino encontrado en la posicion %d (Nombre: %s).\n", posMod + 1, currentName);
        printf("¿Que desea modificar?\n");
        printf("1. Nombre\n2. Edad\n3. Estatura\nOpcion: ");
        if (scanf("%i", &opMod) != 1) {
            printf("ERROR, Opcion no valida.\n");
            while(getchar() != '\n');
            return;
        }

        while(getchar() != '\n');

        switch (opMod) {
            case 1:
                printf("Nuevo Nombre (Max %d chars): ", maxnom - 1);
                char newName[maxnom];
                fgets(newName, maxnom, stdin);
                newName[strcspn(newName, "\n")] = 0;

                if (strlen(newName) > strlen(currentName)) {
                     printf("ERROR: El nuevo nombre es demasiado largo y corromperia otros datos. No se modifico.\n");
                     return;
                }
                strcpy(&almNom[iNom[posMod]], newName);

                break;
            case 2:
                do {
                    printf("Nueva Edad (3-6): ");
                    if (scanf("%i", &edad[posMod]) != 1) {
                        printf("ERROR, ENTRADA NO VALIDA.\n");
                        while(getchar() != '\n');
                        edad[posMod] = 0;
                        continue;
                    }
                    if (edad[posMod] < 3 || edad[posMod] > 6) {
                        printf("ERROR, EDAD NO VALIDA.\n");
                    }
                } while (edad[posMod] < 3 || edad[posMod] > 6);
                break;
            case 3:
                do {
                    printf("Nueva Estatura (cm, 30-110): ");
                    if (scanf("%i", &height[posMod]) != 1) {
                        printf("ERROR, ENTRADA NO VALIDA.\n");
                        while(getchar() != '\n');
                        height[posMod] = 0;
                        continue;
                    }
                    if (height[posMod] < 30 || height[posMod] > 110) {
                        printf("ERROR, ALTURA NO VALIDA.\n");
                    }
                } while (height[posMod] < 30 || height[posMod] > 110);
                break;
            default:
                printf("Opcion de modificacion no valida.\n");
                return;
        }
        printf("Datos modificados con exito.\n");
    } else {
        printf("Nino no encontrado.\n");
    }
}
