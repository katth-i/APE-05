#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Clase GestorEstudiantes
class GestorEstudiantes {
private:
    string archivo = "estudiantes.txt";

public:

    // Método para leer y mostrar estudiantes
    void mostrarRegistros() {

        ifstream file(archivo);

        if (!file.is_open()) {
            cout << "No existe el archivo de estudiantes." << endl;
            return;
        }

        string linea;

        string estudiantes[100][4];
        int contador = 0;

        double sumaPromedios = 0;
        double promedioGeneral = 0;

        cout << "\n========= LISTA DE ESTUDIANTES =========" << endl;

        cout << left
             << setw(15) << "Cedula"
             << setw(20) << "Nombre"
             << setw(20) << "Carrera"
             << setw(10) << "Promedio"
             << endl;

        cout << "--------------------------------------------------------------" << endl;

        // Lectura línea por línea
        while (getline(file, linea)) {

            string datos[4];
            size_t pos = 0;
            int i = 0;

            // Separar por delimitador |
            while ((pos = linea.find('|')) != string::npos && i < 3) {
                datos[i++] = linea.substr(0, pos);
                linea.erase(0, pos + 1);
            }

            datos[i] = linea;

            // Guardar en arreglo
            for (int j = 0; j < 4; j++) {
                estudiantes[contador][j] = datos[j];
            }

            // Mostrar datos
            cout << left
                 << setw(15) << estudiantes[contador][0]
                 << setw(20) << estudiantes[contador][1]
                 << setw(20) << estudiantes[contador][2]
                 << setw(10) << estudiantes[contador][3]
                 << endl;

            // Contar estudiantes
            contador++;

            // Acumular promedio
            sumaPromedios += stod(datos[3]);
        }

        file.close();

        // Calcular promedio general
        if (contador > 0) {
            promedioGeneral = sumaPromedios / contador;
        }

        cout << "\nTotal de estudiantes registrados: "
             << contador << endl;

        cout << "Promedio general: "
             << fixed << setprecision(2)
             << promedioGeneral << endl;
    }
};

int main() {

    GestorEstudiantes gestor;

    gestor.mostrarRegistros();

    return 0;
}
