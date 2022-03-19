#include "Entrada.h"
//------------------------------------------------------------------
//------------------------------------------------------------------
//VARIABLES GLOBALES
//Variable global puntero a doble centinela
Bloque b;
//variable puntero a archivo
FILE* fp;
//variable que cuenta cuantos caracteres tiene el lexema
int cnt_lex=0;
//variable que determina si se carga un nuevo bloque (evita la sobreescritura cuando se retrocede y b.bloqueN[b->delantero]==EOF después de retroceder)
int sobreescritura=1;//0-> no se sobreescribe 1-> se sobreescribe
//------------------------------------------------------------------
//------------------------------------------------------------------
//FUNCIONES
/*
 *      Funci�n: inicializa el primer centinela 
	 Valor de retorno: no devuelve nada
 */
void inicia_doble_centinela(){
   //abro el fichero por defecto wilcoxon.py
    fp = fopen(PATH, "rb");
    //reservo memoria para el doble centinela
    b.inicio=0;
    b.delantero=0;
    b.estado_bloque=1;
    // Si no llega al final del archivo
    if (!feof(fp)) {
    	//función fread para ir leyendo de bloque en bloque
        fread(b.bloque1, sizeof(char), SIZE, fp);
    } 
    //el ultimo char de cada bloque apunta a EOF
    b.bloque1[SIZE]=EOF;
    b.bloque2[SIZE]=EOF;
}
/*
 *      Funci�n:  cierra el archivo
	 Valor de retorno: no devuelve nada
 */
void elimina_doble_centinela(){
   fclose(fp);
}
/*
	 Funci�n: retrocede el puntero del fichero en una posición así como el centinela del
 *      bloque derecha y también el centinela del bloque izquierda apunta en esa dirección, pues
 *      al retroceder es que ya se ha detectado un componente léxico y el puntero ha leido un caracter
 *      de más
	 Valor de retorno: no tiene
*/
void retrocede(){
    if(b.delantero>0){
        b.delantero--;
    }
    //cuando retrocede de 0 comprueba en que bloque esta
    else {
    	if(b.estado_bloque==1){
    		b.estado_bloque=2;
    	}
    	else{
    		b.estado_bloque=1;
    	}
        b.delantero=SIZE;
        //no se puede sobreescribir el bloque
        sobreescritura=0;
    } 
    
    b.inicio=b.delantero;
    cnt_lex=0;
}
/*
	 Funci�n: lee el siguiente caracter del fichero
	 Valor de retorno: devuelve el caracter en cuestión
*/
char lee_sig_char(){
    char aux='\a';
    //comprueba si el lexema ha excedido el tamaño del bloque imprime un error
    if(cnt_lex>SIZE){
		print_Error(6,NULL,0);
		cnt_lex=0;
     }
     if (!feof(fp)) {
	    //si b.bloque[b.delantero]==EOF llegamos al final de un bloque y comprobamos si se puede sobreescribir los bloques
	    if((b.bloque1[b.delantero]==EOF||b.bloque2[b.delantero]==EOF)){  
	    	if(b.estado_bloque==1){
	    	        //si se puede sobreescribir el bloque->fread
	    		if(sobreescritura){
			    	//función fread para ir leyendo de bloque en bloque
				fread(b.bloque2, sizeof (char), SIZE, fp);
			}
			//ya se puede sobreescribir
			else{
				sobreescritura=1;
			}
			//cambio el estado del bloque a 2
			b.estado_bloque=2;
			b.delantero=0;
			aux=b.bloque2[b.delantero];
		}
		else{
			//si se puede sobreescribir el bloque->fread
	    		if(sobreescritura){
			    	//función fread para ir leyendo de bloque en bloque
				fread(b.bloque1, sizeof (char), SIZE, fp);
			}
			//ya se puede sobreescribir
			else{
				sobreescritura=1;
			}
			//cambio el estado del bloque a 1
			b.estado_bloque=1;
			b.delantero=0;
			aux=b.bloque1[b.delantero];
		}
		b.delantero++;
	    }
	    //si delantero no es EOF 
	    else{
	    	//si estado_bloque==1 bloque1 si no bloque2
	    	if(b.estado_bloque==1){
	    		aux= b.bloque1[b.delantero];
	    	}
	    	else{
	    		aux= b.bloque2[b.delantero];
	    	}
	    	//si no se pudo sobreescribir el bloque
	    	//aumento delantero
	    	b.delantero++;
	    }
    }
    cnt_lex++;
    return aux;
}
/*
	 Funci�n: acepta un lexema
	 Valor de retorno: ninguno
*/
void acepta_lexema(){
	b.inicio=b.delantero;
	cnt_lex=0;
}