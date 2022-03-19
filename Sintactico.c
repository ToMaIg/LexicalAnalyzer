#include "Sintactico.h"
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
/*
	 Funci�n: imprime los componentes léxicos que le devuelve el léxico
	 Valor de retorno: no tiene
*/
void print_comp_lex(){
    int cond=0;
    tipoelem t;
    //inicializa la tupla
    iniciaTupla();
    //imprimo la tabla hash
    printf("|TOKENS ECONTRADOS|\n");
    printf("-----------------------------------\n");
    //mientras no devuelva sig_com_lex una tupla con complemento lexico = -1 sigo pidiendo componentes
    while(cond==0){
        t=sig_com_lex();
        if(t.compLex!=-1){
        
            printf("[ %d , %s ] Linea=%d\n",t.compLex,t.lexema,t.linea);
        }
        else{
            cond=1;
        }
    }
    printf("-----------------------------------\n");
}
