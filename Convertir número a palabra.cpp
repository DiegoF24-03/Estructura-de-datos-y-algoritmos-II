/*
* Diego Antonio Frias Castillo
* ID:1128342
* Ej: Convertir número a palabra
* Fecha: 11/11/2025
*/


#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Funcion para convertir numeros del 1 al 29
string convertirUnidadesYDecenas(int numero) {
    string nombres[] = { "", "uno", "dos", "tres", "cuatro", "cinco", "seis", "siete", "ocho", "nueve",
        "diez", "once", "doce", "trece", "catorce", "quince", "dieciseis", "diecisiete",
        "dieciocho", "diecinueve", "veinte", "veintiuno", "veintidos", "veintitres",
        "veinticuatro", "veinticinco", "veintiseis", "veintisiete", "veintiocho", "veintinueve" };

    return (numero <= 29) ? nombres[numero] : "";
}

// Funcion para convertir decenas (30-99) - Divide y Venceras
string convertirDecenas(int numero) {
    if (numero <= 29) return convertirUnidadesYDecenas(numero);

    string decenas[] = { "", "", "", "treinta", "cuarenta", "cincuenta", "sesenta", "setenta", "ochenta", "noventa" };
    int decena = numero / 10;
    int unidad = numero % 10;

    return decenas[decena] + (unidad > 0 ? " y " + convertirUnidadesYDecenas(unidad) : "");
}

// Funcion para convertir centenas (100-999) - Divide y Venceras
string convertirCentenas(int numero) {
    if (numero < 100) return convertirDecenas(numero);
    if (numero == 100) return "cien";

    string centenas[] = { "", "ciento", "doscientos", "trescientos", "cuatrocientos",
                        "quinientos", "seiscientos", "setecientos", "ochocientos", "novecientos" };
    int centena = numero / 100;
    int resto = numero % 100;

    return centenas[centena] + (resto > 0 ? " " + convertirDecenas(resto) : "");
}

// Funcion para convertir miles (1,000-999,999) - Divide y Venceras
string convertirMiles(int numero) {
    if (numero < 1000) return convertirCentenas(numero);

    int miles = numero / 1000;
    int resto = numero % 1000;
    string resultado = (miles == 1) ? "mil" : convertirCentenas(miles) + " mil";

    return resultado + (resto > 0 ? " " + convertirCentenas(resto) : "");
}

// Funcion para convertir millones (1,000,000-999,999,999) - Divide y Venceras
string convertirMillones(int numero) {
    if (numero < 1000000) return convertirMiles(numero);

    int millones = numero / 1000000;
    int resto = numero % 1000000;
    string resultado = (millones == 1) ? "un millon" : convertirCentenas(millones) + " millones";

    return resultado + (resto > 0 ? " " + convertirMiles(resto) : "");
}

// Funcion principal para convertir numero a palabra
string numeroAPalabra(double monto) {
    int parteEntera = (int)monto;
    int centavos = (int)round((monto - parteEntera) * 100);

    string resultado = (parteEntera == 0) ? "cero" : convertirMillones(parteEntera);
    resultado[0] = toupper(resultado[0]);

    return resultado + " con " + to_string(centavos) + " centavos";
}

// Funcion para validar entrada numerica
bool leerNumero(double& numero) {
    if (cin >> numero) {
        return true;
    }
    cin.clear();
    cin.ignore(10000, '\n');
    return false;
}

// Funcion principal del programa
int main() {
    double monto;
    int opcion;

    do {
        cout << "\n==================================================" << endl;
        cout << "    CONVERTIDOR DE NUMERO A PALABRA" << endl;
        cout << "==================================================" << endl;
        cout << "1. Convertir un monto a palabra" << endl;
        cout << "2. Salir" << endl;
        cout << "==================================================" << endl;
        cout << "Seleccione una opcion: ";

        if (!leerNumero(monto)) {
            cout << "\nError: Debe ingresar solo numeros." << endl;
            continue;
        }

        opcion = (int)monto;

        if (opcion == 1) {
            cout << "\nIngrese un monto (maximo 999,999,999.99): ";

            if (!leerNumero(monto)) {
                cout << "\nError: Debe ingresar solo numeros, no letras." << endl;
                continue;
            }

            if (monto < 0 || monto > 999999999.99) {
                cout << "\nError: El monto debe estar entre 0 y 999,999,999.99" << endl;
            }
            else {
                string resultado = numeroAPalabra(monto);
                cout << "\n--------------------------------------------------" << endl;
                cout << "Monto ingresado: $" << fixed << setprecision(2) << monto << endl;
                cout << "En palabras: " << resultado << endl;
                cout << "==================================================" << endl;
            }
        }
        else if (opcion == 2) {
            cout << "\nGracias por usar el convertidor. Hasta pronto!" << endl;
        }
        else {
            cout << "\nOpcion invalida. Por favor seleccione 1 o 2." << endl;
        }

    } while (opcion != 2);

    return 0;
}