#include <iostream>
#include <string>
#include <iomanip>

// Constantes
const int CAPACIDAD_INICIAL = 50;

// Función para duplicar el tamaño de los arreglos dinámicos
void duplicar(
    int*& ids, float*& pesos, std::string*& destinos, int*& prioridades, char*& estados,
    int capacidad, int total_paquetes
) {
    int nueva_capacidad = capacidad * 2;

    int* nuevo_ids = new int[nueva_capacidad];
    float* nuevo_pesos = new float[nueva_capacidad];
    std::string* nuevo_destinos = new std::string[nueva_capacidad];
    int* nuevo_prioridades = new int[nueva_capacidad];
    char* nuevo_estados = new char[nueva_capacidad];

    // Copiar los valores anteriores
    for (int i = 0; i < total_paquetes; ++i) {
        nuevo_ids[i] = ids[i];
        nuevo_pesos[i] = pesos[i];
        nuevo_destinos[i] = destinos[i];
        nuevo_prioridades[i] = prioridades[i];
        nuevo_estados[i] = estados[i];
    }

    // Liberar memoria vieja
    delete[] ids; 
    delete[] pesos; 
    delete[] destinos; 
    delete[] prioridades; 
    delete[] estados;

    // Asignar nuevas referencias
    ids = nuevo_ids;
    pesos = nuevo_pesos;
    destinos = nuevo_destinos;
    prioridades = nuevo_prioridades;
    estados = nuevo_estados;
}

std::string prioridad_to_string(int p) {
    if (p == 1) return "Alta";
    if (p == 2) return "Media";
    if (p == 3) return "Baja";
    return "Desconocida";
}

int main() {
    int capacidad = CAPACIDAD_INICIAL;
    int* ids = new int[capacidad];
    float* pesos = new float[capacidad];
    std::string* destinos = new std::string[capacidad];
    int* prioridades = new int[capacidad];
    char* estados = new char[capacidad];

    int inicio_cola = 0; // Índice lógico del frente de la cola
    int fin_cola = 0;    // Límite lógico de la cola (es el total de paquetes registrados)

    bool salir = false;
    int opcion;

    std::cout << "--- Sistema de Despacho Logístico MegaEnvío (Modo Punteros) ---" << std::endl;
    std::cout << "Inicializando sistema con capacidad para " << capacidad << " paquetes..." << std::endl;

    while (!salir) {
        std::cout << "\nCapacidad actual: " << capacidad << ". Paquetes en cola: " << (fin_cola - inicio_cola) << "." << std::endl;
        std::cout << "\nSeleccione una operación:\n"
                     "1. Agregar Paquete (Encolar)\n"
                     "2. Despachar Paquete (Desencolar)\n"
                     "3. Inspeccionar Frente de Cola\n"
                     "4. Reporte por Destino\n"
                     "5. Salir (Liberar Memoria)\n";
        std::cout << "Opción seleccionada: ";
        std::cin >> opcion;

        if (opcion == 1) { // Encolar
            if (fin_cola >= capacidad) {
                duplicar(ids, pesos, destinos, prioridades, estados, capacidad, fin_cola);
                capacidad *= 2;
            }
            std::cout << "Ingrese ID: ";
            std::cin >> ids[fin_cola];
            std::cout << "Ingrese Peso (kg): ";
            std::cin >> pesos[fin_cola];
            std::cin.ignore();
            std::cout << "Ingrese Destino: ";
            std::getline(std::cin, destinos[fin_cola]);
            do {
                std::cout << "Ingrese Prioridad (1=Alta, 2=Media, 3=Baja): ";
                std::cin >> prioridades[fin_cola];
            } while (prioridades[fin_cola] < 1 || prioridades[fin_cola] > 3);

            estados[fin_cola] = 'E';
            std::cout << "Paquete " << ids[fin_cola] << " encolado. Capacidad utilizada: "
                      << (fin_cola - inicio_cola + 1) << "/" << capacidad << "." << std::endl;
            fin_cola++;
        } else if (opcion == 2) { // Desencolar
            if (inicio_cola == fin_cola) {
                std::cout << "No hay paquetes encola." << std::endl;
            } else {
                std::cout << "Despachando paquete..." << std::endl;
                estados[inicio_cola] = 'D';
                std::cout << "Paquete " << ids[inicio_cola] << " despachado con éxito. Estado: 'D'." << std::endl;
                inicio_cola++;
            }
        } else if (opcion == 3) { // Inspeccionar frente de cola
            if (inicio_cola == fin_cola) {
                std::cout << "No hay paquetes en la cola." << std::endl;
            } else {
                std::cout << "Frente de la cola:" << std::endl;
                std::cout << "  ID: " << ids[inicio_cola]
                          << " | Peso: " << std::fixed << std::setprecision(2) << pesos[inicio_cola] << " kg"
                          << " | Destino: " << destinos[inicio_cola]
                          << " | Prioridad: " << prioridad_to_string(prioridades[inicio_cola])
                          << std::endl;
            }
        } else if (opcion == 4) { // Reporte por destino
            std::string destino_buscado;
            std::cin.ignore();
            std::cout << "Ingrese el destino para el reporte: ";
            std::getline(std::cin, destino_buscado);

            int cantidad = 0;
            float suma_peso = 0;
            for (int i = inicio_cola; i < fin_cola; ++i) {
                if (estados[i] == 'E' && destinos[i] == destino_buscado) {
                    cantidad++;
                    suma_peso += pesos[i];
                }
            }
            std::cout << "Reporte para destino '" << destino_buscado << "':" << std::endl;
            std::cout << "  Paquetes En Cola: " << cantidad << std::endl;
            if (cantidad > 0) {
                std::cout << "  Peso Promedio: " << std::fixed << std::setprecision(2)
                          << (suma_peso / cantidad) << " kg" << std::endl;
            } else {
                std::cout << "  Peso Promedio: 0.00 kg" << std::endl;
            }
        } else if (opcion == 5) { // Salir
            std::cout << "Liberando " << capacidad << " bloques de memoria asignada..." << std::endl;
            delete[] ids;
            delete[] pesos;
            delete[] destinos;
            delete[] prioridades;
            delete[] estados;
            std::cout << "Sistema cerrado. ¡Memoria libre!" << std::endl;
            salir = true;
        } else {
            std::cout << "Opción no válida." << std::endl;
        }
    }
    return 0;
}
