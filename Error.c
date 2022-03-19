#include "Error.h"
/*
	 Funci�n: imprime los distintos tipos de errores
	 Valor de retorno: no tiene
*/
void print_Error(int id,char* value,int linea){
    switch(id){
        case 0:
            printf("[ERROR %d EN LINEA %d]:El valor %s es un carácter ASCII que Python no reconoce.\n",id,linea,value);
        break;
        case 1:
            printf("[ERROR %d EN LINEA %d]:El valor %s es un número binario mal formado\n",id,linea,value);
        break;
        case 2:
            printf("[ERROR %d EN LINEA %d]:El valor %s es un número entero mal formado\n",id,linea,value);
        break;
        case 3:
            printf("[ERROR %d EN LINEA %d]:El valor %s es un número octal mal formado\n",id,linea,value);
        break;
        case 4:
            printf("[ERROR %d EN LINEA %d]:El valor %s es un número hexadecimal mal formado\n",id,linea,value);
        break;
        case 5:
            printf("[ERROR %d EN LINEA %d]:El valor %s es un número en punto flotante mal formado\n",id,linea,value);
        break;
         case 6:
            printf("[ERROR %d]:Se ha excedido el tamaño del bloque\n",id);
        break;
    }
}