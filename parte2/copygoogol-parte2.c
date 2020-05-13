/*Pedro Regio Shoji - 11.2017.21028*/
#include <stdio.h>
#include <stdlib.h>

#define ok printf("ok!\n");
#define pn printf("\n");
#define maxSize 2005

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
void sum(numerao *x, numerao *y);
numerao multiplication(numerao x, numerao y);
void division(numerao *x, numerao *y);


int main(){
    int i;
    numerao a,b;
    char operation;

    a.numero = malloc(1005*sizeof(char));
    b.numero = malloc(1005*sizeof(char));

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

	inverteNumerao(a);
	inverteNumerao(b);

	switch (operation){
	    case '+':
		if(checkMaior(a,b)){
		    sum(&a,&b);
		    printNumerao(a);
		}
		else{
		    sum(&b,&a);
		    printNumerao(b);
		}
		break;
	    case '-':
		b.sinal*=-1;
		if(checkMaior(a,b)){
		    sum(&a,&b);
		    printNumerao(a);
		}
		else{
		    sum(&b,&a);
		    printNumerao(b);
		}
		break;
	    case '*':
		if(checkMaior(a,b)){
		    a = multiplication(a,b);
		    printNumerao(a);
		}
		else{
		    b = multiplication(b,a);
		    printNumerao(b);
		}
		break;
	    case '/':
		division(&a,&b);
		printNumerao(b);
		break;
	    case '%':
		division(&a,&b);
		printNumerao(a);
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


void inverteNumerao(numerao n){
    int i, aux;
    
    for(i=0 ; i<n.tamanho/2 ; i++){
	aux = n.numero[i];
	n.numero[i] = n.numero[n.tamanho-1-i];
	n.numero[n.tamanho-1-i] = aux;
    }
}


/* Input: x (maior numerao), y (menor numerao) */
void sum(numerao *x, numerao *y){
    int i;
    /* Soma */
    if(x->sinal * y->sinal == 1){
	x->tamanho++;
	x->numero[x->tamanho-1]='0';
	for(i=0;i<y->tamanho;i++){
	    x->numero[i] += y->numero[i] - '0';
	    if(x->numero[i] > '9'){
		x->numero[i] -= 10;
		x->numero[i+1]++;
	    }
	}

	for(;i<x->tamanho;i++){
	    if(x->numero[i] <= '9') break;
	    x->numero[i] -= 10;
	    x->numero[i+1]++;
	}
    }


    /* Subtracao
     * Sempre subtraremos o menor numero do maior
     * Manteremos o sinal por conta da seguinte relacao(-x+y) = -(x-y) */
    else{
	for(i=0;i<y->tamanho;i++){
	    x->numero[i] -= y->numero[i] - '0';
	    if(x->numero[i] < '0'){
		x->numero[i] += 10;
		x->numero[i+1]--;
	    }
	}
	for(;i<x->tamanho;i++){
	    if(x->numero[i] >= '0') break;
	    x->numero[i] += 10;
	    x->numero[i+1]--;
	}
    }

    /* ajusta o tamanho final de x */
    for(;x->numero[x->tamanho-1] == '0'; x->tamanho--);
}


/* Input: x (maior numerao), y (menor numerao) */
numerao multiplication(numerao x, numerao y){
    int i, j, k, n, c, aux;
    numerao mult;
    numerao carry;
    numerao num;

    mult.sinal = 1;
    mult.numero = malloc(maxSize*sizeof(char));
    mult.tamanho = 0;

    num.sinal = 1;
    num.numero = malloc(maxSize*sizeof(char));

    carry.sinal = 1;
    carry.numero = malloc(maxSize*sizeof(char));

    for(i=0;i<y.tamanho;i++){
	/* Desloca o carry para a posicao inicial da iteracao */
	for(c=0;c<i+1;c++){
	    carry.numero[c] = '0';
	}
	carry.tamanho = c;
	/* Desloca num para a posicao inicial da iteracao */
	for(n=0;n<i;n++){
	    num.numero[n] = '0';
	}
	num.tamanho = n;
	for(j=0;j<x.tamanho;j++){
	    aux = (x.numero[j] - '0')*(y.numero[i] - '0');
	    carry.numero[c+j] = (aux/10) + '0';
	    carry.tamanho++;
	    num.numero[n+j] = (aux%10) + '0';
	    num.tamanho++;

	}

	/*
	pn
	printf("num\n");
	printNumerao(num);
	printf("carry\n");
	printNumerao(carry);
	*/

	for(;num.numero[num.tamanho-1] == '0'; num.tamanho--);
	for(;carry.numero[carry.tamanho-1] == '0'; carry.tamanho--);

	if(checkMaior(mult,num)){
	    sum(&mult,&num);
	}
	else{
	    sum(&num,&mult);
	    mult.tamanho = num.tamanho;
	    for(k=0;k<mult.tamanho;k++){
		mult.numero[k] = num.numero[k];
	    }
	}
	if(checkMaior(mult,carry)){
	    sum(&mult,&carry);
	}
	else{
	    sum(&carry,&mult);
	    mult.tamanho = carry.tamanho;
	    for(k=0;k<mult.tamanho;k++){
		mult.numero[k] = carry.numero[k];
	    }
	}

	/*
	printf("mult = ");
	printNumerao(mult);
	*/
    }

    mult.sinal = x.sinal*y.sinal;

    /* FREEEEEE */
    free(x.numero);
    free(num.numero);
    free(carry.numero);

    return mult;
}


/* Recebe dois ponteiros de numeroes 
 * no final da operacao, o numerao x guardara o resto
 * e o numerao y guardara o resultado
 * */
void division(numerao *x, numerao *y){
    int i;
    int xTamOri = x->tamanho, yTamOri = y->tamanho;
    numerao div;
    numerao m;
    numerao teste;

    m.sinal = 1;
    m.numero = malloc(sizeof(char));
    m.tamanho = 1;

    teste.numero = malloc(maxSize*sizeof(char));



    if(checkMaior(*y,*x)){
	y->tamanho = 0;
	free(m.numero);
	return;
    }

    for(x->tamanho = 1; checkMaior(*y,*x);x->tamanho++);
    printf("x->tamanho = %d\n",x->tamanho);

    for(m.numero[0] = '1'; ; m.numero[0]++){
	printf("m = ");
	printNumerao(m);
	teste = multiplication(*x,m); 
	printNumerao(teste);
	if(checkMaior(*y,teste)) break;
    }
    printf("multiplicador = %c\n", m.numero[0]);

    

    /* FREEEEEE */
}


/* To do list:
 * Ver se e mais eficiente aumentar o tamanho do vetor de forma eficiente ou de forma precavida
 */
