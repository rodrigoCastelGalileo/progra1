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

// FUNCIONES/PROCESOS

void generarReporte(double totalRecaudado, int totalMenusVendidos,
                    const vector<Menu> &desayunos,
                    const vector<Menu> &almuerzos,
                    const vector<Menu> &cenas)
{
    ofstream reporte("Archivos/reporte_final.txt");

    if (!reporte.is_open())
    {
        cout << "No se pudo crear el archivo reporte_final.txt" << endl;
        return;
    }

    reporte << "******** REPORTE DE VENTAS DIARIO ********" << endl;
    reporte << "TOTAL RECAUDADO: Q " << totalRecaudado << endl;
    reporte << "Total Menu vendidos " << totalMenusVendidos << endl;
    reporte << endl;

    reporte << "******** INVENTARIO SOBRANTE ********" << endl;

    for (size_t i = 0; i < desayunos.size(); i++)
        if (desayunos[i].stock > 0)
            reporte << "- " << desayunos[i].nombre << ": " << desayunos[i].stock << endl;

    for (size_t i = 0; i < almuerzos.size(); i++)
        if (almuerzos[i].stock > 0)
            reporte << "- " << almuerzos[i].nombre << ": " << almuerzos[i].stock << endl;

    for (size_t i = 0; i < cenas.size(); i++)
        if (cenas[i].stock > 0)
            reporte << "- " << cenas[i].nombre << ": " << cenas[i].stock << endl;

    reporte << "******************************************" << endl;

    reporte.close();

    cout << "Reporte final generado correctamente en Archivos/reporte_final.txt" << endl;
}

void pause()
{
    cout << "\n\nPresiona ENTER para salir...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// 🔥 FIX DEFINITIVO DEL ERROR (stod/stoi seguro)
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

        if (!getline(archivo, linea))
            break;

        if (linea.empty())
        {
            i--;
            continue;
        }

        stringstream ss(linea);
        vector<string> palabras;
        string palabra;

        while (ss >> palabra)
            palabras.push_back(palabra);

        if (palabras.size() < 4)
        {
            cout << "Error de formato en archivo: " << nombreArchivo << endl;
            continue;
        }

        try
        {
            nuevoMenu.cantIng = stoi(palabras[palabras.size() - 1]);
            nuevoMenu.stock = stoi(palabras[palabras.size() - 2]);
            nuevoMenu.precio = stod(palabras[palabras.size() - 3]);
        }
        catch (...)
        {
            cout << "Error de formato en archivo: " << nombreArchivo << endl;
            continue;
        }

        nuevoMenu.nombre = "";

        for (size_t j = 0; j < palabras.size() - 3; j++)
        {
            nuevoMenu.nombre += palabras[j];
            if (j < palabras.size() - 4)
                nuevoMenu.nombre += " ";
        }

        for (int j = 0; j < nuevoMenu.cantIng; j++)
        {
            Ingrediente nuevoIngrediente;

            if (!getline(archivo, nuevoIngrediente.nombre))
                break;

            nuevoMenu.ing.push_back(nuevoIngrediente);
        }

        menus.push_back(nuevoMenu);
    }

    archivo.close();
}

void reescribirArchivo(string nombreArchivo, vector<Menu> &menus)
{
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open())
    {
        cout << "No se pudo reescribir el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo << menus.size() << endl;

    for (size_t i = 0; i < menus.size(); i++)
    {
        archivo << menus[i].nombre << " "
                << menus[i].precio << " "
                << menus[i].stock << " "
                << menus[i].cantIng << endl;

        for (size_t j = 0; j < menus[i].ing.size(); j++)
        {
            archivo << menus[i].ing[j].nombre << endl;
        }
    }

    archivo.close();
}

// VENTAS

void ventaDesayuno(vector<Menu> &desayunos, int eleccion)
{
    if (eleccion > 0 && eleccion <= (int)desayunos.size())
    {
        int idx = eleccion - 1;

        if (desayunos[idx].stock > 0)
        {
            desayunos[idx].stock--;
            cout << "Venta exitosa de: " << desayunos[idx].nombre << endl;
            reescribirArchivo("Archivos/desayuno.txt", desayunos);
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
    if (eleccion > 0 && eleccion <= (int)almuerzos.size())
    {
        int idx = eleccion - 1;

        if (almuerzos[idx].stock > 0)
        {
            almuerzos[idx].stock--;
            cout << "Venta exitosa de: " << almuerzos[idx].nombre << endl;
            reescribirArchivo("Archivos/almuerzo.txt", almuerzos);
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
    if (eleccion > 0 && eleccion <= (int)cenas.size())
    {
        int idx = eleccion - 1;

        if (cenas[idx].stock > 0)
        {
            cenas[idx].stock--;
            cout << "Venta exitosa de: " << cenas[idx].nombre << endl;
            reescribirArchivo("Archivos/cena.txt", cenas);
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

// MAIN

int main()
{
    vector<Menu> desayunos;
    vector<Menu> almuerzos;
    vector<Menu> cenas;

    double totalRecaudado = 0;
    int totalMenusVendidos = 0;

    int option;
    int eleccion;

    do
    {
        cout << "*****************************************************************" << endl;
        cout << "Bienvenido al punto de venta de la Cafeteria 'Alimentos y mas'" << endl;
        cout << "Por favor seleccione una de las siguientes opciones del 1 al 5: " << endl;
        cout << "1. Venta de Desayuno" << endl;
        cout << "2. Venta de Almuerzo" << endl;
        cout << "3. Venta de Cena" << endl;
        cout << "4. Cerrar Caja Y salir" << endl;
        cout << "5. Cerrar Programa" << endl;
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
                    cout << "- " << desayunos[i].ing[j].nombre << endl;

                cout << endl;
            }

            cout << "0. Regresar al menu principal" << endl;
            cout << "Elija el numero de plato que desea comprar: ";
            cin >> eleccion;

            if (eleccion == 0)
            {
                cout << "\nRegresando...\n\n";
                break;
            }

            if (eleccion > 0 && eleccion <= (int)desayunos.size())
            {
                if (desayunos[eleccion - 1].stock > 0)
                {
                    totalRecaudado += desayunos[eleccion - 1].precio;
                    totalMenusVendidos++;
                }

                ventaDesayuno(desayunos, eleccion);
            }

            break;

        case 2:
            cargarDatos("Archivos/almuerzo.txt", almuerzos);

            for (size_t i = 0; i < almuerzos.size(); i++)
            {
                cout << i + 1 << ". " << almuerzos[i].nombre << " - Q" << almuerzos[i].precio << endl;
                cout << "Stock: " << almuerzos[i].stock << endl;
                cout << "Ingredientes:" << endl;

                for (size_t j = 0; j < almuerzos[i].ing.size(); j++)
                    cout << "- " << almuerzos[i].ing[j].nombre << endl;

                cout << endl;
            }

            cout << "0. Regresar al menu principal" << endl;
            cout << "Elija el numero de plato que desea comprar: ";
            cin >> eleccion;

            if (eleccion == 0)
            {
                cout << "\nRegresando...\n\n";
                break;
            }

            if (eleccion > 0 && eleccion <= (int)almuerzos.size())
            {
                if (almuerzos[eleccion - 1].stock > 0)
                {
                    totalRecaudado += almuerzos[eleccion - 1].precio;
                    totalMenusVendidos++;
                }

                ventaAlmuerzo(almuerzos, eleccion);
            }

            break;

        case 3:
            cargarDatos("Archivos/cena.txt", cenas);

            for (size_t i = 0; i < cenas.size(); i++)
            {
                cout << i + 1 << ". " << cenas[i].nombre << " - Q" << cenas[i].precio << endl;
                cout << "Stock: " << cenas[i].stock << endl;
                cout << "Ingredientes:" << endl;

                for (size_t j = 0; j < cenas[i].ing.size(); j++)
                    cout << "- " << cenas[i].ing[j].nombre << endl;

                cout << endl;
            }

            cout << "0. Regresar al menu principal" << endl;
            cout << "Elija el numero de plato que desea comprar: ";
            cin >> eleccion;

            if (eleccion == 0)
            {
                cout << "\nRegresando...\n\n";
                break;
            }

            if (eleccion > 0 && eleccion <= (int)cenas.size())
            {
                if (cenas[eleccion - 1].stock > 0)
                {
                    totalRecaudado += cenas[eleccion - 1].precio;
                    totalMenusVendidos++;
                }

                ventaCena(cenas, eleccion);
            }

            break;

        case 4:
            cargarDatos("Archivos/desayuno.txt", desayunos);
            cargarDatos("Archivos/almuerzo.txt", almuerzos);
            cargarDatos("Archivos/cena.txt", cenas);

            generarReporte(totalRecaudado, totalMenusVendidos,
                           desayunos, almuerzos, cenas);

            option = 5;
            break;

        case 5:
            cout << "Saliendo del programa..." << endl;
            break;
        }

    } while (option != 5);

    pause();
    return 0;
}