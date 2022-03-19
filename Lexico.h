#pragma once
#include "Lexico.h"
#include "Error.h"
#include "TablaSimbolos.h"
#include "Entrada.h"
#include "PReservadas.h"
#include "Definiciones.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
//inicializa la tupla
void iniciaTupla();
//devuelve el siguiente componente léxico en forma de id e lo inserta en la hash table
tipoelem sig_com_lex();