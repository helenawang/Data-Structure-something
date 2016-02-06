#include <stdio.h>
#include "Stack.h"
const int MAX_LEN = 100;
const int MAX_OP = 7; //当前共7个算符

char PrecTable[MAX_OP][MAX_OP]={
/*+  -   *   /   (   )   #   !为非法*/
'>','>','<','<','<','>','>',
'>','>','<','<','<','>','>',
'>','>','>','>','<','>','>',
'>','>','>','>','<','>','>',
'<','<','<','<','<','=','!',
'>','>','>','>','!','>','>',
'<','<','<','<','<','!','=',
};

int hash(char x){
	switch(x){
		case '+' : return 0;
		case '-' : return 1;
		case '*' : return 2;
		case '/' : return 3;
		case '(' : return 4;
		case ')' : return 5;
		case '#' : return 6;
		default : return -1;
	}
}
