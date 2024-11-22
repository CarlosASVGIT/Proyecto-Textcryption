#include <iostream>
#include <stdlib.h> //libreria para limpiar la pantalla
#include <time.h> //librería que permite usar 'time' como valor para 'srand'

using namespace std;

//Declaración de variables globales
int numCartasMazo = 0;
int numTurno = 0;
int staminaMax = 1, staminaActual = staminaMax;
int numCartasNIV1 = 6;
int balanza = 0;

///Declaración de Funciones
void DarTurno();
void Continuar();
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
void AccionEnemigo();
void AccionJugador();



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
struct Carta Baraja[6] = { //Cartas que el jugador PODRÍA agarrar de la BARAJA
    //Nombre, HP, PWR, Cost
        {"Norm", 3, 2, 2, 0, 0, 0},
        {"Prot", 4, 1, 3, 0, 0, 0},
        {"Atac", 2, 3, 3, 0, 0, 0},
        {"Bara", 1, 1, 1, 0, 0, 0},
        {"Debi", 2, 2, 2, 0, 0, 0},
        {"Fuer", 4, 5, 5, 0, 0, 0}
};
struct Carta CartasEnemigoNIV1[6] = { //Se crean las cartas que la computadora tendrá para atacar
    //Turno es el numero del turno
    //Pos es la posicion en que se pondra, 1-2-3-4-5
    //Nombre,   HP,PWR,Cost, Turno, Pos
        {"Norm", 3, 2, 2,    0,     0, 0},
        {"Prot", 4, 1, 3,    0,     2, 0},
        {"Atac", 2, 3, 3,    1,     2, 0},
        {"Bara", 1, 1, 1,    1,     3, 0},
        {"Debi", 2, 2, 2,    4,     3, 0},
        {"Fuer", 4, 5, 5,    5,     3, 0}
};
struct Carta Defensa[1] ={
    {"Defe", 2, 0, 1, 0, 0, 0}
};
struct Carta TableroVacio[1] ={
    {"    ", 0, 0, 0, 0, 0, 0}
};

///Declaración de estructuras VACIAS
struct Carta TuTablero[5]; //Cartas del tablero del lado Tuyo
struct Carta TableroEnemigo[5]; //Cartas del tablero del lado Enemigo
struct Carta PreTableroEnemigo[5]; //Cartas que el Enemigo va a poner
struct Carta mazo[10]; //Cartas que tienes en tu Mano (mazo)








int main()
{
    int balanza = 0;
    //Cambia la semilla para el generador de numero aleatorio "rand"
    srand(time(NULL));

    DarMazoInicial();
    InicioTurno();
    Continuar();
    Continuar();
    Continuar();
    Continuar();
    Continuar();
    Continuar();
    Continuar();
    Continuar();
    Continuar();



    return 0;
}


void ImprimirVitales(){
    cout << "            " <<"Stamina:" << "      " << "Balanza:" <<endl;
    cout << "            [";
    for(int i = 1; i <= staminaActual; i++) {
        cout << "*"; //(unsigned char)219
    }
    cout << "]           " << balanza;
    cout << endl << endl;
}

void MenuOpciones(){
    cout << "  ~ Que desea hacer?" << endl << endl;
    cout << "        1            2               3  " << endl;
    cout << "   (Dar Turno)  (Usar Carta)  (Agarrar Carta)" << endl;
    int opc;
    cin >> opc;
    switch(opc){
    case 1:
        DarTurno();
        break;
    case 2:
        UsarCartaMazo();
        break;
    case 3:
        AgarrarCartaBaraja();
        break;
    }
}

void ImprimirCartaTablero(struct Carta c){
    if (c.HP == 0) {
        cout << "|     [            ] ";
    } else {
        cout << "|" << c.nombre << " [HP:" << c.HP << "   PWR:" << c.PWR << "] ";
    }
}

void ImprimirCartaPreTablero(struct Carta c){
    if (c.HP == 0) {
        cout << "|[            ] ";
    } else {
        cout << "|" << "[HP:" << c.HP << "   PWR:" << c.PWR << "] ";
    }
}

void ImprimirCartaMazo(struct Carta c){//Imprime info de Carta individualmente
    cout << "-" << c.nombre << " COST=" << c.COST << " [HP:" << c.HP << " PWR: " << c.PWR << "]" << endl;
}

void ImprimirTablero() {
    cout << " Fila     Tu Tablero         Tablero Enemigo" << endl << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  " << i+1 << "  ";
        ImprimirCartaTablero(TuTablero[i]);
        ImprimirCartaTablero(TableroEnemigo[i]);
        ImprimirCartaPreTablero(PreTableroEnemigo[i]);
        cout << endl << endl; // Para separar cada fila del tablero
    }
}

void ImprimirMazo(){ //Imprime el MAZO completo
    cout << "Tu Mazo: " << endl;
    for(int i = 0; i < numCartasMazo; i++){
        ImprimirCartaMazo(mazo[i]);
    }
    cout << endl;
}
void Continuar(){
    ImprimirPantalla();
    MenuOpciones();
    AccionJugador();
    AccionEnemigo();
};
void ImprimirPantalla(){ //Imprime tablero y mazo completos
    system("cls"); //Limpia la pantalla
    ImprimirVitales();
    ImprimirTablero();
    ImprimirMazo();
}

void DarTurno(){
    ActualizarStamina();
    AvanceTurno();
}

void DarMazoInicial(){ //Pone cartas Random en el array MAZO del jugador
    mazo[0]=Defensa[0];
    for(int i = 0; i<=3; i++){
        int Aleatorio = rand() % 6;
        mazo[i+1]=Baraja[Aleatorio];
        numCartasMazo++; //contador de cartas totales en el MAZO
    }
}

void AgarrarCartaBaraja(){ //Agrega una carta al MAZO del jugador
    int opc;
    ImprimirPantalla();
    cout << "  ~ De que baraja quieres agarrar la carta?"<< endl << endl << endl;
    cout << "      Baraja Aleatoria       Baraja Defensa"<< endl;
    cout << "           - 1 -                  - 2 -"<< endl;
    cin >> opc;
    ImprimirPantalla();

    do{
    if (opc == 0){break;}

    switch (opc){
    case 1:{
        int Aleatorio = rand() % 6;//Escoje un numero del 1 al 6 para agarrar una carta del array Baraja
        mazo[numCartasMazo]=Baraja[Aleatorio];
        numCartasMazo++; //contador de cartas totales en el MAZO
        break;}
    case 2:{
        mazo[numCartasMazo]=Defensa[0];
        numCartasMazo++;
        break;}
    }

    ImprimirPantalla();
    cout << "  ~ Agarraste la carta:" << endl << endl << endl;
    cout << "      ";
    ImprimirCartaMazo(mazo[numCartasMazo-1]);
    cout << endl;
    system("pause");
    break;
    }while(true);
}

void UsarCartaMazo(){
    /*Quita una carta del MAZO del jugador */
    ImprimirPantalla();
    cout << "  ~ Que carta vas a usar?      (Cancelar - 0)" << endl << endl << endl;
    int eleccion;
    do {
    cin >> eleccion;

    while(eleccion > numCartasMazo){
        cout<<"Esa carta no existe"<<endl;
        system("pause");
        ImprimirPantalla();

        cout<<"  ~ Que carta vas a usar?      (Cancelar - 0)" << endl << endl << endl;
        cin>>eleccion;
    }
    if (eleccion == 0){break;}
    Carta CartaUsada = mazo[eleccion-1];//variable temporal

    while(CartaUsada.COST>staminaActual){
     cout<<"No tienes suficiente energia"<<endl;
     system("pause");
     ImprimirPantalla();
     cout << "Que carta vas a usar?      (Cancelar - 0)" << endl;
     cin >> eleccion;
     if (eleccion == 0){break;}
    }
    if (eleccion == 0){break;}

    int pos;
    ImprimirPantalla();
    cout<<"En que posicion quieres poner la carta?" << endl << endl << endl;
    cin>>pos;
    while(TuTablero[pos-1].HP!=0){
        cout<<"la pocision ya esta ocupada"<<endl;
        system("pause");
        ImprimirPantalla();
        cout<<"en que posicion quieres poner la carta?";
        cin>>pos;
        if (pos == 0){break;}
    }
    if (pos == 0){break;}
    while(pos<1 || pos>5){
        cout<<"pocision invalida"<<endl;
         cout<<"en que posicion quieres poner la carta?";
        cin>>pos;
        if (pos == 0){break;}
    }
    if (pos == 0){break;}

    numCartasMazo--;//contador de cartas totales en el MAZO

    for(int i = eleccion-1; i < numCartasMazo; i++){ //Ciclo para reccorrer las cartas del MAZO
        mazo[i]=mazo[i+1];
    }
    TuTablero[pos-1]=CartaUsada;//imprimir la carta que uses del mazo
    staminaActual=staminaActual-CartaUsada.COST;
    break;
    }while(true);
}

void ActualizarStamina(){ //Aumenta la STAMINAMAXima en +1 hasta
    staminaMax++;
    if(staminaMax > 6) {
        staminaMax = 6;
    }
    staminaActual = staminaMax;
}


void InicioTurno(){
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

void AvanceTurno(){
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
void AccionJugador(){
        for(int i = 0; i < numCartasNIV1; i++){
        if (TuTablero[i].HP!=0){
            if (TableroEnemigo[i].HP!=0){
                TableroEnemigo[i].HP=TableroEnemigo[i].HP-TuTablero[i].PWR;

                if (TableroEnemigo[i].HP<0){
                    if (PreTableroEnemigo[i].HP!=0){
                        PreTableroEnemigo[i].HP=PreTableroEnemigo[i].HP+TableroEnemigo[i].HP;
                    }
                }
            }
            else {
                balanza=balanza+TuTablero[i].PWR;

            }
        }
     }
 }

void AccionEnemigo(){
    for(int i = 0; i < numCartasNIV1; i++) {
        if (TableroEnemigo[i].HP!=0){
            if (TuTablero[i].HP!=0){
                TuTablero[i].HP=TuTablero[i].HP-TableroEnemigo[i].PWR;
            }
            else {
                balanza=balanza-TableroEnemigo[i].PWR;
            }
        }
    }
}
