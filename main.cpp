#include <iostream>
#include <stdlib.h> //libreria para limpiar la pantalla
#include <time.h> //librería que permite usar 'time' como valor para 'srand'

#include <windows.h> //libreria para imprimir emoji

#include "Proye_Lib.h"//libreria propia, funciones de imprimir

using namespace std;

///Declaración de variables globales
int numCartasMazo = 0;
int numTurno = 0;
int staminaMax = 1, staminaActual = staminaMax;
int numCartasNIV1 = 6;
int balanza=0;

///Declaración de Funciones
void Menu();
void DarTurno();
void Continuar();
void ContinuarSinAgarrar();
void UsarCartaMazo();
void ImprimirVitales();
void MenuOpciones();
void ImprimirCartaTablero(struct Carta c);
void ImprimirCartaPreTablero(struct Carta c);
void ImprimirCartaMazo(struct Carta c);
void ImprimirMazo();
void ImprimirPantalla();
void ActualizarStamina();
void DarMazoInicial();
void AgarrarCartaBaraja();
void InicioTurno();
void AvanceTurno();
void DarTurno();
void AccionJugador();
void AccionEnemigo();
void VerificarGanador();
void ExplicacionAgarrarCarta();
void ExplicacionTurno();



///Declaración de esructura
struct Carta{ //Se declaran los elementos que tiene cada 'Carta'
    string nombre;
    int HP;
    int PWR;
    int COST;
    int Turno;
    int Pos;
    int IDbaraja; //sin uso de momento
};

///Definicion de estructuras
struct Carta Baraja[7] = { //Cartas que el jugador PODRÍA agarrar de la BARAJA
    //Nombre, HP, PWR, Cost
        {"Bee ", 1, 2, 2, 0, 0, 0},
        {"Crub", 3, 1, 3, 0, 0, 0},
        {"Fly ", 2, 2, 2, 0, 0, 0},
        {"Wasp", 2, 3, 4, 0, 0, 0},
        {"Ant ", 1, 1, 1, 0, 0, 0},
        {"Ant ", 1, 1, 1, 0, 0, 0},
        {"Bee ", 1, 2, 2, 0, 0, 0},

};
struct Carta CartasEnemigoNIV1[7] = { //Se crean las cartas que la computadora tendrá para atacar
    //Turno es el numero del turno
    //Pos es la posicion en que se pondra, 1-2-3-4-5
    //Nombre,   HP,PWR,Cost, Turno, Pos
        {"Ant ", 1, 1, 0,    0,     2, 0},
        {"Fly ", 2, 2, 0,    1,     3, 0},
        {"Ant ", 1, 1, 0,    1,     4, 0},
        {"Wasp", 2, 3, 0,    2,     0, 0},
        {"Rock", 3, 0, 0,    3,     1, 0},
        {"Fly ", 2, 2, 0,    4,     2, 0},
        {"Ant ", 1, 1, 0,    4,     3, 0}
};
struct Carta Defensa[1] ={
    {"Rock", 2, 0, 1, 0, 0, 0}
};
struct Carta TableroVacio[1] ={
    {"    ", 0, 0, 0, 0, 0, 0}
};

///Declaración de estructuras VACIAS
struct Carta TuTablero[5]; //Cartas del tablero del lado Tuyo
struct Carta TableroEnemigo[5]; //Cartas del tablero del lado Enemigo
struct Carta PreTableroEnemigo[5]; //Cartas que el Enemigo va a poner
struct Carta mazo[20]; //Cartas que tienes en tu Mano (mazo)








int main()
{
    //Cambia la semilla para el generador de numero aleatorio "rand"
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); //funcion para admitir imprimir emoji
    Menu();

    DarMazoInicial();
    InicioTurno();
    ContinuarSinAgarrar();
    do {
        Continuar();
    } while(balanza < 5 && balanza > -5);
    system("cls");
    if (balanza >= 5){
        cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl << endl;
        cout << "       ♦ VICTORIOSO FELICIDADES LO DERROTASTE ♦";
        cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl << endl;
    } else if (balanza <= -5){
        cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl << endl;
        cout << "       ♦ HAS PERDIDO, SUERTE LA PROXIMA VEZ ♦";
        cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl << endl;
        }
    return 0;
}


void Menu(){//Despliega la pantalla de inicio del juego
    int opc;
    do{
    system("cls");
    cout << endl << "       ♦ Bienvenido al juego ♦"<< endl << endl;
    cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl << endl;
    cout << "        ¿Quieres iniciar?"<< endl << endl;
    cout << "      Tutorial       Juego"<< endl;
    cout << "       - 1 -         - 2 -"<< endl;
    cout << "  >>";
    cin >> opc;

    switch (opc){
    case 1:{
        system("cls");
        Tutorial();//Funcion que despliega la explicacion del juego
        break;}
    case 2:{
        system("cls");
        cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl;
        cout << endl  << endl <<"  ♦ Comenzando el juego ♦"<<endl<<endl;
        cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl;
        cout << endl << "  >>⌛ ";
        system("pause");
        break;}

    default:{
        system("cls");
        cout << endl  << endl <<"  ! Esa opcion no existe..."<<endl<<endl;
        cout << endl << "  >>⌛ ";
        system("pause");
        break;}
    }
    if(opc==2){break;}
    }while(opc != 2);
}



void ImprimirVitales(){ //Despliega la vida y energía del jugador
    cout << "         " <<"Stamina:" << "      " << "Balanza:" <<endl;
    cout << "         [";
    for(int i = 1; i <= staminaActual; i++) {
        cout << "⚡"; //(unsigned char)219
    }
    for(int i = 6; i > staminaActual; i--){
        cout << ".";
    }
    cout << "]   " << "[";
    for(int i =-5; i < balanza && i < 0; i++){cout << "-";}
    for(int i = 0; i > balanza && i > -5; i--){cout << "o";}
    cout << "|";
    for(int i = 0; i < balanza && i < 5; i++){cout << "o";}
    for(int i = 5; i > balanza && i > 0; i--){cout << "-";}
    cout << "]" << endl << endl;
}

void MenuOpciones(){ //Despliega las opciones que tiene el jugador durante el juego
    int opc = 0;
    do{
    cout << "  ♦ Que desea hacer?" << endl << endl;
    cout << "    Dar Turno    Usar Carta" << endl;
    cout << "      - 1 -        - 2 -   " << endl;
    cout << "  >>"; cin >> opc;
    switch(opc){
    case 1:
        DarTurno();
        break;
    case 2:
        UsarCartaMazo();
        break;
    default:
        ImprimirPantalla();
        cout<<"  ! Esa opcion no existe..."<<endl<<endl;
        cout << endl << "  >>⌛ ";
        system("pause");
        ImprimirPantalla();
        break;
    }
    if (opc != 1){opc = 0;}
    }while(opc < 1 || opc > 2);
}

void ImprimirCartaTablero(struct Carta c){ //Despliega la carta en el tablero
    if (c.HP == 0) {
        cout << "|[             ]";
    } else {
        cout << "|" << c.nombre << " [❤" << c.HP << "  ✊" << c.PWR << "]";
    }
}

void ImprimirCartaPreTablero(struct Carta c){ //Imprime la carta en el pre-tablero
    if (c.HP == 0) {
        cout << "| [        ] ";
    } else {
        cout << "| " << "[❤" << c.HP << "  ✊" << c.PWR << "] ";
    }
}

void ImprimirCartaMazo(struct Carta c){//Imprime info de Carta individualmente
    cout << c.nombre << "   COST: ⚡" << c.COST << " [❤" << c.HP << "  ✊" << c.PWR << "]" << endl;
}

void ImprimirTablero() { //Imprime tanto el tablero, el tablero enemigo y el pretablero
    cout << "      Tus cartas          Enemigo          Proximo Enemigo" << endl << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  ("<< i+1 <<") ";
        ImprimirCartaTablero(TuTablero[i]);
        cout <<"|  ";
        ImprimirCartaTablero(TableroEnemigo[i]);
        ImprimirCartaPreTablero(PreTableroEnemigo[i]);
        cout << endl << endl; // Para separar cada fila del tablero
    }
}

void ImprimirMazo(){ //Imprime el MAZO completo
    cout << "       Tu Mazo: " << endl;
    for(int i = 0; i < numCartasMazo; i++){
        cout << "  ("<<i+1<<")  ";
        ImprimirCartaMazo(mazo[i]);
    }
    cout << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl;
}
void Continuar(){//Continua con el siguiente turno despues de la funcion DarTurno
    ImprimirPantalla();

    AgarrarCartaBaraja();
    ImprimirPantalla();

    MenuOpciones();
};
void ContinuarSinAgarrar(){//Continua con el siguiente turno sin Agarrar carta
    ImprimirPantalla();

    MenuOpciones();
};
void ImprimirPantalla(){ //Imprime tablero y mazo completos
    system("cls");
    ImprimirVitales();
    ImprimirTablero();
    ImprimirMazo();
}

void DarTurno(){ //Hace todas las acciones que deben hacer al final del turno
    ActualizarStamina();
    AccionJugador();
    AccionEnemigo();
    AvanceTurno();

    system("cls");
    ImprimirVitales();
    ImprimirTablero();
    ExplicacionTurno();

}

void DarMazoInicial(){ //Pone cartas Random en el array MAZO del jugador
    mazo[0]=Defensa[0];
    for(int i = 0; i<=3; i++){
        int Aleatorio = rand() % 5;
        mazo[i+1]=Baraja[Aleatorio];
        numCartasMazo++; //contador de cartas totales en el MAZO
    }
}

void AgarrarCartaBaraja(){ //Agrega una carta al MAZO del jugador
    int opc;

    do{
    ImprimirPantalla();
    cout << "  ♦♦♦ De que baraja quieres agarrar la carta?"<< endl << endl;
    cout << "      Baraja Aleatoria       Baraja Defensa       Informacion"<< endl;
    cout << "           - 1 -                  - 2 -              - 3 -"<< endl;
    cout << "  >>"; cin >> opc;
    ImprimirPantalla();

    switch (opc){
    case 1:{
        int Aleatorio = rand() % 5;//Escoje un numero del 1 al 6 para agarrar una carta del array Baraja
        mazo[numCartasMazo]=Baraja[Aleatorio];
        numCartasMazo++; //contador de cartas totales en el MAZO
        break;}
    case 2:{
        mazo[numCartasMazo]=Defensa[0];
        numCartasMazo++;
        break;}
    case 3:{
        ExplicacionAgarrarCarta();
        break;}
    default:{
        ImprimirPantalla();
        cout<<"  ! Esa opcion no existe..."<<endl<<endl;
        cout << endl << "  >>⌛ ";
        system("pause");
        ImprimirPantalla();
        break;}
    }
    }while(opc <= 0 || opc >=3);

    ImprimirPantalla();
    cout << "  ♦️ Agarraste la carta:" << endl << endl;
    cout << "      ";
    ImprimirCartaMazo(mazo[numCartasMazo-1]);
    cout << endl << "  >>⌛ ";
    system("pause");
}

void UsarCartaMazo(){//Funcion para Usar la carta del mazo y la colocarla en el tablero
    /*Quita una carta del MAZO del jugador */
    ImprimirPantalla();
    int eleccion;
    Carta CartaUsada;
    do{
            cout << "  ♦️ Que carta vas a usar?      (Cancelar - 0)" << endl << endl << endl;
            cout << "  >>"; cin >> eleccion;
            if (eleccion == 0){break;}

            if(eleccion > numCartasMazo || eleccion < 0){
                ImprimirPantalla();
                cout<<"  ! Esa carta no existe..."<<endl<<endl;
                cout << endl << "  >>⌛ ";
                system("pause");
                ImprimirPantalla();
            }else{
            CartaUsada = mazo[eleccion-1];//variable temporal

                if(CartaUsada.COST > staminaActual){
                    ImprimirPantalla();
                    cout<<"  !️ No tienes suficiente energia..."<<endl << endl;
                    cout << endl << "  >>⌛ ";
                    system("pause");
                    ImprimirPantalla();
                }
            }
        }while (eleccion > numCartasMazo || eleccion < 0 || CartaUsada.COST > staminaActual);
    if (eleccion != 0){

    ImprimirPantalla();
    int pos;

        do{
            cout<<"  ♦️ En que posicion quieres poner la carta?      (Cancelar - 0)" << endl <<endl<< "     ";
            ImprimirCartaMazo(CartaUsada);
            cout<< endl;
            cout << "  >>"; cin>>pos;
            if(pos == 0){break;}

            if(TuTablero[pos-1].HP!=0){
                cout<<"  ! Posicion ya ocupada..."<<endl<<endl;
                cout << endl << "  >>⌛ ";
                system("pause");
                ImprimirPantalla();
            }
            if(pos<1 || pos>5){
                ImprimirPantalla();
                cout<<"  ! Posicion invalida..."<<endl << endl;
                cout << endl << "  >>⌛ ";
                system("pause");
                ImprimirPantalla();
            }
        }while(TuTablero[pos-1].HP!=0 || pos<1 || pos>5);
    if (pos != 0){

    numCartasMazo--;//contador de cartas totales en el MAZO

    for(int i = eleccion-1; i < numCartasMazo; i++){ //Ciclo para reccorrer las cartas del MAZO
        mazo[i]=mazo[i+1];
    }

    TuTablero[pos-1]=CartaUsada;//imprimir la carta que uses del mazo
    staminaActual=staminaActual-CartaUsada.COST;

    }
}
ImprimirPantalla();
}
void ActualizarStamina(){ //Aumenta la STAMINAMAXima en +1, hasta que llega al 6
    staminaMax++;
    if(staminaMax > 6) {
        staminaMax = 6;
    }
    staminaActual = staminaMax;
}


void InicioTurno(){ //Prepara el tablero para el primer turno
    for(int i = 0; i < numCartasNIV1; i++){
            switch(CartasEnemigoNIV1[i].Turno){
            case 0:
                TableroEnemigo[CartasEnemigoNIV1[i].Pos]=CartasEnemigoNIV1[i];
                break;
            case 1:
                PreTableroEnemigo[CartasEnemigoNIV1[i].Pos]=CartasEnemigoNIV1[i];
            break;
        }
    }

    numTurno++;
}

void AvanceTurno(){ //Mueve las cartas para el siguiente turno
    //Mover cartas de PreTablero a Tablero
    numTurno++;
    for(int i = 0; i < 5; i++){
        if(TableroEnemigo[i].HP==0){
            TableroEnemigo[i]=PreTableroEnemigo[i];
            PreTableroEnemigo[i]=TableroVacio[0];
        }
    }
    //Checar si la Carta siguiente puede ser puesta en el Pretablero
    for(int i = 0; i < 5; i++){
        if(PreTableroEnemigo[i].HP != 0){
            for(int j = 0; j < numCartasNIV1; j++){
                if(CartasEnemigoNIV1[j].Pos==i){
                    while(CartasEnemigoNIV1[j].Turno==numTurno){
                    CartasEnemigoNIV1[j].Turno++;/***!!!!!!!!!!!!!!!!!!!!***/
                    }
                }
            }
        }
    }
    //Poner carta en el PreTablero
    for(int i = 0; i < numCartasNIV1; i++){
        if(CartasEnemigoNIV1[i].Turno==numTurno){
            PreTableroEnemigo[CartasEnemigoNIV1[i].Pos]=CartasEnemigoNIV1[i];
        }
    }
}
void AccionJugador(){//Las cartas del jugador atacan
    int danoExtra = 0;
        for(int i = 0; i < 5; i++){
        if (TuTablero[i].HP!=0){
            if (TableroEnemigo[i].HP!=0){
                TableroEnemigo[i].HP=TableroEnemigo[i].HP-TuTablero[i].PWR;
                if (TableroEnemigo[i].HP<0){
                    danoExtra = TableroEnemigo[i].HP;
                    TableroEnemigo[i].HP = 0;
                    if (PreTableroEnemigo[i].HP!=0){
                        PreTableroEnemigo[i].HP=PreTableroEnemigo[i].HP+danoExtra;
                        if (PreTableroEnemigo[i].HP<0){PreTableroEnemigo[i].HP=0;}
                    }
                }
            }
            else {
                balanza+=TuTablero[i].PWR;
            }
        }
     }
 }

void AccionEnemigo(){//Las cartas del enemigo atacan
    for(int i = 0; i < numCartasNIV1; i++) {
        if (TableroEnemigo[i].HP!=0){
            if (TuTablero[i].HP!=0){
                TuTablero[i].HP=TuTablero[i].HP-TableroEnemigo[i].PWR;
                if (TuTablero[i].HP<0){TuTablero[i].HP=0;}
            }
            else {
                balanza=balanza-TableroEnemigo[i].PWR;
            }
        }
    }
}
void ExplicacionAgarrarCarta(){//Despliega informacion de las cartas para agarrar
    system("cls");
    cout << endl << endl << "   i Estas son las cartas que te pueden tocar..." << endl<< endl << "  ♦ Cartas de la Baraja Aleatoria:" << endl<< endl;
    for(int i = 0; i <= 4; i++){
    cout << "      ";
    ImprimirCartaMazo(Baraja[i]);
    }
    cout << endl << endl << "  ♦ Carta de la Baraja Defensa:" << endl<< endl;
    cout << "      ";
    ImprimirCartaMazo(Defensa[0]);
    cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl;
    cout << endl << "  >>⌛ ";
    system("pause");
}
void ExplicacionTurno(){//Despliega informacion breve de lo sucedido en el turno

    cout << endl << endl << "<<<<>>>><><<<<>>>><><<<<>>>><><<<<>> ><>< << > <>< <<   >" << endl << endl;
    if (balanza <= -5){
        cout << "  ! Tu balanza CAYÓ. Haz perdido!" << endl << endl;
        cout << endl << "  >>⌛ ";
        system("pause");
    }
    if (balanza <-1 && balanza > -5){
        cout << "  ! Tu balanza esta BAJA, tienes poca vida!" << endl << endl;
        cout << "  ♦️ Siguiente turno..." << endl << endl << endl << "  >>⌛ ";
    system("pause");
    }
    if (balanza >=-1 && balanza < 5){
        cout << "  ♦️ Siguiente turno..." << endl << endl << endl << "  >>⌛ ";
    system("pause");
    }
    if (balanza >= 5){
        cout << "  ! Tu balanza SUBIÓ. Haz GANADO!" << endl << endl;
        cout << endl << "  >>⌛ ";
    system("pause");
    }

}
