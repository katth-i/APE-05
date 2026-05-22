#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Clase que representa a un Estudiante y sus calificaciones
class Estudiante {
private:
    string nombre;
    double nota1, nota2, nota3;

public:
    // Constructor vacío
    Estudiante() : nombre(""), nota1(0), nota2(0), nota3(0) {}

    // Método para ingresar y validar los datos del estudiante
    void registrarEstudiante() {
        cin.ignore(); // Limpiar el búfer de entrada
        cout << "Ingrese el nombre del estudiante: ";
        getline(cin, nombre);

        // Validación para que las notas estén entre 0 y 10
        nota1 = solicitarNota("Ingrese la Nota 1 (0-10): ");
        nota2 = solicitarNota("Ingrese la Nota 2 (0-10): ");
        nota3 = solicitarNota("Ingrese la Nota 3 (0-10): ");
    }

    // Método auxiliar para validar el rango de las notas
    double solicitarNota(string mensaje) {
        double nota;
        while (true) {
            cout << mensaje;
            if (cin >> nota && nota >= 0 && nota <= 10) {
                return nota;
            }
            cout << "¡Nota invalida! Debe ser un numero entre 0 y 10.\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    // Método para calcular el promedio de las 3 notas
    double calcularPromedio() const {
        return (nota1 + nota2 + nota3) / 3.0;
    }

    // Método para determinar el estado del estudiante (Se aprueba con 7 o más)
    string determinarCondicion() const {
        return (calcularPromedio() >= 7.0) ? "Aprobado" : "Reprobado";
    }

    // Método para guardar la información directamente en el archivo de texto
    void guardarEnArchivo() const {
        // ofstream con modo ios::app para añadir datos sin borrar los anteriores
        ofstream archivo("notas.txt", ios::app);

        if (archivo.is_open()) {
            archivo << nombre << "," << nota1 << "," << nota2 << "," << nota3 << ","
                    << fixed << setprecision(2) << calcularPromedio() << "," << determinarCondicion() << "\n";
            archivo.close();
            cout << "¡Datos del estudiante guardados exitosamente en 'notas.txt'!\n";
        } else {
            cout << "Error: No se pudo abrir el archivo para guardar.\n";
        }
    }

    // Método para leer y mostrar todo el historial guardado en el archivo
    static void mostrarHistorial() {
        ifstream archivo("notas.txt");
        string linea;

        if (!archivo.is_open()) {
            cout << "No hay registros previos o el archivo no existe aun.\n";
            return;
        }

        cout << "\n================= HISTORIAL DE NOTAS =================" << endl;
        cout << left << setw(20) << "Nombre"
             << setw(8) << "N1" << setw(8) << "N2" << setw(8) << "N3"
             << setw(10) << "Promedio" << "Condicion" << endl;
        cout << "------------------------------------------------------" << endl;

        // Leer el archivo línea por línea (formato CSV simple)
        while (getline(archivo, linea)) {
            // Un procesamiento básico de cadenas para imprimir estético
            size_t pos = 0;
            string token;
            string datos[6];
            int i = 0;

            while ((pos = linea.find(',')) != string::npos && i < 5) {
                datos[i++] = linea.substr(0, pos);
                linea.erase(0, pos + 1);
            }
            datos[i] = linea; // El último elemento

            cout << left << setw(20) << datos[0]
                 << setw(8) << datos[1] << setw(8) << datos[2] << setw(8) << datos[3]
                 << setw(10) << datos[4] << datos[5] << endl;
        }
        archivo.close();
    }
};

int main() {
    int opcion;
    do {
        cout << "\n--- SISTEMA DE NOTAS ---" << endl;
        cout << "1. Registrar un nuevo estudiante" << endl;
        cout << "2. Ver historial de notas guardadas" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opcion: ";

        if (!(cin >> opcion)) {
            cout << "Opcion no valida. Intente de nuevo.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1: {
                Estudiante est;
                est.registrarEstudiante();
                est.guardarEnArchivo();
                break;
            }
            case 2:
                Estudiante::mostrarHistorial();
                break;
            case 3:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion fuera de rango." << endl;
        }
    } while (opcion != 3);

    return 0;
}
