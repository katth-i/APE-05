#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// Clase que representa la entidad Producto
class Producto {
private:
    int id;
    string nombre;
    int cantidad;
    double precio;

public:
    // Constructores
    Producto() : id(0), nombre(""), cantidad(0), precio(0.0) {}
    Producto(int _id, string _nombre, int _cant, double _prec) 
        : id(_id), nombre(_nombre), cantidad(_cant), precio(_prec) {}

    // Getters y Setters
    int getId() const { return id; }
    string getNombre() const { return nombre; }
    int getCantidad() const { return cantidad; }
    double getPrecio() const { return precio; }

    void setNombre(string n) { nombre = n; }
    void setCantidad(int c) { cantidad = c; }
    void setPrecio(double p) { precio = p; }

    // Muestra los datos de este producto en formato de fila
    void mostrarFila() const {
        cout << left << setw(8) << id 
             << setw(25) << nombre 
             << setw(12) << cantidad 
             << "$" << fixed << setprecision(2) << precio << endl;
    }
};

// Clase controladora que gestiona el CRUD y la persistencia
class GestorInventario {
private:
    vector<Producto> inventario;
    const string nombreArchivo = "inventario.txt";

    // Método privado para guardar todo el vector actual en el archivo txt
    void actualizarArchivo() {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            for (const auto& prod : inventario) {
                archivo << prod.getId() << "|" 
                        << prod.getNombre() << "|" 
                        << prod.getCantidad() << "|" 
                        << prod.getPrecio() << "\n";
            }
            archivo.close();
        }
    }

public:
    // Al instanciarse el gestor, carga automáticamente los datos existentes
    GestorInventario() {
        cargarDesdeArchivo();
    }

    // C (Create) - Registrar Producto
    void crearProducto() {
        int id, cantidad;
        string nombre;
        double precio;

        cout << "\n--- Registrar Nuevo Producto ---" << endl;
        
        // Validación de ID único
        while (true) {
            cout << "Ingrese ID numérico: ";
            if (cin >> id) {
                if (buscarPorId(id) == -1) break;
                cout << "Error: Ese ID ya se encuentra registrado.\n";
            } else {
                cout << "Entrada inválida. Ingrese solo números.\n";
                cin.clear(); cin.ignore(10000, '\n');
            }
        }

        cin.ignore();
        cout << "Ingrese nombre del producto: ";
        getline(cin, nombre);

        // Validación de cantidad
        while (true) {
            cout << "Ingrese cantidad en stock: ";
            if (cin >> cantidad && cantidad >= 0) break;
            cout << "Cantidad inválida. Intente de nuevo.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        // Validación de precio
        while (true) {
            cout << "Ingrese precio unitario: ";
            if (cin >> precio && precio >= 0) break;
            cout << "Precio inválido. Intente de nuevo.\n";
            cin.clear(); cin.ignore(10000, '\n');
        }

        // Añadir al contenedor y sincronizar con el archivo
        inventario.push_back(Producto(id, nombre, cantidad, precio));
        actualizarArchivo();
        cout << "¡Producto registrado y guardado con éxito!\n";
    }

    // R (Read) - Listar todos los productos
    void leerProductos() const {
        if (inventario.empty()) {
            cout << "\nEl inventario está vacío actualmente.\n";
            return;
        }

        cout << "\n==================== INVENTARIO GENERAL ====================" << endl;
        cout << left << setw(8) << "ID" << setw(25) << "Nombre" << setw(12) << "Cantidad" << "Precio" << endl;
        cout << "------------------------------------------------------------" << endl;
        for (const auto& prod : inventario) {
            prod.mostrarFila();
        }
        cout << "============================================================" << endl;
    }

    // U (Update) - Modificar un producto existente
    void actualizarProducto() {
        int id;
        cout << "\nIngrese el ID del producto que desea modificar: ";
        cin >> id;

        int indice = buscarPorId(id);
        if (indice == -1) {
            cout << "No se encontró ningún producto con el ID especificado.\n";
            return;
        }

        cin.ignore();
        string nuevoNombre;
        int nuevaCantidad;
        double nuevoPrecio;

        cout << "Producto encontrado: " << inventario[indice].getNombre() << "\n";
        cout << "Ingrese nuevo nombre (o presione Enter para mantener actual): ";
        getline(cin, nuevoNombre);
        if (!nuevoNombre.empty()) {
            inventario[indice].setNombre(nuevoNombre);
        }

        cout << "Ingrese nueva cantidad (Número negativo para mantener actual): ";
        if (cin >> nuevaCantidad && nuevaCantidad >= 0) {
            inventario[indice].setCantidad(nuevaCantidad);
        }

        cout << "Ingrese nuevo precio (Número negativo para mantener actual): ";
        if (cin >> nuevoPrecio && nuevoPrecio >= 0) {
            inventario[indice].setPrecio(nuevoPrecio);
        }

        actualizarArchivo();
        cout << "¡Producto actualizado correctamente en la base de datos!\n";
    }

    // D (Delete) - Eliminar un producto
    void eliminarProducto() {
        int id;
        cout << "\nIngrese el ID del producto que desea eliminar: ";
        cin >> id;

        int indice = buscarPorId(id);
        if (indice == -1) {
            cout << "Error: ID no encontrado.\n";
            return;
        }

        // Eliminar del vector utilizando iteradores
        inventario.erase(inventario.begin() + indice);
        actualizarArchivo();
        cout << "¡Producto eliminado exitosamente del registro de archivos!\n";
    }

    // Método auxiliar de búsqueda (Retorna el índice en el vector o -1)
    int buscarPorId(int id) const {
        for (size_t i = 0; i < inventario.size(); ++i) {
            if (inventario[i].getId() == id) {
                return i; // Encontrado
            }
        }
        return -1; // No existe
    }

    // Recupera la información del archivo .txt al arrancar la aplicación
    void cargarDesdeArchivo() {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) return; // Si no existe el archivo todavía, no hace nada

        inventario.clear();
        string linea;
        while (getline(archivo, linea)) {
            size_t p1 = linea.find('|');
            size_t p2 = linea.find('|', p1 + 1);
            size_t p3 = linea.find('|', p2 + 1);

            if (p1 != string::npos && p2 != string::npos && p3 != string::npos) {
                int id = stoi(linea.substr(0, p1));
                string nombre = linea.substr(p1 + 1, p2 - p1 - 1);
                int cant = stoi(linea.substr(p2 + 1, p3 - p2 - 1));
                double prec = stod(linea.substr(p3 + 1));

                inventario.push_back(Producto(id, nombre, cant, prec));
            }
        }
        archivo.close();
    }
};

int main() {
    GestorInventario gestor;
    int opcion;

    do {
        cout << "\n--- MINI PROYECTO: CONTROL DE INVENTARIO ---" << endl;
        cout << "1. [C] Registrar Producto" << endl;
        cout << "2. [R] Mostrar Catálogo Completo" << endl;
        cout << "3. [U] Actualizar Datos de Producto" << endl;
        cout << "4. [D] Eliminar Producto" << endl;
        cout << "5. Salir del Sistema" << endl;
        cout << "Elija una opción (1-5): ";
        
        if (!(cin >> opcion)) {
            cout << "Entrada inválida. Por favor, digite un número.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (opcion) {
            case 1: gestor.crearProducto(); break;
            case 2: gestor.leerProductos(); break;
            case 3: gestor.actualizarProducto(); break;
            case 4: gestor.eliminarProducto(); break;
            case 5: cout << "Guardando cambios y cerrando sesión..." << endl; break;
            default: cout << "Opción inválida. Intente dentro del rango dinámico.\n";
        }
    } while (opcion != 5);

    return 0;
}