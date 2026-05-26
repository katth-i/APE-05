#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Clase Producto
class Producto {
private:
    string codigo;
    string nombre;
    int cantidad;
    float precio;

public:
    // Constructor
    Producto() {
        codigo = "";
        nombre = "";
        cantidad = 0;
        precio = 0.0;
    }

    // Método para ingresar datos
    void ingresarDatos() {
        cin.ignore();

        cout << "Ingrese el código del producto: ";
        getline(cin, codigo);

        cout << "Ingrese el nombre del producto: ";
        getline(cin, nombre);

        cout << "Ingrese la cantidad: ";
        cin >> cantidad;

        cout << "Ingrese el precio unitario: $";
        cin >> precio;
    }

    // Método para mostrar datos
    void mostrarDatos() {
        cout << left << setw(12) << codigo
             << setw(20) << nombre
             << setw(10) << cantidad
             << "$" << fixed << setprecision(2) << precio
             << endl;
    }

    // Método para calcular valor total del producto
    float calcularValor() {
        return cantidad * precio;
    }

    // Método para guardar en archivo
    void guardarEnArchivo() {
        ofstream archivo("inventario.txt", ios::app);

        if (archivo.is_open()) {
            archivo << codigo << ";"
                    << nombre << ";"
                    << cantidad << ";"
                    << precio << ";"
                    << calcularValor() << endl;
            archivo.close();
        } else {
            cout << "Error al abrir el archivo." << endl;
        }
    }
};

int main() {
    int n;
    float valorTotalInventario = 0.0;

    cout << "==========================================" << endl;
    cout << "      SISTEMA DE REGISTRO DE PRODUCTOS    " << endl;
    cout << "==========================================" << endl;

    cout << "¿Cuántos productos desea registrar?: ";
    cin >> n;

    // Arreglo dinámico de objetos
    Producto* productos = new Producto[n];

    // Ingreso de datos
    for (int i = 0; i < n; i++) {
        cout << "\n--- Producto " << (i + 1) << " ---" << endl;
        productos[i].ingresarDatos();
        productos[i].guardarEnArchivo();
        valorTotalInventario += productos[i].calcularValor();
    }

    // Mostrar productos registrados
    cout << "\n==========================================" << endl;
    cout << "         PRODUCTOS REGISTRADOS            " << endl;
    cout << "==========================================" << endl;

    cout << left << setw(12) << "Código"
         << setw(20) << "Nombre"
         << setw(10) << "Cantidad"
         << "Precio" << endl;

    for (int i = 0; i < n; i++) {
        productos[i].mostrarDatos();
    }

    // Mostrar valor total del inventario
    cout << "\n==========================================" << endl;
    cout << "Valor total del inventario: $"
         << fixed << setprecision(2) // esto ayuda a que el valor se muestre con 2 decimales 
         << valorTotalInventario << endl;
    cout << "==========================================" << endl;

    // Liberar memoria
    delete[] productos;

    return 0;
}