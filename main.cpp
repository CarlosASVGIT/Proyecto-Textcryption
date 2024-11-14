#include <iostream>
#include <iomanip> //libreria para imprimir en consola mas bonito
#include <stdlib.h> //libreria para limpiar la pantalla
#include <string> //librería para manipular correctamente strings

#include <time.h> //librería que permite usar 'time' como valor para 'srand'
using namespace std;

//Declaración de variables
int numCartasMazo = 0;
int numTurno = 0;
int staminaMax = 1, staminaActual = staminaMax;
int numCartasNIV1 = 6;

//Declaración de Funciones
void DarTurno();
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
void ActualizarStamina();


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



int main()
{
    //Cambia la semilla para el generador de numero aleatorio "rand"
    srand(time(NULL));

    DarMazoInicial();
    ImprimirPantalla();
    ImprimirPantalla();
    ImprimirPantalla();

    return 0;
}




void ImprimirVitales(){
    cout << "            " <<"Stamina:" << "      " << "Balanza:" <<endl;
    cout << "            [" << setw(6) << setfill('º');
    for(int i = 1; i <= staminaActual; i++) {
        cout << "*"; //(unsigned char)219
    }
    cout << "]   " << "[~~~~~|o~~~~]";
    cout << endl << endl;
}

void MenuOpciones(){
    cout << "  ~ Que desea hacer?" << endl << endl;
    cout << "        1            2          3  " << endl;
    cout << "   (Dar Turno)  (Usar Carta)  (???)" << endl;
    int opc;
    cin >> opc;
    switch(opc){
    case 1:
        DarTurno();
        break;
    case 2:
        UsarCartaMazo();
        break;
    }
}

void ImprimirCartaTablero(struct Carta c){
    if (c.HP == 0) {
        cout << "|     [            ] ";
    } else {
        cout << "|" << c.nombre << " [HP: " << c.HP << " PWR: " << c.PWR << "] ";
    }
}

void ImprimirCartaPreTablero(struct Carta c){
    if (c.HP == 0) {
        cout << "|[            ] ";
    } else {
        cout << "|" << "[HP:" << c.HP << " PWR: " << c.PWR << "] ";
    }
}

void ImprimirCartaMazo(struct Carta c){//Imprime info de Carta individualmente
    cout << "-" << c.nombre << " COST=" << c.COST << " [HP:" << c.HP << " PWR: " << c.PWR << "]" << endl;
}

void ImprimirTablero() {
    cout << "     Tablero:" << endl << endl;
    for (int i = 0; i < 5; i++) {
        cout << "  ";
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

void ImprimirPantalla(){ //Imprime tablero y mazo completos
    system("cls"); //Limpia la pantalla (ºwº)
    ImprimirVitales();
    ImprimirTablero();
    ImprimirMazo();
    MenuOpciones();
}

void ActualizarStamina();

void DarTurno(){
    ActualizarStamina();
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
    int Aleatorio = rand() % 6;//Escoje un numero del 1 al 6 para agarrar una carta del array Baraja
    mazo[numCartasMazo]=Baraja[Aleatorio];

    ImprimirCartaMazo(mazo[numCartasMazo]);// imprime la carta obtenida
    numCartasMazo++; //contador de cartas totales en el MAZO

    cout << "------------------" << endl;
}

void UsarCartaMazo(){ ///En esta tienes que añadir algo que haga que la carta elegida se ponga en el tablero
    /*Quita una carta del MAZO del jugador */ ///Tienes que preguntar al jugador donde quiere poner su carta
    cout << "Que carta vas a usar?      (Cancelar - 0)" << endl;
    int eleccion;
    do {
    cin >> eleccion;
    if (eleccion == 0){break;}
    Carta CartaUsada = mazo[eleccion-1];//variable temporal

    int pos;
    cout<<"En que posicion quieres poner la carta?";
    cin>>pos;
    while(TuTablero[pos-1].HP!=0){
        cout<<"la pocision ya esta ocupada"<<endl;
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
    ImprimirTablero();
    break;
    }while(true);
}

void ActualizarStamina(){
    if(staminaMax > 6) {
        staminaMax = 6;
    }
    staminaMax++;
    staminaActual = staminaMax;
};
///Esta sujeto a cambio: Stamina(){};
/**void Stamina(){
    int opc;
    do {
        if(staminaMax > 6) {
            staminaMax = 6;
        }
        for(int i = 1; i <= staminaActual; i++) {
            cout << "*"; //(unsigned char)219
            }

        cout << "\nQue deseas hacer? \n1) Nada \n2) Quitar stamina \n3) Terminar turno \n4) Salir" << endl;
        cin >> opc;

        switch(opc) {
        case 1:
            continue;
        case 2:
            staminaActual--;
            continue;
        case 3:
            break;
        case 4:
            break;
        default:
            cout << "Error" << endl;
            break;
            }
        staminaMax++;
        staminaActual = staminaMax;

    } while(true);
}**/
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
}**/
