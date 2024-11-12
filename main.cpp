#include <iostream>
#include <stdlib.h> //libreria para limpiar la pantalla
#include <string> //librería para manipular correctamente strings

#include <time.h> //librería que permite usar 'time' como valor para 'srand'
using namespace std;

//Declaración de variables
int numCartasMazo = 0;
int numTurno = 0;
int eleccion;
int numCartasNIV1 = 6;




//Declaración de esructura

struct Carta{ //Se declaran los elementos que tiene cada 'Carta'
    string nombre;
    int HP;
    int PWR;
    int COST;
    int Turno; //sin uso de momento
    int Pos; //sin uso de momento
    int IDbaraja; //sin uso de momento
};

//Definicion de estructuras
struct Carta Baraja[6] = { //Se crean las cartas que el jugador podría agarrar de la BARAJA
    //Nombre, HP, PWR, Cost
        {"Norm", 3, 2, 2, 0, 0, 0},
        {"Prot", 4, 1, 3, 0, 0, 0},
        {"Atac", 2, 3, 3, 0, 0, 0},
        {"Bara", 1, 1, 1, 0, 0, 0},
        {"Debi", 2, 2, 2, 0, 0, 0},
        {"Fuer", 4, 5, 5, 0, 0, 0}
};
struct Carta CartasEnemigoNIV1[20] = { //Se crean las cartas que la computadora tendrá para atacar
    //Turno es el numero del turno
    //Pos es la posicion en que se pondra, 1-2-3-4-5
    //Nombre, HP, PWR, Cost, Turno, Pos
        {"Norm", 3, 2, 2, 0, 1, 0},
        {"Prot", 4, 1, 3, 1, 2, 0},
        {"Atac", 2, 3, 3, 2, 2, 0},
        {"Bara", 1, 1, 1, 3, 3, 0},
        {"Debi", 2, 2, 2, 4, 2, 0},
        {"Fuer", 4, 5, 5, 5, 3, 0}
};
struct Carta TableroVacio[1] ={
    {"    ", 0, 0, 0, 0, 0, 0}
};

//Declaración de estructuras VACIAS
struct Carta TuTablero[5]; //Cartas del tablero del lado Tuyo
struct Carta TableroEnemigo[5]; //Cartas del tablero del lado Enemigo
struct Carta PreTableroEnemigo[5]; //Cartas que el Enemigo va a poner
struct Carta mazo[10]; //Cartas que tienes en tu Mano (mazo)

//Funciones


void ImprimirCartaTablero(struct Carta c){
    cout << "|" << c.nombre << "[HP: " << c.HP << " PWR: " << c.PWR << "]| ";
}

void ImprimirCartaPreTablero(struct Carta c){
    cout << "|" << "[HP:" << c.HP << " PWR: " << c.PWR << "]| ";
}


void ImprimirCartaMazo(struct Carta c){//Imprime info de Carta individualmente
    cout << "-" << c.nombre << " COST=" << c.COST << " [HP:" << c.HP << " PWR: " << c.PWR << "]" << endl;
}

void ImrpimirCartaPreTableroBien(Carta c){}///Puedes empezar con esta función para imprimir el pretablero VACIO

void ImrpimirCartaTableroBien(Carta c){
    if(c.HP == 0){
        cout << "| - -" << "[ - -Vacio- - ]| ";
    } else {
        ImprimirCartaTablero(c);
    }
}

void ImprimirTablero() {
    cout << "Tablero:" << endl;
    for (int i = 0; i < 5; i++) {
        ImrpimirCartaTableroBien(TuTablero[i]);
        ImrpimirCartaTableroBien(TableroEnemigo[i]);
        ImprimirCartaPreTablero(PreTableroEnemigo[i]);
        cout << endl; // Para separar cada fila del tablero
    }
}

void ImprimirMazo(){ //Imprime el MAZO completo
    cout << "Tu Mazo: " << endl;
    for(int i = 0; i < numCartasMazo; i++){
        ImprimirCartaMazo(mazo[i]);
    }
}

void ImprimirPantalla(){ //Imprime tablero y mazo completos
    ImprimirTablero();
    ImprimirMazo();
}





//Las funciones siguientes
///InicioTurno()
///AvanceTruno()
///void DarTurno()
/*No se usan aún, sera para el siguiente*/ ///avance

/**void InicioTurno(){
    for(int i = 0; i < 5; i++){
        if(CartasEnemigoNIV1[i].Turno==0){
            TableroEnemigo[i]=CartasEnemigoNIV1[i];
        }
    }
    for(int i = 0; i < 5; i++){
        if(CartasEnemigoNIV1[i].Turno==1){ //-----
            PreTableroEnemigo[i]=CartasEnemigoNIV1[i]; //----
        }
    }
    numTurno++;
}
void AvanceTurno(){
    for(int i = 0; i < 5; i++){
        if(TableroEnemigo[i].HP==0){
            TableroEnemigo[i]=PreTableroEnemigo[i];
            PreTableroEnemigo[i]=TableroVacio[0];
        }else{
            PreTableroEnemigo[i].Turno++;
        }
        for(int j = 0; j < numCartasNIV1; j++){
            if(CartasEnemigoNIV1[i].Turno==numTurno){
                if(PreTableroEnemigo[i].Turno==0){
                    PreTableroEnemigo[i]=CartasEnemigoNIV1[i];
                }
            }
        }
    }
}
void DarTurno(){
}**/
void DarMazoInicial(){ //Pone cartas Random en el array MAZO del jugador
    for(int i = 0; i<3; i++){
        int Aleatorio = rand() % 6;
        mazo[i]=Baraja[Aleatorio];
        numCartasMazo++; //contador de cartas totales en el MAZO
    }
}

void AgarrarCartaBaraja(){ //Agrega una carta al MAZO del jugador
    cout << "Agarraste una carta" << endl;
    int Aleatorio = rand() % 6;//Escoje un numero del 1 al 6 para agarrar una carta del array Baraja
    mazo[numCartasMazo]=Baraja[Aleatorio];

    ImprimirCartaMazo(mazo[numCartasMazo]);// imprime la carta obtenida
    numCartasMazo++; //contador de cartas totales en el MAZO

    cout << "------------------" << endl;
}
void UsarCartaMazo(){ ///En esta tienes que añadir algo que haga que la carta elegida se ponga en el tablero
    ImprimirMazo();/*Quita una carta del MAZO del jugador */ ///Tienes que preguntar al jugador donde quiere poner su carta
    cout << "Que carta vas a usar?" << endl;
    cin >> eleccion;
    for(int i = eleccion-1; i < numCartasMazo; i++){ //Ciclo para reccorrer las cartas del MAZO
        mazo[i]=mazo[i+1];
    }
    numCartasMazo--; //contador de cartas totales en el MAZO
}

void Stamina(){
    int opc = 0, staMax = 0, i = 1, temp = i;

    do {
        if(i > 6) {
            i = 6;
        }

        if(temp > 6) {
            temp = 6;
        }
        for(staMax = 1; staMax <= i; staMax++) {
            cout << "*"; //(unsigned char)219
            }
        cout << "\nQue deseas hacer? \n1) Nada \n2) quitar stamina \n3) Terminar turno \n4) Salir" << endl;
        cin >> opc;

        switch(opc) {
        case 1:
            continue;
        case 2:
            a = i;
            i = i - 1;
            continue;
        case 3:
            break;
        case 4:
            return 0;
            break;
        default:
            cout << "Error" << endl;
            break;
            }
        i = temp;
        i++;
        temp++;
    } while(true);
}






int main()
{
    //Cambia la semilla para el generador de numero aleatorio "rand"
    srand(time(NULL));

    ImprimirTablero();

    DarMazoInicial();
    UsarCartaMazo();
    ImprimirMazo();

    return 0;
}

