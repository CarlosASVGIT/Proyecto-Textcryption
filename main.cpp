#include <iostream>
#include <stdlib.h> //libreria para limpiar la pantalla
#include <time.h> //librería que permite usar 'time' como valor para 'srand'

#include <windows.h> //libreria para imprimir emoji


using namespace std;

///Declaración de variables globales
int numCartasMazo = 0;
int numTurno = 0;
int staminaMax = 1, staminaActual = staminaMax;
int numCartasNIV1 = 6;
int balanza=0;

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
void AccionJugador();
void AccionEnemigo();
void VerificarGanador();
void Tutorial();


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
        {"Norm", 3, 2, 2,    2,     0, 0},
        {"Prot", 4, 1, 3,    0,     2, 0},
        {"Atac", 2, 3, 3,    3,     2, 0},
        {"Bara", 1, 1, 1,    1,     3, 0},
        {"Debi", 2, 2, 2,    2,     3, 0},
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
struct Carta mazo[20]; //Cartas que tienes en tu Mano (mazo)








int main()
{
    //Cambia la semilla para el generador de numero aleatorio "rand"
    srand(time(NULL));
    SetConsoleOutputCP(CP_UTF8); //funcion para admitir imprimir emoji

    DarMazoInicial();
    InicioTurno();
    //Continuar();
    do {
        Continuar();
    } while(balanza < 5 && balanza > -5);
    system("cls");
    if (balanza >= 5){
        cout << "VICTORIOSO FELICIDADES LO DERROTASTE";
    } else if (balanza <= -5){
        cout << "HAS PERDIDO ¿QUIERES INTENTARLO DE NUEVO?";
        }
    return 0;
}

void Tutorial(){
cout<<"Aqui hay una explicacion sobre como funciona cada parte del juego:\n\n\n"<<endl;
cout<<"⚡ = STAMINA y COSTE de la carta. Hay un limite de 6 de stamina y aumentara \nen uno cada turno, esta se gastara dependiendo del coste de tu carta.\n\n"<<endl;
cout<<"❤ = HP o VIDA de la carta. Cada carta tiene su propia cantidad de HP y esta \nbajara su valor si es atacada por otra carta en el tablero enemigo. \n\n"<<endl;
cout<<"✊ = ATAQUE de la carta. este tambien varia dependiendo de la carta, es la \ncantidad de daño que se le hara al enemigo.\n\n"<<endl;
cout<<"BALANZA = es la cantidad de daño que se le hace al enemigo o que este le \nhace al jugador(5 puntos como max), solo aumenta o disminuye cuando se ataca a un lugar del \ntablero sin una carta.\n\n"<<endl;
cout<<"TUS CARTAS = sera el espacio donde colocas tus cartas para atacar al enemigo \ny donde este atacara al jugador de manera horizontal, cada una de las filas \ntiene su enumeracion \n\n"<<endl;
cout<<"ENEMIGO = espacio donde estaran las cartas del enemigo.\n\n"<<endl;
cout<<"PROXIMO ENEMIGO = espacio donde se indica las proximas cartas que usara el enenemigo, estas se moveran de \nmanera horizontal al final de cada turno.\n\n"<<endl;
cout<<"TU MAZO = son todas las cartas que tienes en tu posecion, cada una con \nsu nombre, numero y estadisticas.\n\n"<<endl;
cout<<"DAR TURNO = implica acabar el turno, por lo que las cartas atacaran, empezando \ncon TUS CARTAS, luego las del ENEMIGO y al final las del PROXIMO ENEMIGO se \nmoveran de lugar.\n\n"<<endl;
cout<<"USAR CARTA = se escojrea una de las cartas de tu maso y la podras poner en \ncualquier fila de tu tablero, a no ser que esta fila ya este ocupada o que no se \ntenga suficiente estamina.\n\n"<<endl;
cout<<"AGARRAR CARTA = escoje una carta de la baraja para incluirla en su mazo, esta \naccion no requiere ningun coste.\n\n"<<endl;}

void ImprimirVitales(){
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

void MenuOpciones(){
    int opc = 0;
    do{
    cout << "  ♦️ Que desea hacer?" << endl << endl;
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
    }
    }while(opc < 1 || opc > 2);
}

void ImprimirCartaTablero(struct Carta c){
    if (c.HP == 0) {
        cout << "|[             ]";
    } else {
        cout << "|" << c.nombre << " [❤" << c.HP << "  ✊" << c.PWR << "]";
    }
}

void ImprimirCartaPreTablero(struct Carta c){
    if (c.HP == 0) {
        cout << "| [        ] ";
    } else {
        cout << "| " << "[❤" << c.HP << "  ✊" << c.PWR << "] ";
    }
}

void ImprimirCartaMazo(struct Carta c){//Imprime info de Carta individualmente
    cout << c.nombre << "   COST: ⚡" << c.COST << " [❤" << c.HP << "  ✊" << c.PWR << "]" << endl;
}

void ImprimirTablero() {
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
void Continuar(){
    ImprimirPantalla();

    AgarrarCartaBaraja();
    ImprimirPantalla();

    MenuOpciones();
};
void ContinuarSinAgarrar(){
    ImprimirPantalla();

    ImprimirPantalla();

    MenuOpciones();
};
void ImprimirPantalla(){ //Imprime tablero y mazo completos
    system("cls"); //Limpia la pantalla
    ImprimirVitales();
    ImprimirTablero();
    ImprimirMazo();
}

void DarTurno(){
    ActualizarStamina();

    AccionJugador();
    AccionEnemigo();
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
    cout << "  ♦️ De que baraja quieres agarrar la carta?"<< endl << endl;
    cout << "      Baraja Aleatoria       Baraja Defensa"<< endl;
    cout << "           - 1 -                  - 2 -"<< endl;
    cout << "  >>"; cin >> opc;
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
    cout << "  ♦️ Agarraste la carta:" << endl << endl;
    cout << "      ";
    ImprimirCartaMazo(mazo[numCartasMazo-1]);
    cout << endl << "  >>⌛ ";
    system("pause");
    break;
    }while(true);
}

void UsarCartaMazo(){
    /*Quita una carta del MAZO del jugador */
    ImprimirPantalla();
    int eleccion;
    do{
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
    if (eleccion == 0){break;}

    ImprimirPantalla();
    int pos;

        do{
            cout<<"  ♦️ En que posicion quieres poner la carta?" << endl <<endl<< "     ";
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

void AccionEnemigo(){
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
