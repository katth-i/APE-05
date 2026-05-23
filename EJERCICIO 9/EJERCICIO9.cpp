#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Producto {
private:
    string nombre;
    int cantidad;
    double precio, total;
public:
    void setDatos(string n, int c, double p) {
        nombre = n; cantidad = c; precio = p;
        calcularTotal();
    }
    void calcularTotal() { total = cantidad * precio; }
    string getNombre()   { return nombre; }
    int    getCantidad() { return cantidad; }
    double getPrecio()   { return precio; }
    double getTotal()    { return total; }
};

void registrarVenta(Producto& p) {
    string nombre; int cantidad; double precio;
    cout << "Producto: "; getline(cin, nombre);
    cout << "Cantidad: "; cin >> cantidad;
    cout << "Precio unitario: "; cin >> precio; cin.ignore();
    p.setDatos(nombre, cantidad, precio);
    ofstream archivo("ventas.txt", ios::app);
    archivo << nombre << "|" << cantidad << "|"
            << precio << "|" << p.getTotal() << endl;
    archivo.close();
    cout << "Total: $" << p.getTotal() << endl;
}

void generarFactura(Producto& p) {
    cout << "======= FACTURA =======" << endl;
    cout << "Producto : " << p.getNombre() << endl;
    cout << "Cantidad : " << p.getCantidad() << endl;
    cout << fixed << setprecision(2);
    cout << "Precio   : $" << p.getPrecio() << endl;
    cout << "TOTAL    : $" << p.getTotal() << endl;
    cout << "=======================" << endl;
}

void mostrarHistorial() {
    ifstream archivo("ventas.txt");
    string linea;
    cout << "=== HISTORIAL DE VENTAS ===" << endl;
    while (getline(archivo, linea)) cout << linea << endl;
    archivo.close();
}

int main() {
    Producto p;
    int opcion;
    do {
        cout << "1.Registrar 2.Factura 3.Historial 4.Salir: ";
        cin >> opcion; cin.ignore();
        if      (opcion == 1) registrarVenta(p);
        else if (opcion == 2) generarFactura(p);
        else if (opcion == 3) mostrarHistorial();
    } while (opcion != 4);
    return 0;
}

