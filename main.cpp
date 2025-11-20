#include <iostream>
#include "Red.h"
using namespace std;

int main() {
    Red red;
    char opcion = ' '; // Inicializar para que entre al do-while

    do {
        cout << "\n**** ENRUTADORES ****\n";
        cout << "1. Agregar enrutador\n";
        cout << "2. Eliminar enrutador\n";
        cout << "3. Agregar conexion\n";
        cout << "4. Cargar desde archivo\n";
        cout << "5. Crear red aleatoria\n";
        cout << "6. Calcular rutas\n";
        cout << "7. Mostrar tabla completa\n";
        cout << "8. Mostrar tabla individual\n";
        cout << "9. Mostrar camino\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";

        // Leer la opción. Usar cin >> opcion para leer un solo carácter.
        if (!(cin >> opcion)) {
            cout << "Entrada invalida. Saliendo...\n";
            break;
        }

        switch(opcion) {
        case '1': {
            string nombre;
            cout << "Nombre: ";
            cin >> nombre;
            red.agregarEnrutador(nombre);
            break;
        }
        case '2': {
            string nombre;
            cout << "Eliminar: ";
            cin >> nombre;
            red.eliminarEnrutador(nombre);
            break;
        }
        case '3': {
            string origen, destino;
            int costo;
            cout << "Origen: "; cin >> origen;
            cout << "Destino: "; cin >> destino;
            cout << "Costo: ";

            if (cin >> costo) {
                red.agregarConexion(origen, destino, costo);
                red.calcularRutas();
            } else {
                // Manejar error de entrada (si el usuario ingresa un no-entero)
                cout << "Costo invalido. Intente de nuevo.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        }
        case '4': {
            string archivo;
            cout << "Archivo: ";
            cin >> archivo;
            red.cargarDesdeArchivo(archivo);
            break;
        }
        case '5': {
            int r, c;
            cout << "Routers: ";
            if (!(cin >> r)) {
                cout << "Entrada invalida.\n"; break;
            }
            cout << "Conexiones: ";
            if (!(cin >> c)) {
                cout << "Entrada invalida.\n"; break;
            }
            red.crearRedAleatoria(r, c);
            break;
        }
        case '6': red.calcularRutas(); break;
        case '7': red.imprimirTodasLasTablas(); break;
        case '8': {
            string nombre;
            cout << "Router: "; cin >> nombre;
            red.imprimirTablaIndividual(nombre);
            break;
        }
        case '9': {
            string o, d;
            cout << "Origen: "; cin >> o;
            cout << "Destino: "; cin >> d;
            red.imprimirCamino(o, d);
            break;
        }
        case '0':
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
            break;
        }

        // Limpiar el buffer de entrada para evitar problemas en el siguiente bucle
        if (opcion != '0') {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    } while(opcion != '0');

    return 0;
}
