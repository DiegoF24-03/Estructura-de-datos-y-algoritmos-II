/* ENUNCIADO DEL PROBLEMA
Haga un programa C++ que permita que dos jugadores jueguen Tic-Tac-Toe.  El tres en línea, también
conocido como ceros y cruces, tres en raya, cerito cruz, michi, triqui, cuadritos, juego del gato, gato,
equis cero, tic-tac-toe o la vieja es un juego de lápiz y papel entre dos jugadores: O y X, que marcan los
espacios de un tablero de 3×3 alternadamente. La meta del juego es lograr que uno de los jugadores
logre poner tres X o 0 de forma diagonal, horizontal o vertical.
RESTRICCIONES:
A.  El programa debe solicitar los nombres de los jugadores
B. En el caso de que uno de los jugadores gane el programa debe establecer que gano y mostrar el
nombre del jugador que gana
C. El programa solo almacena las tres últimas jugadas de cada jugador. Al ingresar una nueva, se
borra la primera ingresada.
D. El programa debe mostrar al jugador que le toque, cuál será el próximo lugar que será borrado.
*/#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int TAMANO_TABLERO = 3;

// Muestra el tablero con coordenadas 1..3 y a..c
void mostrarTablero(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]) {
    cout << "   a b c" << endl;
    for (int i = 0; i < TAMANO_TABLERO; i++) {
        cout << " " << (i + 1) << " ";
        for (int j = 0; j < TAMANO_TABLERO; j++) {
            cout << tablero[i][j];
            if (j < TAMANO_TABLERO - 1) cout << " ";
        }
        cout << endl;
    }
}

// Verifica si simbolo tiene 3 en raya
bool verificarGanador(char tablero[TAMANO_TABLERO][TAMANO_TABLERO], char simbolo) {
    for (int i = 0; i < TAMANO_TABLERO; i++) {
        if (tablero[i][0] == simbolo && tablero[i][1] == simbolo && tablero[i][2] == simbolo) return true;
        if (tablero[0][i] == simbolo && tablero[1][i] == simbolo && tablero[2][i] == simbolo) return true;
    }
    if (tablero[0][0] == simbolo && tablero[1][1] == simbolo && tablero[2][2] == simbolo) return true;
    if (tablero[0][2] == simbolo && tablero[1][1] == simbolo && tablero[2][0] == simbolo) return true;
    return false;
}

bool tableroLleno(char tablero[TAMANO_TABLERO][TAMANO_TABLERO]) {
    for (int i = 0; i < TAMANO_TABLERO; i++)
        for (int j = 0; j < TAMANO_TABLERO; j++)
            if (tablero[i][j] == ' ') return false;
    return true;
}

// Convierte fila (char '1'..'3') y columna (char 'a'..'c' o 'A'..'C') a índices. Devuelve true si válido.
bool parsearEntrada(const string& s, int& fila, int& columna) {
    // Acepta formatos: "1 a", "1a", con o sin espacio, columna mayúscula o minúscula
    if (s.empty()) return false;
    // eliminar espacios extra al inicio y fin
    size_t i = 0;
    while (i < s.size() && isspace((unsigned char)s[i])) i++;
    if (i == s.size()) return false;
    // leer primer dígito válido
    char cfila = 0;
    if (i < s.size() && (s[i] >= '1' && s[i] <= '3')) {
        cfila = s[i];
        i++;
    }
    else return false;
    // saltar espacios intermedios
    while (i < s.size() && isspace((unsigned char)s[i])) i++;
    if (i == s.size()) return false;
    char ccol = s[i];
    if (isalpha((unsigned char)ccol)) {
        ccol = tolower(ccol);
        if (ccol < 'a' || ccol > 'c') return false;
    }
    else return false;
    // ok
    fila = cfila - '1';
    columna = ccol - 'a';
    return true;
}

int main() {
    // Instrucciones en español y muy específicas (según enunciado)
    cout << "INSTRUCCIONES:" << endl;
    cout << " - Este es un juego Tic-Tac-Toe para 2 jugadores." << endl;
    cout << " - El Jugador 1 usa X y el Jugador 2 usa O." << endl;
    cout << " - Para indicar una jugada escriba fila y columna: ejemplo '1 a' o '2b'." << endl;
    cout << endl;

    string jugador1, jugador2;
    cout << "Ingrese el nombre del Jugador 1 (X): ";
    getline(cin, jugador1);
    if (jugador1.empty()) jugador1 = "Jugador1";
    cout << "Ingrese el nombre del Jugador 2 (O): ";
    getline(cin, jugador2);
    if (jugador2.empty()) jugador2 = "Jugador2";

    char tablero[TAMANO_TABLERO][TAMANO_TABLERO];
    for (int i = 0; i < TAMANO_TABLERO; i++)
        for (int j = 0; j < TAMANO_TABLERO; j++)
            tablero[i][j] = ' ';

    // arreglos circulares para almacenar las ultimas 3 jugadas de cada jugador
    int jugadasJugador1[3] = { -1, -1, -1 }; // guardan index = fila*3 + col
    int jugadasJugador2[3] = { -1, -1, -1 };
    int contJugador1 = 0; // numero de jugadas totales hechas por jugador1
    int contJugador2 = 0;

    int turno = 0; // 0 => jugador1, 1 => jugador2 ; se incrementa despues de jugada valida

    while (true) {
        mostrarTablero(tablero);
        string jugadorActual = (turno % 2 == 0) ? jugador1 : jugador2;
        char simboloActual = (turno % 2 == 0) ? 'X' : 'O';

        // indicar cual será la próxima jugada que se borrará de ESTE jugador (si corresponde)
        if (turno % 2 == 0) {
            // jugador1
            if (contJugador1 >= 3) {
                int indiceBorrar = contJugador1 % 3; // posición circular que se reemplazará ahora
                int cod = jugadasJugador1[indiceBorrar];
                if (cod != -1) {
                    int fb = cod / TAMANO_TABLERO;
                    int cb = cod % TAMANO_TABLERO;
                    cout << jugadorActual << " (X), la proxima jugada que se borrara de su historial es: "
                        << (fb + 1) << char('a' + cb) << " (esta casilla NO se borrara ahora del tablero; se borrara solo cuando se excedan 3 jugadas y se requiera liberar espacio)" << endl;
                }
                else {
                    cout << jugadorActual << " (X), aun no hay jugada que se borrara." << endl;
                }
            }
            else {
                cout << jugadorActual << " (X), aun no hay jugada que se borrara." << endl;
            }
        }
        else {
            // jugador2
            if (contJugador2 >= 3) {
                int indiceBorrar = contJugador2 % 3;
                int cod = jugadasJugador2[indiceBorrar];
                if (cod != -1) {
                    int fb = cod / TAMANO_TABLERO;
                    int cb = cod % TAMANO_TABLERO;
                    cout << jugadorActual << " (O), la proxima jugada que se borrara de su historial es: "
                        << (fb + 1) << char('a' + cb) << " (esta casilla NO se borrara ahora del tablero; se borrara solo cuando se excedan 3 jugadas y se requiera liberar espacio)" << endl;
                }
                else {
                    cout << jugadorActual << " (O), aun no hay jugada que se borrara." << endl;
                }
            }
            else {
                cout << jugadorActual << " (O), aun no hay jugada que se borrara." << endl;
            }
        }

        cout << jugadorActual << ", ingrese su jugada (ej. 1 a): ";
        string entrada;
        if (!getline(cin, entrada)) {
            cout << "Error de entrada. Saliendo." << endl;
            break;
        }
        int fila = -1, columna = -1;
        if (!parsearEntrada(entrada, fila, columna)) {
            cout << "Entrada invalida. Use formato: fila(1-3) columna(a-c). Intente de nuevo." << endl;
            continue;
        }
        if (fila < 0 || fila >= TAMANO_TABLERO || columna < 0 || columna >= TAMANO_TABLERO) {
            cout << "Coordenadas fuera de rango. Intente de nuevo." << endl;
            continue;
        }
        if (tablero[fila][columna] != ' ') {
            cout << "Posicion ocupada. Intente de nuevo." << endl;
            continue;
        }

        // colocar la ficha
        tablero[fila][columna] = simboloActual;

        // actualizar historial (circular) y borrar del tablero si corresponde
        if (turno % 2 == 0) {
            // jugador1 hace una jugada
            int posIndex = contJugador1 % 3; // donde guardamos la nueva jugada
            // si vamos a sobrescribir una jugada previa almacenada, debemos BORRARLA del tablero
            int codigoPrevio = jugadasJugador1[posIndex];
            if (codigoPrevio != -1) {
                int fb = codigoPrevio / TAMANO_TABLERO;
                int cb = codigoPrevio % TAMANO_TABLERO;
                // solo borramos si la casilla sigue siendo de este jugador (por si el otro la usó, aunque eso no puede pasar por validación)
                if (tablero[fb][cb] == 'X') tablero[fb][cb] = ' ';
            }
            jugadasJugador1[posIndex] = fila * TAMANO_TABLERO + columna;
            contJugador1++;
        }
        else {
            // jugador2 hace una jugada
            int posIndex = contJugador2 % 3;
            int codigoPrevio = jugadasJugador2[posIndex];
            if (codigoPrevio != -1) {
                int fb = codigoPrevio / TAMANO_TABLERO;
                int cb = codigoPrevio % TAMANO_TABLERO;
                if (tablero[fb][cb] == 'O') tablero[fb][cb] = ' ';
            }
            jugadasJugador2[posIndex] = fila * TAMANO_TABLERO + columna;
            contJugador2++;
        }

        // comprobar ganador
        if (verificarGanador(tablero, simboloActual)) {
            mostrarTablero(tablero);
            cout << "Felicidades " << jugadorActual << ", has ganado!" << endl;
            break;
        }

        // comprobar empate
        if (tableroLleno(tablero)) {
            mostrarTablero(tablero);
            cout << "El juego es un empate." << endl;
            break;
        }

        turno++;
    }

    return 0;
}