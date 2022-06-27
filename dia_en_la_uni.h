#ifndef __DIA_EN_LA_UNI_H__
#define __DIA_EN_LA_UNI_H__

/*
*   Procedimiento que cargara la pregunta 1 y guardara solo la respuesta correcta
*/
void pregunta_transporte(char* respuesta1);

/*

*    Procedimiento que cargara la pregunta 2 y guardara solo la respuesta correcta
*/
void pregunta_arma(char* respuesta2);

/*
*    Procedimiento que cargara la pregunta 3 y guardara solo la respuesta correcta
*/
void pregunta_hora(float* respuesta3);

/* 
*   Procedimiento que cargara la pregunta 4 y guardara solo la respuesta correcta
*/
void pregunta_nota(int* respuesta4);

/*
*   Procedimiento que llamara a las 4 preguntas, para luego simplificar el llamado en el main
*/
void preguntas(char* respuesta1, char* respuesta2, float* respuesta3, int* respuesta4);

int valor_respuesta1(char* respuesta1);

int valor_respuesta2(char* respuesta2);

int valor_respuesta4(int* respuesta4);
/*
*    respuesta1 debe ser igual a TRINEO, NAVE_ESPACIAL, CAMION o ALFOMBRA.
*/
int puntaje(char* respuesta1, char* respuesta2, int* respuesta4);

/*
*    procedimiento que recibe las 4 respuestas, crea una variable que le asigna el valor de la funcion "puntaje" y luego,
*    segun los puntos obtenidos y la hora llegada, printea el personaje.
*/
char personaje(char* respuesta1, char* respuesta2, float* respuesta3, int* respuesta4);

#endif