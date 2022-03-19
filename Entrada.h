#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Error.h"
#define SIZE 64
#define PATH "wilcoxon.py"
typedef struct bloque{
    char bloque1[SIZE+1];
    char bloque2[SIZE+1];
    int inicio;
    int estado_bloque; //1->bloque1 2->bloque2
    int delantero;
}Bloque;
//inicializa el doble centinela
void inicia_doble_centinela();
//devuelve el siguiente caracter leido
char lee_sig_char();
//retrocede 1 caracter
void retrocede();
//cierra el doble centinela
void elimina_doble_centinela();
//inicio=delantero
void acepta_lexema();