#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Cajero {
private:
    string usuario;
    double saldo;

public:
    Cajero() {
        saldo = 0;
    }

    void registrarUsuario() {
        cout << "Ingrese nombre del usuario: ";
        cin.ignore();
        getline(cin, usuario);
        saldo = 0;
        guardarDatos();
    }

    void cargarDatos() {
        ifstream archivo("cajero.txt");

        if (archivo.is_open()) {
            getline(archivo, usuario);
            archivo >> saldo;
            archivo.close();
        } else {
            cout << "No existe cuenta registrada.\n";
            registrarUsuario();
        }
    }

    void guardarDatos() {
        ofstream archivo("cajero.txt");

        archivo << usuario << endl;
        archivo << saldo;

        archivo.close();
    }

    void mostrarUsuario() {
        cout << "\nUsuario: " << usuario << endl;
    }

    void consultarSaldo() {
        cout << "Saldo actual: $" << saldo << endl;
    }

    void depositar() {
        double monto;

        cout << "Monto a depositar: ";
        cin >> monto;

        if (monto > 0) {
            saldo += monto;
            guardarDatos();
            cout << "Deposito realizado.\n";
        } else {
            cout << "Monto invalido.\n";
        }
    }

    void retirar() {
        double monto;

        cout << "Monto a retirar: ";
        cin >> monto;

        if (monto > saldo) {
            cout << "Saldo insuficiente.\n";
        } else if (monto <= 0) {
            cout << "Monto invalido.\n";
        } else {
            saldo -= monto;
            guardarDatos();
            cout << "Retiro realizado.\n";
        }
    }
};

int main() {

    Cajero cuenta;
    cuenta.cargarDatos();

    int opcion;

    do {
        cout << "\n===== CAJERO AUTOMATICO =====\n";

        cuenta.mostrarUsuario();

        cout << "1. Consultar saldo\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Retirar dinero\n";
        cout << "4. Salir\n";
        cout << "Seleccione: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cuenta.consultarSaldo();
                break;

            case 2:
                cuenta.depositar();
                break;

            case 3:
                cuenta.retirar();
                break;

            case 4:
                cout << "Gracias por usar el cajero.\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 4);

    return 0;
}
