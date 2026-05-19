#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <sstream>

using namespace std;

// ESTRUCTURAS

struct Ingrediente
{
    string nombre;
};

struct Menu
{
    string nombre;
    double precio;
    int stock;
    vector<Ingrediente> ing;
    int cantIng;
};

// FUNCIONES DE VENTAS D/A/C

void ventaDesayuno(vector<Menu> &desayunos, int eleccion)
{
    if (eleccion > 0 && eleccion <= desayunos.size())
    {
        int idx = eleccion - 1;
        if (desayunos[idx].stock > 0)
        {
            desayunos[idx].stock--;
            cout << "Venta exitosa de: " << desayunos[idx].nombre << endl;
        }
        else
        {
            cout << "Lo sentimos, el menu " << desayunos[idx].nombre << " se ha agotado" << endl;
        }
    }
    else
    {
        cout << "Opcion de plato invalida." << endl;
    }
}

void ventaAlmuerzo(vector<Menu> &almuerzos, int eleccion)
{
    if (eleccion > 0 && eleccion <= almuerzos.size())
    {
        int idx = eleccion - 1;
        if (almuerzos[idx].stock > 0)
        {
            almuerzos[idx].stock--;
            cout << "Venta exitosa de: " << almuerzos[idx].nombre << endl;
        }
        else
        {
            cout << "Lo sentimos, el menu " << almuerzos[idx].nombre << " se ha agotado" << endl;
        }
    }
    else
    {
        cout << "Opcion de plato invalida." << endl;
    }
}

void ventaCena(vector<Menu> &cenas, int eleccion)
{
    if (eleccion > 0 && eleccion <= cenas.size())
    {
        int idx = eleccion - 1;
        if (cenas[idx].stock > 0)
        {
            cenas[idx].stock--;
            cout << "Venta exitosa de: " << cenas[idx].nombre << endl;
        }
        else
        {
            cout << "Lo sentimos, el menu " << cenas[idx].nombre << " se ha agotado" << endl;
        }
    }
    else
    {
        cout << "Opcion de plato invalida." << endl;
    }
}


// FUNCIONES/PROCESOS

void pause()
{
    cout << "\n\nPresiona ENTER para salir...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void cargarDatos(string nombreArchivo, vector<Menu> &menus)
{
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    int cantidadMenus;
    archivo >> cantidadMenus;
    archivo.ignore(numeric_limits<streamsize>::max(), '\n');

    menus.clear();

    for (int i = 0; i < cantidadMenus; i++)
    {
        Menu nuevoMenu;
        string linea;

        getline(archivo, linea);

        stringstream ss(linea);

        vector<string> palabras;
        string palabra;

        while (ss >> palabra)
        {
            palabras.push_back(palabra);
        }

        nuevoMenu.cantIng = stoi(palabras[palabras.size() - 1]);
        nuevoMenu.stock = stoi(palabras[palabras.size() - 2]);
        nuevoMenu.precio = stod(palabras[palabras.size() - 3]);

        nuevoMenu.nombre = "";

        for (size_t j = 0; j < palabras.size() - 3; j++)
        {
            nuevoMenu.nombre += palabras[j];

            if (j < palabras.size() - 4)
            {
                nuevoMenu.nombre += " ";
            }
        }

        for (int j = 0; j < nuevoMenu.cantIng; j++)
        {
            Ingrediente nuevoIngrediente;
            getline(archivo, nuevoIngrediente.nombre);
            nuevoMenu.ing.push_back(nuevoIngrediente);
        }

        menus.push_back(nuevoMenu);
    }

    archivo.close();
}

// MAIN (Tu estructura base original sin alterar)
int main()
{
    vector<Menu> desayunos;
    vector<Menu> almuerzos;
    vector<Menu> cenas;

    int option;
    int eleccion;

    cout << "Bienvenido al punto de venta de la Cafeteria 'Alimentos y mas'" << endl;
    cout << "Por favor seleccione una de las siguientes opciones del 1 al 4: " << endl;
    cout << "1. Venta de Desayuno" << endl;
    cout << "2. Venta de Almuerzo" << endl;
    cout << "3. Venta de Cena" << endl;
    cout << "4. Cerrar Caja Y salir" << endl;
    cout << "*****************************************************************" << endl;
    cin >> option;
    switch (option)
    {
    case 1:
        cargarDatos("Archivos/desayuno.txt", desayunos);

        for (size_t i = 0; i < desayunos.size(); i++)
        {
            cout << i + 1 << ". " << desayunos[i].nombre << " - Q" << desayunos[i].precio << endl;
            cout << "Stock: " << desayunos[i].stock << endl;
            cout << "Ingredientes:" << endl;

            for (size_t j = 0; j < desayunos[i].ing.size(); j++)
            {
                cout << "- " << desayunos[i].ing[j].nombre << endl;
            }

            cout << endl;
        }

        // Bloque original para pedir el plato y llamar a su funci n externa
        cout << "Elija el numero de plato que desea comprar: ";
        cin >> eleccion;
        ventaDesayuno(desayunos, eleccion);
        break;

    case 2:
        cargarDatos("Archivos/almuerzo.txt", almuerzos);

        for (size_t i = 0; i < almuerzos.size(); i++)
        {
            cout << i + 1 << ". " << almuerzos[i].nombre << " - Q" << almuerzos[i].precio << endl;
            cout << "Stock: " << almuerzos[i].stock << endl;
            cout << "Ingredientes:" << endl;

            for (size_t j = 0; j < almuerzos[i].ing.size(); j++)
            {
                cout << "- " << almuerzos[i].ing[j].nombre << endl;
            }

            cout << endl;
        }

        // Bloque original para pedir el plato y llamar a su funci n externa
        cout << "Elija el numero de plato que desea comprar: ";
        cin >> eleccion;
        ventaAlmuerzo(almuerzos, eleccion);
        break;

    case 3:
        cargarDatos("Archivos/cena.txt", cenas);

        for (size_t i = 0; i < cenas.size(); i++)
        {
            cout << i + 1 << ". " << cenas[i].nombre << " - Q" << cenas[i].precio << endl;
            cout << "Stock: " << cenas[i].stock << endl;
            cout << "Ingredientes:" << endl;

            for (size_t j = 0; j < cenas[i].ing.size(); j++)
            {
                cout << "- " << cenas[i].ing[j].nombre << endl;
            }

            cout << endl;
        }

        // Bloque original para pedir el plato y llamar a su funci n externa
        cout << "Elija el numero de plato que desea comprar: ";
        cin >> eleccion;
        ventaCena(cenas, eleccion);
        break;

    case 4:
        /* code */
        break;

    default:
        cout << "Opcion invalida" << endl;
        break;
    }
    pause();
    return 0;
}
