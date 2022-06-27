#include <stdio.h>
#include "dia_en_la_uni.h"

const char OLAF = 'O';
const char STITCH = 'S';
const char JASMIN = 'J';
const char RAYOMCQUEEN = 'R';
const char TRINEO = 'T';
const char NAVE_ESPACIAL = 'N';
const char CAMION = 'C';
const char ALFOMBRA = 'A';
const char BOLAS_DE_NIEVE = 'B';
const char PIUM_PIUM = 'P';
const char KUCHAU = 'K';
const char GENIO = 'G';
const double LLEGAR_TARDE = 15.31;



void pregunta_transporte(char* respuesta1){
    printf("(1) Estás saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegís?\n");
    printf("Las respuestas pueden ser: Trineo (T), Nave Espacial (N), Camión (C) o Alfombra (A).\n");
    scanf(" %c", respuesta1);
    while ((*respuesta1) != TRINEO && (*respuesta1) != NAVE_ESPACIAL && (*respuesta1) != CAMION && (*respuesta1) != ALFOMBRA){
        printf("No existe esa opcion!\n");
        scanf(" %c", respuesta1);
    }   
}

void pregunta_arma(char* respuesta2){
    printf("\n(2) En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    printf("Las respuestas pueden ser: Bolas de nieve (B), Pium pium (P), Kuchau (K) o Genio (G).\n");
    scanf(" %c", respuesta2);
    while ((*respuesta2) != BOLAS_DE_NIEVE && (*respuesta2) != PIUM_PIUM && (*respuesta2) != KUCHAU && (*respuesta2) != GENIO){
        printf("No existe esa opcion!\n");
        scanf(" %c", respuesta2);
    }  
}

void pregunta_hora(float* respuesta3){
    printf("\n(3) Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
    printf("El formato de la hora es: La parte entera representa la hora y La parte decimal representa los minutos.\n");
    scanf("%f", respuesta3);
    int parte_entera = (int)(*respuesta3);
    float decimal = (*respuesta3) - ((float)parte_entera);
    while ((*respuesta3 > 23.59 || *respuesta3 < 0) || (decimal > 0.59 || decimal < 0.00)){
        printf("No existe esa opcion!\n");
        scanf("%f", respuesta3);
        parte_entera = (int)(*respuesta3);
        decimal = (*respuesta3) - ((float)parte_entera);
    }
}

void pregunta_nota(int* respuesta4){
    printf("\n(4) Por fin llegó la nota del parcial! ¿Qué nota lograste sacarte del 1 al 10?\n");
    scanf("%i", respuesta4);
    while ((*respuesta4) > 10 || (*respuesta4) < 0){
        printf("No existe esa opcion!\n");
        scanf("%i", respuesta4);
    }   
}

void preguntas(char* respuesta1, char* respuesta2, float* respuesta3, int* respuesta4){
    pregunta_transporte(respuesta1);
    pregunta_arma(respuesta2);
    pregunta_hora(respuesta3);
    pregunta_nota(respuesta4);
}

int valor_respuesta1(char* respuesta1){
    int valor = 0;
    if((*respuesta1) == TRINEO || (*respuesta1) == NAVE_ESPACIAL){
        valor = 10;
    }else{
        valor = 20;
    }
    return valor;
}

int valor_respuesta2(char* respuesta2){
    int valor = 0;
    if((*respuesta2) == BOLAS_DE_NIEVE){
        valor = 3;
    }else if((*respuesta2) == PIUM_PIUM){
        valor = 6;
    }else if((*respuesta2) == KUCHAU){
        valor = 9;
    }else{
        valor = 12;
    } 
    return valor;
}

int valor_respuesta4(int* respuesta4){
    int valor = 0;
    if((*respuesta4) > 0 && (*respuesta4) < 4){
        valor = 1;
    }else if((*respuesta4) > 3 && (*respuesta4) < 7){
        valor = 2;
    }else if((*respuesta4) == 7 || (*respuesta4) == 8){
        valor = 3;
    }else{
        valor = 4;
    }
    return valor;
}

int puntaje(char* respuesta1, char* respuesta2, int* respuesta4){
    int puntaje_pregunta1 = valor_respuesta1(respuesta1);

    int puntaje_pregunta2 = valor_respuesta2(respuesta2);

    int puntaje_pregunta4 = valor_respuesta4(respuesta4);

    int suma_de_puntos = (puntaje_pregunta1 + (puntaje_pregunta2 * puntaje_pregunta4));

    return suma_de_puntos;
}

char personaje(char* respuesta1, char* respuesta2, float* respuesta3, int* respuesta4){
    preguntas(respuesta1, respuesta2, respuesta3, respuesta4);
    int total_puntos = puntaje(respuesta1, respuesta2, respuesta4);
    printf("\nLa suma de puntos es: \n%i\n", total_puntos);
    if((total_puntos >= 13) && (total_puntos <= 41)){
        if((*respuesta3) >= LLEGAR_TARDE){
            printf("\nEl personaje es: \n-Olaf-\n");
            return OLAF;
        }else{
            printf("\nEl personaje es: \n-Stitch-\n");
            return STITCH;
        }
    }else{
        if((*respuesta3) >= LLEGAR_TARDE){
            printf("\nEl personaje es: \n-Rayo McQueen-\n");
            return RAYOMCQUEEN;
        }else{
            printf("\nEl personaje es: \n-Jasmín-\n");
            return JASMIN;
        }
    }
}

