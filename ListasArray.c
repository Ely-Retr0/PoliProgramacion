#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1. DEFINICIÓN DE ESTRUCTURAS ---

typedef struct {
    int codigoAtencion;
    char nombre[100];
    int tipoCuentahabiente; // 1:Ahorro, 2:Nomina, 3:TC, 4:Empresarial
    char tramite[100];
} Cliente;

typedef struct Nodo {
    Cliente datos;
    struct Nodo *siguiente;
} Nodo;

// --- 2. VARIABLES GLOBALES (Punteros a las listas) ---
// Usamos punteros a cabeza y cola para inserción O(1)
Nodo *listaClientes = NULL;
Nodo *colaClientes = NULL;

Nodo *listaAtendidos = NULL;
Nodo *colaAtendidos = NULL;

int codigoGlobal = 1; // Contador autoincremental para el código de atención

// --- 3. PROTOTIPOS DE FUNCIONES (Modularidad) ---

// Funciones de utilidad de la lista
int estaVacia(Nodo *lista);
Nodo* crearNodo(Cliente info);
void insertarCliente(Nodo **cabeza, Nodo **cola, Cliente info);
void liberarLista(Nodo **cabeza, Nodo **cola);

// Funciones de utilidad del programa
void mostrarMenu();
char* obtenerTipoCuenta(int tipo);
void imprimirCliente(Cliente c);
Cliente capturarCliente();
void limpiarBuffer();

// Módulos principales (Opciones del menú)
void moduloNuevoCliente();
void moduloAtenderCliente();
void moduloMostrarTodos(Nodo *lista, const char* titulo);
void moduloMostrarSiguiente();
void moduloBuscarCliente();
void moduloReportes();

// Sub-módulos (Búsqueda y Reportes)
void buscarPorNombre(Nodo *lista);
void buscarPorApellido(Nodo *lista);
void buscarPorCodigo(Nodo *lista);
void buscarPorTipo(Nodo *lista);
void reporteEstadisticas();
int contarNodos(Nodo *lista);
void contarTipos(Nodo *lista, int conteo[4]);


// --- 4. FUNCIÓN PRINCIPAL (main) ---

int main() {
    int opcion = 0;

    do {
        mostrarMenu();
        if (scanf("%d", &opcion) != 1) {
            opcion = 0; // Entrada inválida
        }
        limpiarBuffer(); // Limpia el buffer de entrada

        switch (opcion) {
            case 1:
                moduloNuevoCliente();
                break;
            case 2:
                moduloAtenderCliente();
                break;
            case 3:
                moduloMostrarTodos(listaClientes, "--- Clientes en Fila de Espera ---");
                break;
            case 4:
                moduloMostrarSiguiente();
                break;
            case 5:
                moduloBuscarCliente();
                break;
            case 6:
                moduloReportes();
                break;
            case 7:
                printf("Limpiando memoria y saliendo...\n");
                liberarLista(&listaClientes, &colaClientes);
                liberarLista(&listaAtendidos, &colaAtendidos);
                break;
            default:
                printf("\n[ERROR] Opcion no valida. Intente de nuevo.\n\n");
        }

        if (opcion != 7) {
            printf("\nPresione Enter para continuar...");
            getchar();
        }

    } while (opcion != 7);

    return 0;
}

// --- 5. IMPLEMENTACIÓN DE FUNCIONES DE UTILIDAD ---

// Limpia el buffer de entrada (stdin)
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Muestra el menú principal
void mostrarMenu() {
    system("clear || cls"); // Limpia la pantalla (compatible Windows/Linux)
    printf("==================================\n");
    printf("   SIMULADOR DE ATENCION BANCARIA\n");
    printf("==================================\n");
    printf("a) 1. Nuevo Cliente\n");
    printf("b) 2. Atender Cliente\n");
    printf("c) 3. Mostrar todos los Clientes (en espera)\n");
    printf("d) 4. Mostrar datos del siguiente Cliente\n");
    printf("e) 5. Buscar cliente (en espera)\n");
    printf("f) 6. Reporte de clientes\n");
    printf("g) 7. Salir\n");
    printf("----------------------------------\n");
    printf("Seleccione una opcion: ");
}

// Verifica si la lista está vacía (Requerimiento específico)
int estaVacia(Nodo *lista) {
    return (lista == NULL);
}

// Crea un nuevo nodo
Nodo* crearNodo(Cliente info) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("[ERROR] No hay memoria disponible.\n");
        exit(1);
    }
    nuevo->datos = info;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Inserta un cliente al final de la lista (Cola)
void insertarCliente(Nodo **cabeza, Nodo **cola, Cliente info) {
    Nodo *nuevo = crearNodo(info);

    if (estaVacia(*cabeza)) {
        *cabeza = nuevo;
        *cola = nuevo;
    } else {
        (*cola)->siguiente = nuevo;
        *cola = nuevo;
    }
}

// Libera toda la memoria de una lista
void liberarLista(Nodo **cabeza, Nodo **cola) {
    Nodo *actual = *cabeza;
    Nodo *temp;

    while (actual != NULL) {
        temp = actual;
        actual = actual->siguiente;
        free(temp);
    }

    *cabeza = NULL;
    *cola = NULL;
}

// Devuelve el string del tipo de cuenta
char* obtenerTipoCuenta(int tipo) {
    switch (tipo) {
        case 1: return "Ahorro";
        case 2: return "Nomina";
        case 3: return "Tarjeta de Credito";
        case 4: return "Empresarial";
        default: return "Desconocido";
    }
}

// Imprime los datos de un cliente
void imprimirCliente(Cliente c) {
    printf("----------------------------------\n");
    printf("Codigo de Atencion: %d\n", c.codigoAtencion);
    printf("Nombre:             %s\n", c.nombre);
    printf("Tipo Cuentahabiente: %s\n", obtenerTipoCuenta(c.tipoCuentahabiente));
    printf("Tramite a Realizar: %s\n", c.tramite);
    printf("----------------------------------\n");
}

// Solicita los datos para un nuevo cliente
Cliente capturarCliente() {
    Cliente c;
    int tipo = 0;

    printf("\n--- Nuevo Cliente ---\n");
    printf("Ingrese Nombre Completo: ");
    fgets(c.nombre, 100, stdin);
    c.nombre[strcspn(c.nombre, "\n")] = 0; // Elimina el salto de línea

    printf("Ingrese Tramite a Realizar: ");
    fgets(c.tramite, 100, stdin);
    c.tramite[strcspn(c.tramite, "\n")] = 0;

    while (tipo < 1 || tipo > 4) {
        printf("Seleccione Tipo de Cuentahabiente:\n");
        printf("  1. Ahorro\n  2. Nomina\n  3. Tarjeta de Credito\n  4. Empresarial\n");
        printf("Opcion: ");
        if (scanf("%d", &tipo) != 1) {
            tipo = 0; // Entrada inválida
        }
        limpiarBuffer();
        if (tipo < 1 || tipo > 4) {
            printf("[ERROR] Opcion de tipo invalida.\n");
        }
    }
    c.tipoCuentahabiente = tipo;

    return c;
}


// --- 6. IMPLEMENTACIÓN DE MÓDULOS DEL MENÚ ---

// a) Nuevo Cliente
void moduloNuevoCliente() {
    // Validar si la lista está vacía (aunque solo es para insertar)
    if (estaVacia(listaClientes)) {
        printf("\n(Info: La fila estaba vacia. Este sera el primer cliente.)\n");
    }

    Cliente c = capturarCliente();
    c.codigoAtencion = codigoGlobal;
    codigoGlobal++;

    insertarCliente(&listaClientes, &colaClientes, c);

    printf("\n[EXITO] Cliente '%s' agregado a la fila con el codigo: %d\n", c.nombre, c.codigoAtencion);
}

// b) Atender Cliente
void moduloAtenderCliente() {
    printf("\n--- Atender Cliente ---\n");

    if (estaVacia(listaClientes)) {
        printf("No hay clientes en la fila de espera.\n");
        return;
    }

    // 1. Apuntar al nodo a eliminar (la cabeza)
    Nodo *nodoAtendido = listaClientes;
    Cliente info = nodoAtendido->datos;

    // 2. Avanzar la cabeza de la lista de clientes
    listaClientes = listaClientes->siguiente;

    // 3. Si la lista quedó vacía, actualizar la cola
    if (estaVacia(listaClientes)) {
        colaClientes = NULL;
    }

    // 4. Mostrar datos ANTES de sacarlo (Requerimiento)
    printf("Llamando al cliente para atencion:\n");
    imprimirCliente(info);

    // 5. Agregar a la lista de atendidos
    insertarCliente(&listaAtendidos, &colaAtendidos, info);
    printf("(Cliente movido al historial de atendidos)\n");

    // 6. Liberar el nodo
    free(nodoAtendido);
}

// c) Mostrar todos los Clientes (en espera)
void moduloMostrarTodos(Nodo *lista, const char* titulo) {
    printf("\n%s\n", titulo);

    if (estaVacia(lista)) {
        printf("La lista esta vacia.\n");
        return;
    }

    Nodo *actual = lista;
    int contador = 1;
    while (actual != NULL) {
        printf("\n[Posicion en fila: %d]\n", contador);
        imprimirCliente(actual->datos);
        actual = actual->siguiente;
        contador++;
    }
}

// d) Mostrar los datos del siguiente Cliente
void moduloMostrarSiguiente() {
    printf("\n--- Siguiente Cliente en la Fila ---\n");

    if (estaVacia(listaClientes)) {
        printf("No hay clientes en la fila de espera.\n");
    } else {
        printf("El siguiente cliente a ser atendido es:\n");
        imprimirCliente(listaClientes->datos);
    }
}

// e) Buscar cliente
void moduloBuscarCliente() {
    int opcion = 0;
    if (estaVacia(listaClientes)) {
        printf("\nNo hay clientes en la fila para buscar.\n");
        return;
    }

    printf("\n--- Buscar Cliente (en Fila de Espera) ---\n");
    printf("Buscar por:\n");
    printf("  1. Nombre (coincidencia parcial)\n");
    printf("  2. Apellido Paterno (coincidencia parcial)\n");
    printf("  3. Numero de Atencion (codigo)\n");
    printf("  4. Tipo de Cuenta\n");
    printf("Opcion: ");

    if (scanf("%d", &opcion) != 1) {
        opcion = 0;
    }
    limpiarBuffer();

    switch (opcion) {
        case 1: buscarPorNombre(listaClientes); break;
        case 2: buscarPorApellido(listaClientes); break;
        case 3: buscarPorCodigo(listaClientes); break;
        case 4: buscarPorTipo(listaClientes); break;
        default: printf("[ERROR] Opcion de busqueda invalida.\n");
    }
}

// f) Reporte de clientes
void moduloReportes() {
    int opcion = 0;
    printf("\n--- Modulo de Reportes ---\n");
    printf("  1. Informe (Mostrar todos los clientes ATENDIDOS)\n");
    printf("  2. Estadisticas (Listas de atencion)\n");
    printf("Opcion: ");

    if (scanf("%d", &opcion) != 1) {
        opcion = 0;
    }
    limpiarBuffer();

    if (opcion == 1) {
        moduloMostrarTodos(listaAtendidos, "--- Informe: Clientes Atendidos Hoy ---");
    } else if (opcion == 2) {
        reporteEstadisticas();
    } else {
        printf("[ERROR] Opcion de reporte invalida.\n");
    }
}


// --- 7. IMPLEMENTACIÓN DE SUB-MÓDULOS (Búsqueda y Reportes) ---

// Funciones de búsqueda
void buscarPorNombre(Nodo *lista) {
    char busqueda[100];
    int encontrados = 0;
    printf("Ingrese el Nombre a buscar: ");
    fgets(busqueda, 100, stdin);
    busqueda[strcspn(busqueda, "\n")] = 0;

    Nodo *actual = lista;
    while (actual != NULL) {
        // strstr busca si la 'busqueda' está dentro del 'nombre'
        if (strstr(actual->datos.nombre, busqueda) != NULL) {
            imprimirCliente(actual->datos);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    printf("Se encontraron %d coincidencias.\n", encontrados);
}

// (Asumimos que el apellido está en el campo nombre)
void buscarPorApellido(Nodo *lista) {
    char busqueda[100];
    int encontrados = 0;
    printf("Ingrese el Apellido a buscar: ");
    fgets(busqueda, 100, stdin);
    busqueda[strcspn(busqueda, "\n")] = 0;

    Nodo *actual = lista;
    while (actual != NULL) {
        if (strstr(actual->datos.nombre, busqueda) != NULL) {
            imprimirCliente(actual->datos);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    printf("Se encontraron %d coincidencias.\n", encontrados);
}

void buscarPorCodigo(Nodo *lista) {
    int codigo = 0;
    int encontrados = 0;
    printf("Ingrese el Codigo de Atencion a buscar: ");
    scanf("%d", &codigo);
    limpiarBuffer();

    Nodo *actual = lista;
    while (actual != NULL) {
        if (actual->datos.codigoAtencion == codigo) {
            imprimirCliente(actual->datos);
            encontrados++;
            break; // El código es único, podemos parar
        }
        actual = actual->siguiente;
    }
    if (encontrados == 0) {
        printf("No se encontro cliente con el codigo %d.\n", codigo);
    }
}

void buscarPorTipo(Nodo *lista) {
    int tipo = 0;
    int encontrados = 0;
    printf("Seleccione Tipo de Cuentahabiente a buscar (1-4): ");
    scanf("%d", &tipo);
    limpiarBuffer();

    if (tipo < 1 || tipo > 4) {
        printf("[ERROR] Tipo invalido.\n");
        return;
    }

    Nodo *actual = lista;
    while (actual != NULL) {
        if (actual->datos.tipoCuentahabiente == tipo) {
            imprimirCliente(actual->datos);
            encontrados++;
        }
        actual = actual->siguiente;
    }
    printf("Se encontraron %d clientes de tipo '%s'.\n", encontrados, obtenerTipoCuenta(tipo));
}

// Funciones de estadísticas
int contarNodos(Nodo *lista) {
    int i = 0;
    Nodo *actual = lista;
    while (actual != NULL) {
        i++;
        actual = actual->siguiente;
    }
    return i;
}

// Cuenta cuántos clientes hay de cada tipo
void contarTipos(Nodo *lista, int conteo[4]) {
    // Índices: 0=Ahorro(1), 1=Nomina(2), 2=TC(3), 3=Empresarial(4)
    for (int i = 0; i < 4; i++) conteo[i] = 0;

    Nodo *actual = lista;
    while (actual != NULL) {
        int tipo = actual->datos.tipoCuentahabiente;
        if (tipo >= 1 && tipo <= 4) {
            conteo[tipo - 1]++; // Ajusta el índice (tipo 1 va a índice 0)
        }
        actual = actual->siguiente;
    }
}

void reporteEstadisticas() {
    printf("\n--- Estadisticas de Atencion ---\n");

    // 1. Clientes en espera
    int enEspera = contarNodos(listaClientes);
    printf("Clientes que faltan por atender (en espera): %d\n", enEspera);

    // 2. Tipos en espera
    if (enEspera > 0) {
        int conteoEspera[4];
        contarTipos(listaClientes, conteoEspera);
        printf("  - Ahorro:           %d\n", conteoEspera[0]);
        printf("  - Nomina:           %d\n", conteoEspera[1]);
        printf("  - T.C.:             %d\n", conteoEspera[2]);
        printf("  - Empresarial:      %d\n", conteoEspera[3]);
    }

    printf("\n");

    // 3. Clientes atendidos
    int atendidos = contarNodos(listaAtendidos);
    printf("Clientes que han sido atendidos: %d\n", atendidos);

    // 4. Tipos atendidos
    if (atendidos > 0) {
        int conteoAtendidos[4];
        contarTipos(listaAtendidos, conteoAtendidos);
        printf("  - Ahorro:           %d\n", conteoAtendidos[0]);
        printf("  - Nomina:           %d\n", conteoAtendidos[1]);
        printf("  - T.C.:             %d\n", conteoAtendidos[2]);
        printf("  - Empresarial:      %d\n", conteoAtendidos[3]);
    }
}
