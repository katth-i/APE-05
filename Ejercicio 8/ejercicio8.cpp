#include    <iostream>
#include    <fstream>
using namespace std;    

class Libro {
private:
    string codigo;
    string titulo;
    string autor;
    string estado; // Disponible o Prestado

public:
    // Ingresar datos
    void ingresarDatos() {
        cin.ignore();

        cout << "Ingrese el código del libro: ";
        getline(cin, codigo);

        cout << "Ingrese el título: ";
        getline(cin, titulo);

        cout << "Ingrese el autor: ";
        getline(cin, autor);

        cout << "Ingrese el estado (Disponible/Prestado): ";
        getline(cin, estado);
    }

    // Guardar en archivo
    void guardarArchivo() {
        ofstream archivo("informacionlibros.txt", ios::app);

        if (archivo.is_open()) {
            archivo << codigo << ";"
                    << titulo << ";"
                    << autor << ";"
                    << estado << endl;
            archivo.close();
        }
    }

    // Buscar libro por código
    static void buscarLibro(string codigoBuscar) {
        ifstream archivo("informacionlibros.txt");
        string codigo, titulo, autor, estado;
        bool encontrado = false;

        while (getline(archivo, codigo, ';')) {
            getline(archivo, titulo, ';');
            getline(archivo, autor, ';');
            getline(archivo, estado);

            if (codigo == codigoBuscar) {
                cout << "\nLibro encontrado:\n";
                cout << "Código: " << codigo << endl;
                cout << "Título: " << titulo << endl;
                cout << "Autor: " << autor << endl;
                cout << "Estado: " << estado << endl;
                encontrado = true;
                break;
            }
        }

        if (!encontrado) {
            cout << "Libro no encontrado.\n";
        }

        archivo.close();
    }

    // Mostrar por estado
    static void mostrarPorEstado(string estadoBuscar) {
        ifstream archivo("informacionlibros.txt");
        string codigo, titulo, autor, estado;

        cout << "\nLibros " << estadoBuscar << ":\n";

        while (getline(archivo, codigo, ';')) {
            getline(archivo, titulo, ';');
            getline(archivo, autor, ';');
            getline(archivo, estado);

            if (estado == estadoBuscar) {
                cout << "Código: " << codigo
                     << " | Título: " << titulo
                     << " | Autor: " << autor << endl;
            }
        }

        archivo.close();
    }
};
int main() {
    Libro libro;    
    int opcion;
    string codigoBuscar;

    do {
        cout << "\n=== Sistema de Gestión de Biblioteca ===\n";
        cout << "1. Ingresar nuevo libro\n";
        cout << "2. Buscar libro por código\n";
        cout << "3. Mostrar libros disponibles\n";
        cout << "4. Mostrar libros prestados\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                libro.ingresarDatos();
                libro.guardarArchivo();
                break;
            case 2: {
                cout << "Ingrese el código del libro a buscar: ";
                getline(cin, codigoBuscar);
                Libro::buscarLibro(codigoBuscar);
                break;
            }
            case 3:
                Libro::mostrarPorEstado("Disponible");
                break;
            case 4:
                Libro::mostrarPorEstado("Prestado");
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida. Intente nuevamente.\n";
        }
    } while (opcion != 5);

    return 0;
}
