#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "dia_en_la_uni.h"
#include "utiles.h"
#include "papeleo.h"

int main(){
    srand ((unsigned)time(NULL));
    juego_t juego;
    //char respuesta1, respuesta2;
    //float respuesta3;
    //int respuesta4;
    juego.personaje_tp1 = 'S';//personaje(&respuesta1, &respuesta2, &respuesta3, &respuesta4);
    juego.nivel_actual = 1;

    inicializar_juego(&juego, juego.personaje_tp1);
    estado_juego(juego);  
    while(estado_juego(juego) == 0)
    {
        realizar_jugada(&juego);
        if(estado_nivel(juego.niveles[juego.nivel_actual-1].papeleos, juego.niveles[juego.nivel_actual-1].tope_papeleos) == 1 && estado_juego(juego) != 1){
            juego.nivel_actual++;
            inicializar_juego(&juego, juego.personaje_tp1);         
        }
        system("clear");
    }
    if(estado_juego(juego) == 1){
        printf("GANASTE EL JUEGO\n");
    }else{
        printf("PERDISTE\n");
    }
    
    return 0;
}