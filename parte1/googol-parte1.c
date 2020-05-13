/*Pedro Regio Shoji - 11.2017.21028*/
#include <stdio.h>
#include <stdlib.h>

#define ok printf("ok!\n");
#define maxSize 2002

typedef struct{
    int sinal;
    char *numero;
    int tamanho;
} numerao;

/* funcoes para numeroes comuns */
void getNumerao(numerao *n);
int checkFIM(char *str);
void inverteNumerao(numerao n);

/* Funcoes para numeroes invertidos */
void printNumerao(numerao n);
int checkMaior(numerao x, numerao y);

/* Funcoes de operacoes */
void sum(numerao x, numerao y);


int main(){
    int i;
    numerao a,b;
    char operation;

    a.numero = malloc(maxSize*sizeof(char));
    b.numero = malloc(maxSize*sizeof(char));

    while(1){
	/* input */

	getNumerao(&a);
	if(checkFIM(a.numero)) break;

	getNumerao(&b);

	scanf("%c", &operation);
	getchar();
	/**************************************/

	/*
	inverteNumerao(a);
	inverteNumerao(b);
	printNumerao(a);
	printf("ta = %d\n", a.tamanho);
	printf("sa = %d\n", a.sinal);
	printNumerao(b);
	printf("tb = %d\n", b.tamanho);
	printf("sb = %d\n", b.sinal);
	*/

	/**************************************/

	switch (operation){
	    case '+':
		inverteNumerao(a);
		inverteNumerao(b);
		if(checkMaior(a,b)){
		    sum(a,b);
		}
		else sum(b,a);
		break;
	    case '-':
		inverteNumerao(a);
		inverteNumerao(b);
		b.sinal*=-1;
		if(checkMaior(a,b)){
		    sum(a,b);
		}
		else sum(b,a);
		break;
	}
    }

    free(a.numero);
    free(b.numero);
    
    return 0;
}


/* Retorna 1, se os primeiros caracteres do vetor forem iguais a 'F','I''M'
 * Retorna 0, caso contrario */
int checkFIM(char *str){
    if(str[0] != 'F') return 0;
    if(str[1] != 'I') return 0;
    if(str[2] != 'M') return 0;
    return 1;
}


/* Retorna 1, se |x|>|y|
 * Retorna 0. caso contrario */
int checkMaior(numerao x, numerao y){
    int i;
    if(x.tamanho>y.tamanho) return 1;
    if(y.tamanho>x.tamanho) return 0;
    for(i=1;i<=x.tamanho;i++){
	if(x.numero[x.tamanho-i]>y.numero[y.tamanho-i]) return 1;
	if(y.numero[y.tamanho-i]>x.numero[x.tamanho-i]) return 0;
    }
    
    return 1;
}


/* Imprime um numerao
 * Apenas imprime o sinal se o numerao for negativo */
void printNumerao(numerao n){
    int i;
    if(n.tamanho==0) printf("0\n");
    else{
	if(n.sinal == -1){
	    printf("-");
	}

	for(i=n.tamanho-1;i>=0;i--){
	    printf("%c", n.numero[i]);
	}
	printf("\n");
    }
}


/* Recebe um ponteiro para numerao;
 * Cria um numerao de acordo com o padrao definido
 * Sinal:  1, positivo
 *	  -1, negativo
 * numero, tamanho */
void getNumerao(numerao *n){
    int i=0;
    scanf("%c", &n->numero[i]);
    if(n->numero[i]=='-'){
	n->sinal = -1;
    }
    else{
	n->sinal = 1;
	i++;
    }

    for(; n->numero[i-1] != '\n' ; i++){
	scanf("%c", &n->numero[i]);
    }
    
    n->tamanho = i-1;
}


/* Input: x (maior numerao), y (menor numerao) */
void sum(numerao x, numerao y){
    int i;
    /* Soma */
    if(x.sinal * y.sinal == 1){
	x.tamanho++;
	x.numero[x.tamanho-1]='0';
	for(i=0;i<y.tamanho;i++){
	    x.numero[i] += y.numero[i] - '0';
	    if(x.numero[i] > '9'){
		x.numero[i] -= 10;
		x.numero[i+1]++;
	    }
	}

	for(;i<x.tamanho;i++){
	    if(x.numero[i] <= '9') break;
	    x.numero[i] -= 10;
	    x.numero[i+1]++;
	}
    }


    /* Subtracao
     * Sempre subtraremos o menor numero do maior
     * Manteremos o sinal por conta da seguinte relacao(-x+y) = -(x-y) */
    else{
	for(i=0;i<y.tamanho;i++){
	    x.numero[i] -= y.numero[i] - '0';
	    if(x.numero[i] < '0'){
		x.numero[i] += 10;
		x.numero[i+1]--;
	    }
	}
	for(;i<x.tamanho;i++){
	    if(x.numero[i] >= '0') break;
	    x.numero[i] += 10;
	    x.numero[i+1]--;
	}
    }

    /* ajusta o tamanho final de x */
    for(;x.numero[x.tamanho-1] == '0'; x.tamanho--);
    

    printNumerao(x);
}

void inverteNumerao(numerao n){
    int i, aux;
    
    for(i=0 ; i<n.tamanho/2 ; i++){
	aux = n.numero[i];
	n.numero[i] = n.numero[n.tamanho-1-i];
	n.numero[n.tamanho-1-i] = aux;
    }
}


/* To do list:
 * Ver se e mais eficiente aumentar o tamanho do vetor de forma eficiente ou de forma precavida
 */
