//jijijijijiji
#include <iostream>
#include <stdlib.h> //libreria para limpiar la pantalla
#include <string> //librería para manipular correctamente strings

#include <time.h> //librería que permite usar 'time' como valor para 'srand'
using namespace std;
int numCartasMazo = 0;
int numTurno = 0;
int eleccion;
int numCartasNIV1 = 6;

struct Carta{ //Se declaran los elementos que tiene cada 'Carta'
    string nombre;
    int HP;
    int PWR;
    int COST;
    int Turno; //sin uso de momento
    int Pos; //sin uso de momento
    int IDbaraja; //sin uso de momento
};
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

struct Carta TuTablero[5];
struct Carta TableroEnemigo[5];
struct Carta PreTableroEnemigo[5];
struct Carta mazo[10]; //Se crea el arreglo del MAZO del jugador, este se crea vacío
void ImprimirPantalla(){
    ImprimirCartaTablero();
    ImprimirMazo();
}
void ImprimirCartaPreTablero(struct Carta c){
    cout << "|" << "[HP:" << c.HP << " PWR: " << c.PWR << "]| " << endl;
}
void ImprimirCartaTablero(struct Carta c){
    cout << "|" << c.nombre << "[HP:" << c.HP+Damage << " PWR: " << c.PWR+Effect << "]| ";
}
void ImprimirCartaMazo(struct Carta c){ //imprime info de Carta individual
    cout << "-" << c.nombre << " COST=" << c.COST << " [HP:" << c.HP << " PWR: " << c.PWR << "]" << endl;
}
void ImprimirTablero(){
    cout << "Tablero:" << endl;
    for(int i = 0; i < 5; i++){
        ImprimirCartaTablero(TuTablero[1]);
        ImprimirCartaTablero(TableroEnemigo[1]);
    }
}

void ImprimirMazo(){ //Imprime el MAZO completo
    cout << "Tu Mazo: " << endl;
    for(int i = 0; i < numCartasMazo; i++){
        ImprimirCartaMazo(mazo[i]);
    }
}
void InicioTurno(){
    for(int i = 0; i < 5; i++){
        if(CartasEnemigoNIV1[i].Turno==0){
            TableroEnemigo[i]=CartasEnemigoNIV1[i];
        }
    }
    for(int i = 0; i < 5; i++){
        if(CartasEnemigoNIV1[i].Turno==1){
            PreTableroEnemigo[i]=CartasEnemigoNIV1[i];
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
                    PreTableroEnemigo[i]=numCartasNIV1[i];
                }
            }
        }
    }
}
void DarTurno(){
}
void DarMazoInicial(){ //Pone cartas Random en el array MAZO del jugador
    for(int i = 0; i<3; i++){
        int Aleatorio = rand() % 6;
        mazo[i]=Baraja[Aleatorio];
        numCartasMazo++; //contador de cartas totales en el MAZO
    }
}

void AgarrarCartaBaraja(){ //Agrega una carta al MAZO del jugador
    cout << "Agarraste una carta" << endl;
    int Aleatorio = rand() % 6;
    mazo[numCartasMazo]=Baraja[Aleatorio];

    ImprimirCartaMazo(mazo[numCartasMazo]);// imprime la carta obtenida
    numCartasMazo++; //contador de cartas totales en el MAZO

    cout << "------------------" << endl;
}
void UsarCartaMazo(){ //Quita una carta del MAZO del jugador
    ImprimirMazo();
    cout << "Que carta vas a usar?" << endl;
    cin >> eleccion;
    for(int i = eleccion-1; i < numCartasMazo; i++){ //Ciclo para reccorrer las cartas del MAZO
        mazo[i]=mazo[i+1];
    }
    numCartasMazo--; //contador de cartas totales en el MAZO
}




int main()
{
    srand(time(NULL));
    DarMazoInicial();

    do while(1==1){

    }
     //Cambia la semilla para el generador de numero aleatorio "rand"

    ImprimirMazo();


    AgarrarCartaBaraja();
    ImprimirMazo();


    ImprimirMazo();
    UsarCartaMazo();

    ImprimirMazo();

    return 0;
}


/*
void tablero() {
    cout << "[HP:" << HPjugador << "]" "[HP:" << STjugador << "]" << endl << endl;
    cout << "-" << Nombre[f1] << "[HP:" << HP[f1] << " PWR: " PWR[f1] << "]" << endl;
    cout << "-" << Nombre[f2] << "[HP:" << HP[f2] << " PWR: " PWR[f2] << "]" << endl;
    cout << "-" << Nombre[f3] << "[HP:" << HP[f3] << " PWR: " PWR[f3] << "]" << endl;
    cout << "-" << Nombre[f4] << "[HP:" << HP[f4] << " PWR: " PWR[f4] << "]" << endl;
};*/

