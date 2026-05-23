#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void agregarContacto(string nombre, string telefono, string correo) {
    ofstream archivo("agenda.txt", ios::app);
    archivo << nombre << "|" << telefono << "|" << correo << endl;
    archivo.close();
    cout << "Contacto guardado." << endl;
}

void buscarContacto(string nombre) {
    ifstream archivo("agenda.txt");
    string linea, n, t, c;
    bool encontrado = false;
    while (getline(archivo, linea)) {
        int p1 = linea.find("|"), p2 = linea.rfind("|");
        n = linea.substr(0, p1);
        t = linea.substr(p1+1, p2-p1-1);
        c = linea.substr(p2+1);
        if (n == nombre) {
            cout << "Tel: " << t << " | Correo: " << c << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "Contacto no encontrado." << endl;
    archivo.close();
}

void mostrarTodos() {
    ifstream archivo("agenda.txt");
    string linea;
    cout << "=== TODOS LOS CONTACTOS ===" << endl;
    while (getline(archivo, linea)) cout << linea << endl;
    archivo.close();
}

int main() {
    int opcion;
    string nombre, telefono, correo;
    do {
        cout << "1.Agregar 2.Buscar 3.Mostrar 4.Salir: ";
        cin >> opcion; cin.ignore();
        if (opcion == 1) {
            cout << "Nombre: "; getline(cin, nombre);
            cout << "Telefono: "; getline(cin, telefono);
            cout << "Correo: "; getline(cin, correo);
            agregarContacto(nombre, telefono, correo);
        } else if (opcion == 2) {
            cout << "Buscar: "; getline(cin, nombre);
            buscarContacto(nombre);
        } else if (opcion == 3) {
            mostrarTodos();
        }
    } while (opcion != 4);
    return 0;
}
