#include "Lexico.h"
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//VARIABLES GLOBALES
//variable global que resgistra en que linea se encuentra el lexema (empieza en 1)
int linea=1;
//cadena del tamaño del bloque de entrada
char cadena[SIZE];
//tupla que devuelve al analizador sintactico
tipoelem tup;
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//FUNCION CADENA GLOBAL

/*
	 Funci�n: añade un caracter al final de una cadena y reserva memoria
	 Valor de retorno: ninguno
*/
void appendCadena(char c){
	char cadenaAux[2];
	cadenaAux[0]=c;
	cadenaAux[1]='\0';
	strcat(cadena,cadenaAux);
}
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//FUNCION TUPLAS
/*
	 Funci�n: inicializa la tupla tup
	 Valor de retorno: no tiene
*/
void iniciaTupla(){
	tup.compLex=0;
	tup.linea=0;
}
/*
	 Funci�n: asigna los datos a la tupla (lexema y linea son variables globales);
	 Valor de retorno: no tiene
*/
void setTupla(int comp_lex){
	tup.linea=linea;
	tup.compLex=comp_lex;
	memset(tup.lexema,0,SIZE);
	strcat(tup.lexema,cadena);

}

//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//FUNCION AUTOMATAS
/*
	 Funci�n: guarda en la tupla la información del operador o delimitador que encuentra
	 Valor de retorno: ninguno
*/
void automata_operador_delimitador(char ch){	
	char w;
	appendCadena(ch);
	switch(ch){
		case '(':case ')':case '[':case ']':case '{':case '}':case '.': case ',':case ':':case ';':
			w=lee_sig_char();
			//caso := es operador
			if(w=='=' && ch==':'){
				appendCadena(w);
				setTupla(ASIGNACION);
			}
			else{
				//retrocede por que es solo un caracter delimitador
				retrocede();
				if(ch=='('){
					setTupla(IPAR);
				}
				else if(ch==')'){
					setTupla(DPAR);
				}
				else if(ch=='['){
					setTupla(ICOR);
				}
				else if(ch==']'){
					setTupla(DCOR);
				}
				else if(ch=='{'){
					setTupla(ICON);
				}
				else if(ch=='}'){
					setTupla(DCON);
				}
				else if(ch=='.'){
					setTupla(PUNTO);
				}
				else if(ch==','){
					setTupla(COMA);
				}
				else if(ch==':'){
					setTupla(DOSPUNTOS);
				}
				else if(ch==';'){
					setTupla(PUNTOCOMA);
				}
			}
			break;
				
		case '+':case '-':case '%':case '@':case '^':case '|':case '&':case '~':
			w=lee_sig_char();
			//caso +=, -=, %=, @=... delimitadores
			if(w=='='){
				appendCadena(w);
				if(ch=='+'){
					setTupla(MASIGUAL);
				}
				else if(ch=='-'){
					setTupla(MENOSIGUAL);
				}
				else if(ch=='%'){
					setTupla(MODULOIGUAL);
				}
				else if(ch=='@'){
					setTupla(ARROBAIGUAL);
				}
				else if(ch=='^'){
					setTupla(ELEVADOIGUAL);
				}
				else if(ch=='|'){
					setTupla(BARRAVIGUAL);
				}
				else if(ch=='&'){
					setTupla(AMPERSANDIGUAL);
				}
				else if(ch=='~'){
					setTupla(VIRGULILLAIGUAL);
				}
			}
			//caso -> delimitador
			else if(w=='>' && ch=='-'){
				appendCadena(w);
				setTupla(FLECHA);
			}
			else{
				//retrocede es un caracter operador
				retrocede();
				if(ch=='+'){
					setTupla(MAS);
				}
				else if(ch=='-'){
					setTupla(MENOS);
				}
				else if(ch=='%'){
					setTupla(MODULO);
				}
				else if(ch=='@'){
					setTupla(ARROBA);
				}
				else if(ch=='^'){
					setTupla(ELEVADO);
				}
				else if(ch=='|'){
					setTupla(BARRAV);
				}
				else if(ch=='&'){
					setTupla(AMPERSAND);
				}
				else if(ch=='~'){
					setTupla(VIRGULILLA);
				}
			}
			break;
			
		case '*': case '<': case '>': case '/': case'=':
			w=lee_sig_char();
			//PARA ** << >> // ==
			if(w==ch){
				appendCadena(w);
				w=lee_sig_char();
				//PARA **= <<= >>= //= delimitador
				if(ch!='='&& w=='='){
					appendCadena(w);
					if(ch=='*'){
						setTupla(PORPORIGUAL);
					}
					else if(ch=='<'){
						setTupla(MENORMENORIGUALIGUAL);
					}
					else if(ch=='>'){
						setTupla(MAYORMAYORIGUALIGUAL);
					}
					else if(ch=='/'){
						setTupla(BARRABARRAIGUAL);
					}
				
				}
				//PARA ** << >> // == operador
				else{
					retrocede();
					if(ch=='*'){
						setTupla(PORPOR);
					}
					else if(ch=='<'){
						setTupla(MENORMENOR);
					}
					else if(ch=='>'){
						setTupla(MAYORMAYOR);
					}
					else if(ch=='/'){
						setTupla(BARRABARRA);
					}
					else if(ch=='='){
						setTupla(IGUALIGUAL);
					}
				}
			}
			//para <= >= operadores y *= /= delimitadores
			else if(w=='='){
			 	//<= y >=operador
				if(ch=='>'){
					appendCadena(w);
					setTupla(MAYORIGUAL);
				}
				else if(ch=='<'){
					appendCadena(w);
					setTupla(MENORIGUAL);
				}
				//delimitador *= /=
				else if(ch=='*'){
					appendCadena(w);
					setTupla(PORIGUAL);	
				}
				else if(ch=='/'){
					appendCadena(w);
					setTupla(BARRAIGUAL);	
				}
			}
			//* < > / = operadores
			else{
				if(ch=='>'){
					setTupla(MAYOR);
				}
				else if(ch=='<'){
					setTupla(MENOR);
				}
				else if(ch=='*'){
					setTupla(POR);	
				}
				else if(ch=='/'){
					setTupla(BARRA);	
				}
				else if(ch=='='){
					setTupla(IGUAL);
				}
				retrocede();
			}
			break;
		case '!':
			w=lee_sig_char();
			//!= operador
			if(w=='='){
				appendCadena(w);
				setTupla(NOIGUAL);
			}
			else{
				retrocede();
			}
			break;		
		}		
	}
/*
	 Funci�n: guarda en la tupla la información del literal cadena que encuentra ya sea "ejemplo" o 'ejemplo'
	 Valor de retorno: ninguno
*/
void automata_litcadena(char primer_char){
	char c;
	appendCadena(primer_char);
	if(primer_char=='\''){
		//sigo añadiendo mientras no sea '
		c=lee_sig_char();
		while(c!='\''){
			appendCadena(c);
			//acepto lexema para evitar error de tamaño
			acepta_lexema();
			c=lee_sig_char();
		}
        
        }
	//busco las otras comillas dobles
	else{
		//sigo añadiendo mientras no sea "
		c=lee_sig_char();
		while(c!='\"'){
			appendCadena(c);
			//acepto lexema para evitar error de tamaño
			acepta_lexema();
			c=lee_sig_char();
		}
	}
	//anado las ultimas comillas dobles o simples
	appendCadena(primer_char);
	setTupla(CAD);
}
/*
	 Funci�n: guarda en la tupla la información del literal int que encuentra
	 Valor de retorno: ninguno
*/
void automata_litfloat(char primer_char){
	appendCadena(primer_char);
	char c;
	int pnt=0;
	c=lee_sig_char();
	if(!isalpha(c)){
		pnt++;
		//mientras sea un digito e(+/-) o . es un float
		while(isdigit(c)||c=='_'||c=='e'||c=='E'||c=='+'||c=='-'||c=='.'){
			if(c=='.'){
				pnt++;
				appendCadena(c);
			}
			//si encuentro e tiene que ser de la forma e[+|-]?int
			else if(c=='e'||c=='E'){
				appendCadena(c);
				c=lee_sig_char();
				if(c=='-'||c=='+'){
					appendCadena(c);
					c=lee_sig_char();
					while(isdigit(c)){
						appendCadena(c);
						c=lee_sig_char();
					}
				}
			}
			//si no sigo metiendo en la cadena los caracteres
			else{
				appendCadena(c);
				c=lee_sig_char();
			}
		}
		//si hay  más de un punto; error, numero flotante mal descrito
		if(pnt>1){
			while(isalnum(c)||c=='_'){
				appendCadena(c);
				c=lee_sig_char();	
			}
			retrocede();
			print_Error(5,cadena,linea);
		}
		//si no hay más de un punto es un float bien formado
		else{
			retrocede();
			setTupla(FLT);
		}
	}
	//si es una letra lo mas seguro es que sea identificador.identificador, retrocedo y mando el punto al automata de operador delimitador
	else{
		retrocede();
		memset(cadena,0,SIZE);
		automata_operador_delimitador(primer_char);
	}
}
/*
	 Funci�n: guarda en la tupla la información del literal int que encuentra
	 Valor de retorno: ninguno
*/
void automata_litfloatCadena(){
	char c;
	int pnt=0;
	c=lee_sig_char();
	//mientras sea un digito e(+/-) o . es un float
	while(isdigit(c)||c=='_'||c=='e'||c=='E'||c=='+'||c=='-'||c=='.'){
		if(c=='.'){
			pnt++;
			appendCadena(c);
		}
		//si encuentro e tiene que ser de la forma e[+|-]?int
		else if(c=='e'||c=='E'){
			appendCadena(c);
			c=lee_sig_char();
			if(c=='-'||c=='+'){
				appendCadena(c);
				c=lee_sig_char();
				while(isdigit(c)){
					appendCadena(c);
					c=lee_sig_char();
				}
			}
		}
		else{
			appendCadena(c);
			c=lee_sig_char();
		}
	}
	//si hay una letra distinta de e o E o más de un (punto,e o +/-) error, numero flotante mal descrito
	if(isalpha(c)||pnt>1){
		while(isalnum(c)||c=='_'){
			appendCadena(c);
			c=lee_sig_char();	
		}
		retrocede();
		print_Error(5,cadena,linea);
	}
	//si no es un número float bien formado
	else{
		retrocede();
		setTupla(FLT);
	}
}
/*
	 Funci�n: guarda en la tupla la información del literal int que encuentra
	 Valor de retorno: ninguno
*/
void automata_litint(char primer_char){
	appendCadena(primer_char);
	char c;
	c=lee_sig_char();
	//numeros hexadecimales, octales o binarios
	if(primer_char=='0' && isalpha(c)){
		//binarios
		if(c=='b'||c=='B'){
			//añado b o B
			appendCadena(c);
			c=lee_sig_char();
			//mientras sea 0,1 u _ anado a cadena
			while(c=='0'||c=='1'||c=='_'){
				appendCadena(c);
				c=lee_sig_char();
			}
			//si es otro digito que no sea 1 o 0 o una letra esta mal definido lanzo error
			if(isalnum(c)){
				while(isalnum(c)||c=='_'){
					appendCadena(c);
					c=lee_sig_char();	
				}
				retrocede();
				print_Error(1,cadena,linea);
			}
			else{
				retrocede();
				setTupla(BIN);
			
			}
		}
		//octales
		else if(c=='o'||c=='O'){
			//añado o u O
			appendCadena(c);
			c=lee_sig_char();
			//mientras sea 0..7 u _ anado a cadena
			while((c!='8'&& c!='9' && isdigit(c))||c=='_'){
				appendCadena(c);
				c=lee_sig_char();
			}
			//si es 8 o 9 o una letra esta mal definido lanzo error es un octal mal definido
			if(isalnum(c)){
				while(isalnum(c)||c=='_'){
					appendCadena(c);
					c=lee_sig_char();	
				}
				retrocede();
				print_Error(3,cadena,linea);
			}
			else{
				retrocede();
				setTupla(OCT);
			
			}
		}
		//hexadecimal
		else if(c=='x'||c=='X'){
			//añado x o X
			appendCadena(c);
			c=lee_sig_char();
			//mientras sea 0..9, a..f, A..F u _ anado a cadena
			while(isdigit(c)||c=='_'||c=='a'||c=='A'||c=='b'||c=='B'||c=='c'||c=='C'||c=='d'||c=='D'||c=='e'||c=='E'||c=='f'||c=='F'){
				appendCadena(c);
				c=lee_sig_char();
			}
			//si es letra que no sea a..f o A..F esta mal definido lanzo error es un hexadecimal mal definido
			if(isalpha(c)){
				while(isalnum(c)||c=='_'){
					appendCadena(c);
					c=lee_sig_char();	
				}	
				retrocede();
				print_Error(4,cadena,linea);
			}
			else{
				retrocede();
				setTupla(HX);
			
			}
		}
		//deriva en automata_litfloat 0e....
		else if(c=='e'||c=='E'){
			appendCadena(c);
			automata_litfloatCadena(cadena);
		}
		//si no es ninguno de los anteriores casos es un entero mal formado
		else{
			while(isalnum(c)||c=='_'){
				appendCadena(c);
				c=lee_sig_char();
			}
			retrocede();
			print_Error(2,cadena,linea);
		}
	}
	else{
		//sigo añadiendo mientra sea un numérico ,'_' o '.'
		while(isdigit(c)||c=='_'){
			appendCadena(c);	
			c=lee_sig_char();
		}
		//automata_litfloat si encuentro . o e
		if(c=='.'||c=='e'||c=='E'){
			appendCadena(c);
			automata_litfloatCadena(cadena);
		}
		//si leo una letra es un numero entero mal formado
		else if(isalpha(c)){
			while(isalnum(c)||c=='_'){
				appendCadena(c);
				c=lee_sig_char();	
			}
			retrocede();
			print_Error(2,cadena,linea);
		}
		else{
			//si no encuentro . o e retrocedo y acepto como literal entero
			retrocede();
			setTupla(INT);
		}
	}
}
/*
	 Funci�n: guarda en la tupla la información del identificador que encuentra
	 Valor de retorno: ninguno
*/
void automata_alfa(char primer_char){
	tipoelem elemento;
	char c;
	//añado el primer caracter
	appendCadena(primer_char);
	c=lee_sig_char();
	//sigo añadiendo mientra sea un alfanumérico ,'_' o '.'
	while(isalnum(c)||c=='_'){
		appendCadena(c);	
		c=lee_sig_char();
	}
	//he leido un caracter de mas, retrocedo
	retrocede();
	if(is_keyword(cadena)){
		//guardo y devuelvo Tupla
		setTupla(asigna_compLex(cadena));
	}
	else{
		//guardo y devuelvo Tupla
		setTupla(ID);
		
		//añado el elemento a la tabla
		memset(elemento.lexema,0,SIZE);
	 	strcat(elemento.lexema,cadena);
		elemento.compLex=336;
		if(!MiembroHashTablaSimbolos(elemento)){
			//si no existe en la tabla lo inserto
			InsertarHashTablaSimbolos(elemento);
		}
	}
}

/*
	 Funci�n: guarda en la tupla la información del comentario que encuentra
	 Valor de retorno: ninguno
*/
void automata_comentarios(char primer_char){
	char c;
	int contador=0;
	if(primer_char=='#'){
		//añado #
		//añado el comentario hasta encontrar un salto de linea
		c=lee_sig_char();
		while(c!='\n'){
			c=lee_sig_char();
			//acepto para que no llegue a error x tamaño de bloque
			acepta_lexema();	
		}
		linea++;
		
	}
	else{
		//añado """
		c=lee_sig_char();
		//si el siguiente caracter de las comillas dobles son otras comillas es un comentario
		if(c=='\"'){
			//busco las """ finales
			c=lee_sig_char();
			while(contador!=3){
				c=lee_sig_char();			
				//si encuentro comillas cuento hasta 3 para salir
				if(c=='\"'){
					contador++;
				}
				//si encuentro \n sumo linea
				else if(c=='\n'){
					linea++;
				}
                        	//acepto para que no llegue a error x tamaño de bloque
				acepta_lexema();
			}
			if(c=='\n'){
				linea++;
			}
		}
		//si el siguiente caracter a " no son otras comillas dobles paso al automata de cadena literal y retrocede pues se hace un c=lee_sig_char 
		//pero no se guarda en cadena
		else{
			retrocede();	
			automata_litcadena(primer_char);
		}	
	}
	
}
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//FUNCION SIG_COMP_LEX

/*
	 Funci�n: devuelve el siguiente componente léxico
	 Valor de retorno: devuelve el id asociado al nuevo componente léxico
*/
tipoelem sig_com_lex(){
	char c;
	tup.compLex=0;
	while(tup.compLex==0){
		c=lee_sig_char();
		//COMENTARIOS (automata_comentarios lleva a automata_litcadena con " simple)
		if(c=='#'||c=='\"'){
			automata_comentarios(c);
		}
		//ESPACIO
		else if(c==' '){
			continue;
		}
		//SALTO DE LINEA
		else if(c=='\n'){
			linea++;
		}
		//ALFABETICO O _
		else if(isalpha(c)||c=='_'){
			automata_alfa(c);
		}
		//LITERAL INT (incluyendo octal, binario y hexadecimal) tambien deriva en automata_litfloat()
		else if(isdigit(c)){
			automata_litint(c);
		}
		//FIN DE FICHERO devuelve un caracter de control -> fin de la funcion sig_com_lex
		else if(iscntrl(c)){
			tup.compLex=-1;
		}
		//LITERAL FLOAT
		else if(c=='.'){
			automata_litfloat(c);
		}
		//' LITERAL CADENA
		else if(c=='\''){
			automata_litcadena(c);
		}
		//OPERADORES Y DELIMITADORES
		else if(c=='+'||c=='-'||c=='*'||c=='/'||c=='|'||c=='%'||c=='&'||c=='^'||c=='{'||c=='}'||c=='['||c==']'||c==','||
		c==';'||c==':'||c=='@'||c=='~'||c=='<'||c=='>'||c=='!'||c=='='||c=='('||c==')'){
			automata_operador_delimitador(c);
		}
		//error, no se reconoce el caracter ASCII
		else{
			char *cadena=(char*) malloc(sizeof(char));
			memset(cadena,0,SIZE);
			appendCadena(c);
			print_Error(0,cadena,linea);
			free(cadena);
			cadena=NULL;
		}
		acepta_lexema();

	}
	memset(cadena,0,SIZE);
	return tup;
}
