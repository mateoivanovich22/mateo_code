#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "dia_en_la_uni.h"
#include "utiles.h" 
#include "papeleo.h"

#define EMOJI_PARED "🧱​"
#define EMOJI_FUEGO "​🔥​"
#define EMOJI_MEDIA "​🧦​"
#define EMOJI_BOTELLA "​🍾​"
#define EMOJI_INTERRUPTOR "​🛎️​"
#define EMOJI_MIKE "​🧑​"

const char FUEGOS = 'F';
const char MEDIAS = 'M';
const char BOTTELAS_DE_GRITOS = 'G';
const char INTERRUPTORES = 'I';
const char MIKE = 'W';
const char PARED = '#';
const char VACIO = ' ';
const int DIMENSION_NVL1 = 22;
const int DIMENSION_NVL2 = 17;
const int DIMENSION_NVL3 = 12;
const char PERSONAJE_OLAF = 'O';
const char PERSONAJE_STITCH = 'S';
const char PERSONAJE_JASMIN = 'J';
const char PERSONAJE_RAYOMCQUEEN = 'R';
const int CANT_OBST_NVL1 = 15;
const int CANT_OBST_NVL2 = 9;
const int CANT_OBST_NVL3 = 6;
const int CANT_HERR_NVL1 = 5;
const int CANT_HERR_NVL2 = 4;
const int CANT_HERR_NVL3 = 2;
const int CANT_PAPELEOS_NVL1 = 2;
const int CANT_PAPELEOS_NVL2 = 3;
const int CANT_PAPELEOS_NVL3 = 4;
const int NIVEL_1 = 1;
const int NIVEL_2 = 2;
const int NIVEL_3 = 3;
const int MOV_NIVEL1 = 40;
const int MOV_NIVEL2 = 30;
const int MOV_NIVEL3 = 20;
const int MARTILLOS_NVL1 = 4;
const int MARTILLOS_NVL2 = 5;
const int MARTILLOS_NVL3 = 6;
const int EXTINTORES_NVL1 = 4;
const int EXTINTORES_NVL2 = 2;
const int EXTINTORES_NVL3 = 2;
const int MOV_NVL1_MAS_OBSEQUIO = 50;

const char MOVER_IZQ = 'A';
const char MOVER_DER = 'D';
const char ABAJO = 'S';
const char UTILIZAR_MARTILLO = 'Z';
const char UTILIZAR_EXTINTOR = 'C';
const char MARTILLAR_ABAJO = 'S';
const char MARTILLAR_O_EXTINGUIR_IZQ = 'A';
const char MARTILLAR_O_EXTINGUIR_DER = 'D';
const char MARTILLAR_O_EXTINGUIR_ARRIBA= 'W';
const char ROTACION_HOR = 'E';
const char ROTACION_ANTIHOR = 'Q';
const int BORDE_IZQ = 0;
const int BORDE_ARRIBA = 0;

const int INTERACCION_MEDIA = 10;
const int INTERACCION_BOTELLA = 7;



/*
 * Funcion que recibe una referencia al nivel actual, que debe ser del 1 al 3, y devuelve la dimension de la matriz
 */
int dimension_de_matriz(int nivel_actual){
    int dimension = 0;
    if(nivel_actual == NIVEL_1){
        dimension = DIMENSION_NVL1;
    }else if(nivel_actual == NIVEL_2){
        dimension = DIMENSION_NVL2;
    }else if(nivel_actual == NIVEL_3){
        dimension = DIMENSION_NVL3;
    }
    return dimension;
}

/*
 * Procedimiento que recibe un nivel (que debe ser del 1 al 3) y una referencia a una posicion, y devolvera una posicion aleatoria
 * dependiendo de la dimension de la matriz
 */
void posicion_aleatoria(int nivel_actual, coordenada_t* posicion){
	(*posicion).fil = rand() % dimension_de_matriz(nivel_actual);
	(*posicion).col = rand() % dimension_de_matriz(nivel_actual);
}

/*
 * Funcion booleana que recibe el nivel, una posicion, y devuelve true si en esa posicion hay algun obstaculo, herramienta
 * papeleo o una pared, y false si en esa posicion no hay nada
 */
bool espacio_ocupado(nivel_t nivel, coordenada_t posicion){
    bool posicion_ocupada = false;
    int i = 0;
    while(i< nivel.tope_obstaculos && posicion_ocupada == false){
        if(nivel.obstaculos[i].posicion.fil == posicion.fil && nivel.obstaculos[i].posicion.col == posicion.col){
            posicion_ocupada = true;
        }
        i++;
    }
    i = 0;
    while(i<nivel.tope_herramientas && posicion_ocupada == false){
         if(nivel.herramientas[i].posicion.fil == posicion.fil && nivel.herramientas[i].posicion.col == posicion.col){
            posicion_ocupada = true;
        }
        i++;
    }
    i = 0;
    while(i < nivel.tope_paredes && posicion_ocupada == false){
        if(nivel.paredes[i].fil == posicion.fil && nivel.paredes[i].col == posicion.col){
            posicion_ocupada = true;
        }
        i++;
    }
    i = 0;
    while(i < nivel.tope_papeleos && posicion_ocupada == false){
        if(nivel.papeleos[i].posicion.fil == posicion.fil && nivel.papeleos[i].posicion.col == posicion.col){
            posicion_ocupada = true;
        }
        i++;
    }
    if(posicion.fil == nivel.pos_inicial_jugador.fil && posicion.col == nivel.pos_inicial_jugador.col){
        posicion_ocupada = true;
    }

    return posicion_ocupada;
}
/*
 * Funcion booleana que al recibir una referencia al nivel, y una posicion, devuelve true si hay una pared adyacente
 * a esa posicion, y false si no hay ninguna
 */
bool posicion_adyacente_a_pared(nivel_t nivel, coordenada_t posicion){ // arreglar y hacerlo con un while
    bool posicion_adyacente = false;
    if(espacio_ocupado(nivel, posicion) == false){
        for(int i = 0; i < nivel.tope_paredes;i++){
            if((posicion.fil == nivel.paredes[i].fil+1) && (posicion.col == nivel.paredes[i].col) ){
                posicion_adyacente = true;
                nivel.tope_paredes = 0;
            }else if((posicion.fil == nivel.paredes[i].fil-1) && (posicion.col == nivel.paredes[i].col)){
                posicion_adyacente = true;
                nivel.tope_paredes = 0;
            }else if((posicion.fil == nivel.paredes[i].fil) && (posicion.col == nivel.paredes[i].col+1)){
                posicion_adyacente = true;
                nivel.tope_paredes = 0;
            }else if((posicion.fil == nivel.paredes[i].fil) && (posicion.col == nivel.paredes[i].col-1)){
                posicion_adyacente = true;
                nivel.tope_paredes = 0;
            }
        }
    }
    return posicion_adyacente;
}

/*
 * Funcion que recibe un nivel (del 1 al 3) y devuelve el tope de obstaculos
 */
int tope_obstaculos(int numero_nivel){
    int tope_total = 0;
    if(numero_nivel == NIVEL_1){
        tope_total = CANT_OBST_NVL1;
    }else if(numero_nivel == NIVEL_2){
        tope_total = CANT_OBST_NVL2;
    }else{
        tope_total = CANT_OBST_NVL3;
    }
    return tope_total;
}
/*
 * pre: recibe una referencia al nivel, el nivel actual, y el personaje del tp1
 * post: dependiendo del personaje y el nivel, aplicara el obsequio
 */
void sumar_regalo(nivel_t* nivel, int nivel_actual,  char personaje_tp1){
    if((personaje_tp1 == PERSONAJE_OLAF) && (nivel_actual == NIVEL_1)){
        (*nivel).tope_obstaculos -=2;
    }else if((personaje_tp1 == PERSONAJE_OLAF) && (nivel_actual == NIVEL_2)){
        (*nivel).tope_obstaculos--;
    }
}

/*
 * Procedimiento que recibe una referencia al nivel, un nivel(debe ser del 1 al 3), una referencia al tope_obstaculos
 * (debe estar inicializado en 0), un obstaculo, y el personaje del tp1. Cargara el vector de obstaculos, con la posicion
 *  aleatoria y valida, y dependiendo del nivel y el personaje, aplicara el "obsequio".
 */
void cargar_obstaculos(nivel_t* nivel, int numero_nivel, int* tope_obstaculo, char obstaculo, char personaje_tp1){
    char obstaculo_actual = MEDIAS;
    coordenada_t posicion_obstaculo;
    int tope_total = tope_obstaculos(numero_nivel);
    for(int i = 0; i < tope_total;i++){
        if ((numero_nivel == NIVEL_1 && i == 5) || (numero_nivel == NIVEL_2 && i == 4) || (numero_nivel == NIVEL_3 && i == 3)){
            obstaculo_actual = FUEGOS;
        }   
        (*nivel).obstaculos[i].tipo = obstaculo_actual;
        if(obstaculo_actual == FUEGOS){
            posicion_aleatoria(numero_nivel ,&posicion_obstaculo);
            while((posicion_adyacente_a_pared((*nivel), posicion_obstaculo) == false)){
                posicion_aleatoria(numero_nivel, &posicion_obstaculo); 
            }            
        }else if(obstaculo_actual == MEDIAS){
            while((espacio_ocupado((*nivel), posicion_obstaculo) == true)){
                posicion_aleatoria(numero_nivel, &posicion_obstaculo);
            }
        }
        (*nivel).obstaculos[i].posicion.fil = posicion_obstaculo.fil;
        (*nivel).obstaculos[i].posicion.col = posicion_obstaculo.col;
        (*nivel).tope_obstaculos++;
    }
    sumar_regalo(&(*nivel), numero_nivel, personaje_tp1);
}

/*
 * Funcion que recibe un nivel (del 1 al 3) y devuelve el tope de herramientas
 */
int tope_herramientas(int numero_nivel){
    int tope_total = 0;
    if(numero_nivel == NIVEL_1){
        tope_total = CANT_HERR_NVL1;
    }else if(numero_nivel == NIVEL_2){
        tope_total = CANT_HERR_NVL2;
    }else{
        tope_total =CANT_HERR_NVL3;
    }
    return tope_total;
}

/*
 * Procedimiento que recibe una referencia al nivel, un nivel(debe ser del 1 al 3), una referencia al tope_herramientas
 * (debe estar inicializado en 0), y una herramienta. Cargara el vector de herramientas, con la posicion
 *  aleatoria y valida.
 */
void cargar_herramientas(nivel_t* nivel, int numero_nivel, int* tope_herramienta, char herramienta){
    char herramienta_actual = BOTTELAS_DE_GRITOS;
    coordenada_t posicion_herramienta;
    int tope_total = tope_herramientas(numero_nivel);
    for(int i = 0; i < tope_total;i++){
        if ((numero_nivel == NIVEL_1 && i == 4) || (numero_nivel == NIVEL_2 && i == 3) || (numero_nivel == NIVEL_3 && i == 2)){
            herramienta_actual = INTERRUPTORES;
        }    
        (*nivel).herramientas[i].tipo = herramienta_actual;
        posicion_aleatoria(numero_nivel ,&posicion_herramienta);

        while((espacio_ocupado((*nivel), posicion_herramienta) == true)){
            posicion_aleatoria(numero_nivel, &posicion_herramienta);
        }
        (*nivel).herramientas[i].posicion.fil = posicion_herramienta.fil;
        (*nivel).herramientas[i].posicion.col = posicion_herramienta.col;
        (*nivel).tope_herramientas++;
    }
}

/*
 * Funcion que recibe un nivel (del 1 al 3) y devuelve el tope de papeleos
 */
int tope_papeleo(int numero_nivel){
    int tope = 0;
    if(numero_nivel == NIVEL_1){
        tope = CANT_PAPELEOS_NVL1;
    }else if(numero_nivel == NIVEL_2){   
        tope = CANT_PAPELEOS_NVL2;
    }else{
        tope = CANT_PAPELEOS_NVL3;
    }
    return tope;
}

/*
 * Procedimiento que recibira una referencia del struct nivel_t, un nivel (debe ser del 1 al 3), una referencia al tope_papeleos
 * (debe estar inicializado en 0), y un personaje. Cargara el vector de papeleos, con la posicion aleatoria y valida
 */
void cargar_papeleos(nivel_t* nivel, int numero_nivel, int* tope_papeleos, char personaje_tp1){
    coordenada_t posicion_papeleo;
    int tope = tope_papeleo(numero_nivel);
    for(int i = 0;i < tope ;i++){
        posicion_aleatoria(numero_nivel, &posicion_papeleo);
        while((espacio_ocupado((*nivel), posicion_papeleo) == true)){
            posicion_aleatoria(numero_nivel, &posicion_papeleo);
        }
        (*nivel).papeleos[i].id_papeleo = i;
        (*nivel).papeleos[i].recolectado = false;
        (*nivel).papeleos[i].posicion.fil = posicion_papeleo.fil;
        (*nivel).papeleos[i].posicion.col = posicion_papeleo.col;
        (*nivel).tope_papeleos++;
    }
    if((personaje_tp1 == PERSONAJE_STITCH) && (numero_nivel == NIVEL_3)){
        (*nivel).tope_papeleos--;
    }
}

/*
 * Procedimiento que recibira una referencia del juego y llenara el struct jugador_t
 */
void inicializar_jugador(jugador_t* jugador,int nivel_actual, char personaje_tp1){ 
    int movimientos_nivel_anterior = (*jugador).movimientos - (*jugador).movimientos_realizados;
    if(nivel_actual == NIVEL_1){
        (*jugador).extintores = EXTINTORES_NVL1;
        (*jugador).martillos = MARTILLOS_NVL1;
        if(personaje_tp1 == PERSONAJE_RAYOMCQUEEN){
            (*jugador).movimientos = MOV_NVL1_MAS_OBSEQUIO;    
        }else{
            (*jugador).movimientos =MOV_NIVEL1;
        }
    }else if(nivel_actual == NIVEL_2){
        (*jugador).movimientos = MOV_NIVEL2 + movimientos_nivel_anterior;
        (*jugador).extintores = EXTINTORES_NVL2;
        (*jugador).martillos = MARTILLOS_NVL2;
    }else{
        (*jugador).movimientos = MOV_NIVEL3 + movimientos_nivel_anterior;
        (*jugador).extintores = EXTINTORES_NVL3;
        (*jugador).martillos = MARTILLOS_NVL3;
    }
    if(personaje_tp1 == PERSONAJE_JASMIN){
        (*jugador).martillos += 1;
    }

}

/* 
 * Procedimiento que recibe el juego e imprime toda su información por pantalla.
 */

void imprimir_terreno(juego_t juego){
    int dimension = dimension_de_matriz(juego.nivel_actual);
    char matriz[dimension][dimension];
    printf("\nNivel: %i\n\n", juego.nivel_actual);
    for(int i = 0; i < dimension;i++){
        for(int j = 0; j< dimension; j++){
            matriz[i][j] = VACIO;          
        }     
    }
    for(int i = 0; i < juego.niveles[juego.nivel_actual-1].tope_paredes; i++){
        matriz[juego.niveles[juego.nivel_actual-1].paredes[i].fil][juego.niveles[juego.nivel_actual-1].paredes[i].col] = PARED;
    }
    for(int i = 0; i < juego.niveles[juego.nivel_actual-1].tope_obstaculos ;i++){
        matriz[juego.niveles[juego.nivel_actual-1].obstaculos[i].posicion.fil][juego.niveles[juego.nivel_actual-1].obstaculos[i].posicion.col] = juego.niveles[juego.nivel_actual-1].obstaculos[i].tipo;
    }
    for(int i = 0; i < juego.niveles[juego.nivel_actual-1].tope_herramientas; i++){
        matriz[juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.fil][juego.niveles[juego.nivel_actual-1].herramientas[i].posicion.col] = juego.niveles[juego.nivel_actual-1].herramientas[i].tipo;
    }
    for(int i = 0; i < juego.niveles[juego.nivel_actual-1].tope_papeleos; i++){
        if(juego.niveles[juego.nivel_actual-1].papeleos[i].recolectado == false){
            matriz[juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.fil][juego.niveles[juego.nivel_actual-1].papeleos[i].posicion.col] = (char)(juego.niveles[juego.nivel_actual-1].papeleos[i].id_papeleo + 49);
        }
    }
    matriz[juego.jugador.posicion.fil][juego.jugador.posicion.col] = MIKE;
    for(int i = 0; i < dimension;i++){
        for(int j = 0; j < dimension;j++){ 
            if(matriz[i][j] == PARED){
                printf("%s", EMOJI_PARED);
            }else if(matriz[i][j] == INTERRUPTORES){
                printf(" %s", EMOJI_INTERRUPTOR);
            }else if(matriz[i][j] == BOTTELAS_DE_GRITOS){
                printf("%s", EMOJI_BOTELLA);
            }else if(matriz[i][j] == MEDIAS){
                printf("%s", EMOJI_MEDIA);
            }else if(matriz[i][j] == FUEGOS){
                printf("%s", EMOJI_FUEGO);
            }else if(matriz[i][j] == MIKE){
                printf("%s", EMOJI_MIKE);
            }else if(matriz[i][j] == VACIO){
                printf(" %c", matriz[i][j]);
            }else{
                printf(" %c", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

/* 
 * Inicializará un nivel, cargando toda la información inicial, las paredes,
 * los objetos, los papeleos y la posición inicial del jugador en dicho nivel.
 */
void inicializar_nivel(nivel_t* nivel, int numero_nivel, char personaje_tp1){
    (*nivel).tope_herramientas = 0;
    (*nivel).tope_papeleos = 0;
    (*nivel).tope_paredes = 0;
    (*nivel).tope_obstaculos = 0;

    obtener_paredes(numero_nivel, (*nivel).paredes, &(*nivel).tope_paredes, &(*nivel).pos_inicial_jugador);
    cargar_herramientas(&(*nivel), numero_nivel, &(*nivel).tope_herramientas, (*nivel).herramientas->tipo);
    cargar_papeleos(&(*nivel), numero_nivel, &(*nivel).tope_papeleos, personaje_tp1);
    cargar_obstaculos(&(*nivel), numero_nivel, &(*nivel).tope_obstaculos, (*nivel).obstaculos->tipo, personaje_tp1);
}

/*
 * Inicializará el juego, cargando toda la información inicial, los datos del jugador, 
 * el personaje resultado del tp anterior, y los 3 niveles. El campo "nivel_actual"
 * comienza en 1.
 */
void inicializar_juego(juego_t* juego, char personaje_tp1){
    //(*juego).nivel_actual = NIVEL_1;
    (*juego).jugador.ahuyenta_randall = false;
    (*juego).personaje_tp1 = personaje_tp1;
    (*juego).jugador.movimientos_realizados = 0;
    inicializar_nivel(&(*juego).niveles[0], NIVEL_1, (*juego).personaje_tp1);
    inicializar_nivel(&(*juego).niveles[1], NIVEL_2, (*juego).personaje_tp1);
    inicializar_nivel(&(*juego).niveles[2], NIVEL_3, (*juego).personaje_tp1);
    (*juego).jugador.posicion = (*juego).niveles[(*juego).nivel_actual-1].pos_inicial_jugador;
    inicializar_jugador(&(*juego).jugador,(*juego).nivel_actual, (*juego).personaje_tp1);
}

/*
 * Funcion booleana que recibe una accion y devuelve TRUE si es valida
 */
bool es_accion_valida(char accion){
    
    return ((accion == MOVER_IZQ) || (accion == MOVER_DER) || (accion == ROTACION_HOR) || (accion == ROTACION_ANTIHOR) ||
             (accion == UTILIZAR_MARTILLO) || (accion == UTILIZAR_EXTINTOR));
}

/*
 * Funcion booleana que recibe una accion y devuelve TRUE si es valida
 */
bool es_accion_valida_herr(char accion){
    
    return ((accion == MARTILLAR_O_EXTINGUIR_DER) || (accion == MARTILLAR_O_EXTINGUIR_IZQ) || (accion == MARTILLAR_ABAJO)
             || (accion == MARTILLAR_O_EXTINGUIR_ARRIBA));
}

/*
 * pre: recibe una referencia a la accion
 * post: en caso de no ser valida la accion, se volvera a pedirlo hasta ser valida
 */
void pedir_movimiento(char* ref_accion){
    printf("Ingrese una acción: \n");
    scanf(" %c", ref_accion);
    
    while (!es_accion_valida(*ref_accion)){
        scanf(" %c", ref_accion);
    }
}

/*
 * pre: recibe una referencia a la accion
 * post: en caso de no ser valida la accion, se volvera a pedirlo hasta ser valida
 */
void indicar_uso_herr(char* ref_accion){
    if((*ref_accion) == UTILIZAR_MARTILLO){
        printf("Ingrese donde quiere usar su martillo: \n");
    }else if((*ref_accion) == UTILIZAR_EXTINTOR){
        printf("Ingrese donde quiere usar su extintor: \n");
    }
    scanf(" %c", ref_accion);
    
    while (!es_accion_valida_herr(*ref_accion)){
        scanf(" %c", ref_accion);
    }
}

/*
 * Funcion booleana que recibe el juego, una coordenada y devuelve TRUE si el personaje tiene debajo una pared
 */
bool gravedad(juego_t juego, coordenada_t jugador){
    bool hay_pared = false;
    int i = 0;

    while(i < juego.niveles[juego.nivel_actual-1].tope_paredes && hay_pared == false){
        if(((jugador.fil+1) == (juego.niveles[juego.nivel_actual-1].paredes[i].fil)) && 
            (jugador.col == juego.niveles[juego.nivel_actual-1].paredes[i].col)){
            hay_pared = true;
        }
        i++;
    }
    return hay_pared;
}

/*
 * Funcion booleana que recibe el juego, una coordenada y devuelve TRUE si la coordenada pertenece a una pared del borde
 */
bool pared_borde(juego_t juego, coordenada_t pared){
    int dimension = dimension_de_matriz(juego.nivel_actual) - 1;;
    bool pared_limite = false;

    if(pared.fil == BORDE_ARRIBA || pared.col == BORDE_IZQ || pared.fil == dimension || pared.col == dimension){
        pared_limite = true;
    }

    return pared_limite;
}

/*
 * Funcion booleana que recibe el juego, una coordenada y devuelve TRUE si la coordenada del jugador tiene una pared en alguno de los laterales
 */
bool pared_al_lado(juego_t juego, coordenada_t jugador, char movimiento){
    bool hay_una_pared = false;
    int i = 0;
    while (i < juego.niveles[juego.nivel_actual-1].tope_paredes && hay_una_pared == false){
        if(((jugador.fil == juego.niveles[juego.nivel_actual-1].paredes[i].fil) && (jugador.col+1 == juego.niveles[juego.nivel_actual-1].paredes[i].col))&&
            movimiento == MOVER_DER){
            hay_una_pared = true;
        }else if(((jugador.fil == juego.niveles[juego.nivel_actual-1].paredes[i].fil) && (jugador.col-1 == juego.niveles[juego.nivel_actual-1].paredes[i].col))&&
                    movimiento == MOVER_IZQ){
            hay_una_pared = true;
        }
        i++;
    }
    
    return hay_una_pared;
}

/*
 * pre: recibe una referencia al juego y un movimiento
 * post: en caso de poder usar el martillo en una pared disponible, cumplira su funcion; borrarla y resta un martillo, siempre y
 *       cuando haya martillos disponibles
 */
void usar_martillo(juego_t* juego, char movimiento){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_paredes; i++){
        if(pared_borde((*juego), (*juego).niveles[(*juego).nivel_actual-1].paredes[i]) == false){
            if(movimiento == MARTILLAR_ABAJO && ((*juego).niveles[(*juego).nivel_actual-1].paredes[i].fil == (*juego).jugador.posicion.fil+1 &&
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i].col == (*juego).jugador.posicion.col)){
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i] = (*juego).niveles[(*juego).nivel_actual-1].paredes[(*juego).niveles[(*juego).nivel_actual-1].tope_paredes-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_paredes--;
                (*juego).jugador.martillos--;

            }else if(movimiento == MARTILLAR_O_EXTINGUIR_DER && ((*juego).niveles[(*juego).nivel_actual-1].paredes[i].fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i].col == (*juego).jugador.posicion.col+1)){
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i] = (*juego).niveles[(*juego).nivel_actual-1].paredes[(*juego).niveles[(*juego).nivel_actual-1].tope_paredes-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_paredes--;
                (*juego).jugador.martillos--;

            }else if(movimiento == MARTILLAR_O_EXTINGUIR_IZQ && ((*juego).niveles[(*juego).nivel_actual-1].paredes[i].fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i].col == (*juego).jugador.posicion.col-1)){
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i] = (*juego).niveles[(*juego).nivel_actual-1].paredes[(*juego).niveles[(*juego).nivel_actual-1].tope_paredes-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_paredes--;
                (*juego).jugador.martillos--;

            }else if(movimiento == MARTILLAR_O_EXTINGUIR_ARRIBA && ((*juego).niveles[(*juego).nivel_actual-1].paredes[i].fil == (*juego).jugador.posicion.fil-1 &&
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i].col == (*juego).jugador.posicion.col)){
                (*juego).niveles[(*juego).nivel_actual-1].paredes[i] = (*juego).niveles[(*juego).nivel_actual-1].paredes[(*juego).niveles[(*juego).nivel_actual-1].tope_paredes-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_paredes--;
                (*juego).jugador.martillos--;
            }
        }
    }
}

/*
 * pre: recibe una referencia al juego y un movimiento
 * post: en caso de poder usar el extintor en un fuego disponible, cumplira su funcion; borrarlo y resta un extintor, siempre y
 *       cuando haya extintores disponibles
 */
void usar_extintor(juego_t* juego, char movimiento){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos;i++){
        if((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].tipo == FUEGOS){
            if(movimiento == MARTILLAR_O_EXTINGUIR_ARRIBA && ((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.fil == (*juego).jugador.posicion.fil-1 &&
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.col == (*juego).jugador.posicion.col)){
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i] = (*juego).niveles[(*juego).nivel_actual-1].obstaculos[(*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos--;
                (*juego).jugador.extintores--;

            }else if(movimiento == MARTILLAR_O_EXTINGUIR_DER && ((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.col == (*juego).jugador.posicion.col+1)){
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i] = (*juego).niveles[(*juego).nivel_actual-1].obstaculos[(*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos--;
                (*juego).jugador.extintores--;

            }else if(movimiento == MARTILLAR_O_EXTINGUIR_IZQ && ((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.col == (*juego).jugador.posicion.col-1)){
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i] = (*juego).niveles[(*juego).nivel_actual-1].obstaculos[(*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos-1];
                (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos--;
                (*juego).jugador.extintores--;
            }
        }
    }
}

/*
 * pre: recibe una referencia al juego
 * post: en caso de que el personaje tenga la misma coordenada que algun obstaculo, pedendiendo del obstaculo, hara lo que deba
 */
void interaccion_obstaculo(juego_t* juego){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos;i++){
        if((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].tipo == FUEGOS){
            if((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.col == (*juego).jugador.posicion.col){
                (*juego).jugador.movimientos = 0;
            }
        }else if((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].tipo == MEDIAS){
            if((*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion.col == (*juego).jugador.posicion.col){
                (*juego).jugador.movimientos -= INTERACCION_MEDIA;
            }
        }
    }
}

/*
 * pre: recibe una referencia al juego
 * post: en caso de que el personaje tenga la misma coordenada que alguna herramienta, pedendiendo de la herramienta, hara lo que deba
 */
void interaccion_herramienta(juego_t* juego){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_herramientas;i++){
        if((*juego).niveles[(*juego).nivel_actual-1].herramientas[i].tipo == BOTTELAS_DE_GRITOS){
            if((*juego).niveles[(*juego).nivel_actual-1].herramientas[i].posicion.fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].herramientas[i].posicion.col == (*juego).jugador.posicion.col){
                (*juego).jugador.movimientos+= INTERACCION_BOTELLA;
            }
        }else if((*juego).niveles[(*juego).nivel_actual-1].herramientas[i].tipo == INTERRUPTORES){
            if((*juego).niveles[(*juego).nivel_actual-1].herramientas[i].posicion.fil == (*juego).jugador.posicion.fil &&
                (*juego).niveles[(*juego).nivel_actual-1].herramientas[i].posicion.col == (*juego).jugador.posicion.col){
                if((*juego).jugador.ahuyenta_randall == false){
                    (*juego).jugador.ahuyenta_randall = true;
                }else if((*juego).jugador.ahuyenta_randall == true){
                    (*juego).jugador.ahuyenta_randall = false;
                } 
            }
        }
    }
}

/*
 * pre: recibe una referencia al juego
 * post: en caso de que el personaje tenga la misma coordenada que algun papeleo, si el papeleo anterior no fue recolectado, no lo agarrara
 */
void interaccion_papeleos(juego_t* juego){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_papeleos;i++){
        if((*juego).niveles[(*juego).nivel_actual-1].papeleos[i].posicion.fil == (*juego).jugador.posicion.fil &&
            (*juego).niveles[(*juego).nivel_actual-1].papeleos[i].posicion.col == (*juego).jugador.posicion.col){

            if((*juego).niveles[(*juego).nivel_actual-1].papeleos[i].id_papeleo == 0){
                (*juego).niveles[(*juego).nivel_actual-1].papeleos[i].recolectado = true;

            }else if((*juego).niveles[(*juego).nivel_actual-1].papeleos[i].id_papeleo != 0){
                if((*juego).niveles[(*juego).nivel_actual-1].papeleos[i-1].recolectado == true){
                    (*juego).niveles[(*juego).nivel_actual-1].papeleos[i].recolectado = true;                   
                }
            }            
        }
    }
}

/*
 * pre: recibe una referencia a una coordenada, y el nivel actual
 * post: modificara la coordenada recibida, en funcion de rotar la matriz en sentido horario
 */
void rotacion_hor(coordenada_t* coordenada, int nivel_actual){
    int dimension = dimension_de_matriz(nivel_actual) -2;
    int guardar_valor = 0;
    guardar_valor = (*coordenada).fil;
    (*coordenada).fil = (*coordenada).col;
    (*coordenada).col = abs(guardar_valor - dimension -1);
    
}

/*
 * pre: recibe una referencia al juego
 * post: recorrera todas las paredes, obstaculos, herramientas y papeleos, y rotara las mismas
 */
void rotar_mapa_horario(juego_t* juego){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_paredes;i++){
        rotacion_hor(&(*juego).niveles[(*juego).nivel_actual-1].paredes[i], (*juego).nivel_actual);
    }
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos; i++){
        rotacion_hor(&(*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion, (*juego).nivel_actual);
    }
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_herramientas;i++){
        rotacion_hor(&(*juego).niveles[(*juego).nivel_actual-1].herramientas[i].posicion, (*juego).nivel_actual);
    }
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_papeleos;i++){
        rotacion_hor(&(*juego).niveles[(*juego).nivel_actual-1].papeleos[i].posicion, (*juego).nivel_actual);
    }
    rotacion_hor(&(*juego).jugador.posicion, (*juego).nivel_actual);
}

/*
 * pre: recibe una referencia a una coordenada, y el nivel actual
 * post: modificara la coordenada recibida, en funcion de rotar la matriz en sentido antihorario
 */
void rotacion_anti(coordenada_t* coordenada, int nivel_actual){
    int dimension = dimension_de_matriz(nivel_actual) -2;
    int guardar_valor = 0;
    guardar_valor = (*coordenada).fil;
    (*coordenada).fil = abs((*coordenada).col - dimension - 1);
    (*coordenada).col = guardar_valor;
    
}

/*
 * pre: recibe una referencia al juego
 * post: recorrera todas las paredes, obstaculos, herramientas y papeleos, y rotara las mismas
 */
void rotar_mapa_antihorario(juego_t* juego){
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_paredes;i++){
        rotacion_anti(&(*juego).niveles[(*juego).nivel_actual-1].paredes[i], (*juego).nivel_actual);
    }
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_obstaculos; i++){
        rotacion_anti(&(*juego).niveles[(*juego).nivel_actual-1].obstaculos[i].posicion, (*juego).nivel_actual);
    }
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_herramientas;i++){
        rotacion_anti(&(*juego).niveles[(*juego).nivel_actual-1].herramientas[i].posicion, (*juego).nivel_actual);
    }
    for(int i = 0; i < (*juego).niveles[(*juego).nivel_actual-1].tope_papeleos;i++){
        rotacion_anti(&(*juego).niveles[(*juego).nivel_actual-1].papeleos[i].posicion, (*juego).nivel_actual);
    }
    rotacion_anti(&(*juego).jugador.posicion, (*juego).nivel_actual);
}

/*
 * pre: recibe una referencia al juego
 * post: aumentara el tope de paredes, y creara una pared en una posicion random aleatoria
 */
void crear_pared_aleatoria(juego_t* juego){
    (*juego).niveles[(*juego).nivel_actual-1].tope_paredes++;
    coordenada_t posicion_random;
    for(int i = (*juego).niveles[(*juego).nivel_actual-1].tope_paredes-1; i < (*juego).niveles[(*juego).nivel_actual-1].tope_paredes;i++){
        posicion_aleatoria((*juego).nivel_actual, &posicion_random);
        while(espacio_ocupado((*juego).niveles[(*juego).nivel_actual-1], posicion_random) == true){
            posicion_aleatoria((*juego).nivel_actual, &posicion_random);
        }
        (*juego).niveles[(*juego).nivel_actual-1].paredes[i].fil = posicion_random.fil;
        (*juego).niveles[(*juego).nivel_actual-1].paredes[i].col = posicion_random.col;
    }

}

/*
 * pre: recibe una referencia al juego
 * post: creara las paredes necesarias segun el nivel
 */
void crear_paredes_por_nivel(juego_t* juego){
    if((*juego).nivel_actual == 1 && (*juego).jugador.movimientos_realizados <= 40){
        crear_pared_aleatoria(&(*juego));
    }else if((*juego).nivel_actual == 2 && (*juego).jugador.movimientos_realizados <= 30){
        crear_pared_aleatoria(&(*juego));
    }else if((*juego).nivel_actual == 3 && (*juego).jugador.movimientos_realizados <= 20){
        crear_pared_aleatoria(&(*juego));
    }
}

/*
 * Funcion que recibe el nivel actual, y dependiendo de eso devuelve la divisibilidad de randall
 */
int divisible_randall(int nivel){
    int divisibilidad = 0;
    if(nivel == 1){
        divisibilidad = 7;
    }else if(nivel== 2){
        divisibilidad = 5;
    }else if(nivel == 3){
        divisibilidad = 3;
    }

    return divisibilidad;        
}

/*
 * pre: recibe una referencia al juego
 * post: si el ahuyenta randall esta desactivado y cumple todos los requisitos, se movera el papeleo a una posicion random valida
 */
void randall(juego_t* juego){
    int divisibilidad = divisible_randall((*juego).nivel_actual);
    bool papeleo_cambiado = false;
    int i = 0;
    coordenada_t posicion_random;
    if((*juego).jugador.movimientos_realizados != 0){
        if((*juego).jugador.ahuyenta_randall == false){
            if((*juego).jugador.movimientos_realizados % divisibilidad == 0){
                while(i < (*juego).niveles[(*juego).nivel_actual-1].tope_papeleos && papeleo_cambiado == false){
                    if((*juego).niveles[(*juego).nivel_actual-1].papeleos[i].recolectado == false){
                        papeleo_cambiado = true;
                        posicion_aleatoria((*juego).nivel_actual, &posicion_random);
                        while(espacio_ocupado((*juego).niveles[(*juego).nivel_actual-1], posicion_random) == true){
                            posicion_aleatoria((*juego).nivel_actual, &posicion_random);
                        }
                        (*juego).niveles[(*juego).nivel_actual-1].papeleos[i].posicion.fil = posicion_random.fil;
                        (*juego).niveles[(*juego).nivel_actual-1].papeleos[i].posicion.col = posicion_random.col;
                    }
                    i++;
                }
            }
        }
    }
}

/*
 * pre: recibe una referencia al juego
 * post: llama a todos los procedimientos de interacciones
 */
void interacciones_jugador(juego_t* juego){
    interaccion_obstaculo(&(*juego));
    interaccion_herramienta(&(*juego));
    interaccion_papeleos(&(*juego));
}

/*
 * pos: recibe una referencia al juego
 * post: resta un movimiento y suma uno al contador de movimientos realizados
 */
void restar_movimiento(juego_t* juego){
    (*juego).jugador.movimientos--;
    (*juego).jugador.movimientos_realizados++;
}

/*
 * pos: recibe una referencia al juego y un caracter(movimiento)
 * post: dependiendo del movimiento y si esta en forma de ejecutarlo, modificara las coordenadas hasta cumplir con el movimiento
 */
void mover_lateralmente(juego_t* juego, char movimiento){
    if(movimiento == MOVER_DER && pared_al_lado((*juego), (*juego).jugador.posicion, movimiento) == false){
        (*juego).jugador.posicion.col+=1;
        while(gravedad((*juego), (*juego).jugador.posicion) == false){
            (*juego).jugador.posicion.fil++;
            interacciones_jugador(&(*juego));           
        }
        restar_movimiento(&(*juego));
        crear_paredes_por_nivel(&(*juego));
    }else if(movimiento == MOVER_IZQ && pared_al_lado((*juego), (*juego).jugador.posicion, movimiento) == false){
        (*juego).jugador.posicion.col-=1;        
        while(gravedad((*juego), (*juego).jugador.posicion) == false){
            (*juego).jugador.posicion.fil++;
            interacciones_jugador(&(*juego)); 
        }      
        restar_movimiento(&(*juego));
        crear_paredes_por_nivel(&(*juego));
    }
}

/*
 * pre: recibe una referencia al juego y un caracter(movimiento)
 * post: dependiendo del movimiento y si se puede ejecutar, llamara a otras funciones/procedimientos 
 *       para hacer lo que corresponda segun la herramienta
 */
void utilizar_herramientas(juego_t* juego, char movimiento){
    if((movimiento == UTILIZAR_MARTILLO && (*juego).jugador.martillos>0) || (movimiento == UTILIZAR_EXTINTOR && (*juego).jugador.extintores>0)){
        if(movimiento == UTILIZAR_MARTILLO){
            indicar_uso_herr(&movimiento);
            usar_martillo(&(*juego), movimiento);
            while(gravedad((*juego), (*juego).jugador.posicion) == false){
                (*juego).jugador.posicion.fil++;  
                interacciones_jugador(&(*juego));    
            }
            
        }else if(movimiento == UTILIZAR_EXTINTOR){
            indicar_uso_herr(&movimiento);
            usar_extintor(&(*juego), movimiento);
        }         
    }
}

/*
 * pre: recibe una referencia al juego, un movimiento
 * post: dependiendo del movimiento, rotara el mapa segun el sentido pedido en el movimiento, y aplicara la gravedad en caso necesario
 */
void rotacion_de_mapa(juego_t* juego, char movimiento){
    if(movimiento == ROTACION_HOR){
        rotar_mapa_horario(&(*juego));
        while(gravedad((*juego), (*juego).jugador.posicion) == false){
            (*juego).jugador.posicion.fil++; 
            interacciones_jugador(&(*juego));           
        }
        restar_movimiento(&(*juego));
    }else if(movimiento == ROTACION_ANTIHOR){
        rotar_mapa_antihorario(&(*juego));
        while(gravedad((*juego), (*juego).jugador.posicion) == false){
            (*juego).jugador.posicion.fil++; 
            interacciones_jugador(&(*juego));           
        }
        restar_movimiento(&(*juego));
    }
}

/*
 * pos: recibe una referencia al juego, y un movimiento
 * post: llamara a la funciones/procedimientos dependiendo del movimiento, aplicara la interaccion en caso de chocar algun objeto, y 
 *       al procedimiento randall, que funcionara en caso de que cumpla los requisitos
 */
void mover_personaje(juego_t* juego, char movimiento){
    mover_lateralmente(&(*juego), movimiento);
    utilizar_herramientas(&(*juego), movimiento);
    rotacion_de_mapa(&(*juego), movimiento);
    interacciones_jugador(&(*juego));
    randall(&(*juego));
}


/*
 * El nivel se dará por terminado , si se reolectan todos los papeleos en el mismo.
 * Devolverá:
 * -> 0 si el estado es jugando.
 * -> 1 si el estado es ganado.
 */
int estado_nivel(papeleo_t papeleos[MAX_PAPELEOS], int tope_papeleos){
    int conteo_papeleos = 0;
    int estado_juego = 0;
    for(int i = 0; i < tope_papeleos;i++){
        if(papeleos[i].recolectado == true){
            conteo_papeleos++;
        }
    }
    if(conteo_papeleos == tope_papeleos){
        estado_juego = 1;
    }
    return estado_juego;
}

/*
 * Recibe un juego con todas sus estructuras válidas.
 *
 * El juego se dará por ganado , si terminó todos los niveles. O perdido , si el personaje queda
 * sin movimientos.
 * Devolverá:
 * -> 0 si el estado es jugando.
 * -> -1 si el estado es perdido.
 * -> 1 si el estado es ganado.
 */
int estado_juego(juego_t juego){
    int estado_nivel_actual = estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos, juego.niveles[juego.nivel_actual-1].tope_papeleos);
    int estado = 0;
    if(juego.nivel_actual == 1){
        if(juego.jugador.movimientos <= 0){
            estado = -1;
        }
    }else if(juego.nivel_actual == 2){
        if(juego.jugador.movimientos <= 0){
           estado = -1;
        }
    }else{
        if(juego.jugador.movimientos <= 0){
            estado = -1;
        }
    }
    if(juego.nivel_actual == 3){
        if(estado_nivel_actual == 1){
            estado = 1;
        }
    }
    return estado;
}

/*
 * Moverá el personaje , y realizará la acción necesaria en caso de chocar con un elemento
 */
void realizar_jugada(juego_t* juego){
    char movimiento = ' '; 
    imprimir_terreno((*juego));
    printf("Movimientos disponibles: %i\n", (*juego).jugador.movimientos);
    printf("Movimientos realizados: %i\n", (*juego).jugador.movimientos_realizados);
    printf("Martillos disponibles: %i\n", (*juego).jugador.martillos);
    printf("Extintores disponibles: %i\n", (*juego).jugador.extintores);
    if((*juego).jugador.ahuyenta_randall == false && (*juego).nivel_actual != 3){
        printf("Ahuyenta randall DESACTIVADO\n");
    }else if((*juego).jugador.ahuyenta_randall == true && (*juego).nivel_actual != 3){
        printf("Ahuyenta randall ACTIVADO\n");
    }
    printf("\nMovimientos: izquierda(A), derecha(D)\n");
    printf("Rotar mapa: antihorario(Q), horario(E)\n");
    printf("Romper pared: (Z), e indicar donde, (A,S,D,W) \n");
    printf("Apagar fuego: (C), e indicar donde, (A,S,D,W\n");
    pedir_movimiento(&movimiento);
    mover_personaje(juego, movimiento);
}

