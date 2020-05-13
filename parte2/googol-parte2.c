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
int maiorComum(numerao x, numerao y);

/* Funcoes para numeroes invertidos */
void printNumerao(numerao n);
int checkMaior(numerao x, numerao y);

/* Funcoes de operacoes */
    /* Invertido */
    void sum(numerao *x, numerao *y);
    void multiplication(numerao *x, numerao *y);
    /* Comum */
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

	/* [DEBUG]
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
		    sum(&a,&b);
		    printNumerao(a);
		}
		else{
		    sum(&b,&a);
		    printNumerao(b);
		}
		break;
	    case '-':
		inverteNumerao(a);
		inverteNumerao(b);

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
		inverteNumerao(a);
		inverteNumerao(b);

		if(checkMaior(a,b)){
		    multiplication(&a,&b);
		    printNumerao(a);
		}
		else{
		    multiplication(&b,&a);
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


/* Funcoes para numeroes na ordem comum */


/* Recebe um ponteiro para numerao;
 * Cria um numerao de acordo com o padrao definido
 * Sinal:  1, positivo
 *	  -1, negativo
 * Numero
 * Tamanho */
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


/* Retorna 1, se os primeiros caracteres do vetor forem iguais a 'F','I''M'
 * Retorna 0, caso contrario */
int checkFIM(char *str){
    if(str[0] != 'F') return 0;
    if(str[1] != 'I') return 0;
    if(str[2] != 'M') return 0;
    return 1;
}


/* Inverte a ordem na qual um numerao e guardado */
void inverteNumerao(numerao n){
    int i, aux;
    
    for(i=0 ; i<n.tamanho/2 ; i++){
	aux = n.numero[i];
	n.numero[i] = n.numero[n.tamanho-1-i];
	n.numero[n.tamanho-1-i] = aux;
    }
}


/* Input: numeroes nao invertidos
 * retorna 1, caso |x| > |y|
 * retorna 0, caso |x| == |y|
 * retorna -1, caso |x| < |y| */
int maiorComum(numerao x, numerao y){
    int i;
    if(x.tamanho>y.tamanho) return 1;
    if(y.tamanho>x.tamanho) return -1;
    for(i=0;i<x.tamanho;i++){
	if(x.numero[i]>y.numero[i]) return 1;
	if(y.numero[i]>x.numero[i]) return -1;
    }
    
    return 0;
}


/* Funcoes para numeroes invertidos */


/* Imprime um numerao invertido
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


/* Retorna 1, se |x|>=|y|
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


/* Funcoes de operacoes */


/* Input: x (ponteiro do maior numerao), y (ponteiro do menor numerao)
 * Altera o valor de x para o valor da soma/subtracao */
void sum(numerao *x, numerao *y){
    int i;
    /* Soma */
    if(x->sinal * y->sinal == 1){
	/* Adiciona um digito zero  ao final do resultado de forma precavida
	 * para o caso da soma ter mais digitos que os valores iniciais */
	x->tamanho++;
	x->numero[x->tamanho-1]='0';
	/* Loop da soma ate o numero de algarismos de y */
	for(i=0;i<y->tamanho;i++){
	    x->numero[i] += y->numero[i] - '0';
	    /* Soma do carry no proximo numero */
	    if(x->numero[i] > '9'){
		x->numero[i] -= 10;
		x->numero[i+1]++;
	    }
	}

	/* Lida com carries depois do tamanho de y */
	for(;i<x->tamanho;i++){
	    if(x->numero[i] <= '9') break;
	    x->numero[i] -= 10;
	    x->numero[i+1]++;
	}
    }


    /* Subtracao
     * Sempre subtrairemos o menor numero do maior
     * Manteremos o sinal do maior por conta da seguinte relacao(-x+y) = -(x-y) */
    else{
	/* Loop da subtracao ate o numero de algarismos de y */
	for(i=0;i<y->tamanho;i++){
	    x->numero[i] -= y->numero[i] - '0';
	    /* Subtrai 1 do proximo digito caso tenha sido necessario para a subtracao */
	    if(x->numero[i] < '0'){
		x->numero[i] += 10;
		x->numero[i+1]--;
	    }
	}

	/* Lida com digitos menores que zero depois do tamanho de y*/
	for(;i<x->tamanho;i++){
	    if(x->numero[i] >= '0') break;
	    x->numero[i] += 10;
	    x->numero[i+1]--;
	}
    }

    /* Ajusta o tamanho final de x */
    for(;x->numero[x->tamanho-1] == '0'; x->tamanho--);
}


/* Input: x (maior numerao), y (menor numerao)
 * Altera o valor de x para o valor da multiplicacao */
void multiplication(numerao *x, numerao *y){
    int i, j, k, n, c, aux;
    numerao mult;
    numerao carry;
    numerao num;

    /* Inicializa Variaveis */
    /* Resultado final da multiplicacao */
    mult.sinal = 1;
    mult.numero = malloc(maxSize*sizeof(char));
    mult.tamanho = 0;

    /* Numero advindo da multiplicao pelo digito */
    num.sinal = 1;
    num.numero = malloc(maxSize*sizeof(char));

    /* Numerao que guarda todo o carry */
    carry.sinal = 1;
    carry.numero = malloc(maxSize*sizeof(char));

    /* Multiplicara por cada digito do menor numero */
    for(i=0;i<y->tamanho;i++){
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

	/* para cada digito do menor numero multiplica por todos os digitos do maior
	 * e guarda respectivamente os valores do resultado em carry e num
	 * ex.: 9x9 = 81
	 *	carry = 8
	 *	num = 1 */
	for(j=0;j<x->tamanho;j++){
	    aux = (x->numero[j] - '0')*(y->numero[i] - '0');
	    carry.numero[c+j] = (aux/10) + '0';
	    carry.tamanho++;
	    num.numero[n+j] = (aux%10) + '0';
	    num.tamanho++;

	}

	/* [DEBUG]
	pn
	printf("num\n");
	printNumerao(num);
	printf("carry\n");
	printNumerao(carry);
	*/

	/* Ajusta o tamanho de num e de carry */
	for(;num.numero[num.tamanho-1] == '0'; num.tamanho--);
	for(;carry.numero[carry.tamanho-1] == '0'; carry.tamanho--);

	/* Soma os valores num e carry em mult. */
	/* Como a funcao sum precisa receber (maior numerao, menor numerao) e 
	 * altera o valor do maior numerao
	 * e necessario checar quem e o maior
	 * e depois fazer um ajuste para que o valor da soma seja acumulado em mult corretamente. */
	if(checkMaior(mult,num)){
	    sum(&mult,&num);
	}
	else{
	    sum(&num,&mult);
	    /* ajuste para que a soma fique salva em mult */
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
	    /* ajuste para que a soma fique salva em mult */
	    mult.tamanho = carry.tamanho;
	    for(k=0;k<mult.tamanho;k++){
		mult.numero[k] = carry.numero[k];
	    }
	}

	/* [DEBUG]
	printf("mult = ");
	printNumerao(mult);
	*/
    }

    /* Arruma o sinal final da multiplicacao */
    x->sinal *= y->sinal;
    /* [Metodo antigo]
     * if(x->sinal*y->sinal == 1) x->sinal = 1;
     * else x->sinal = -1; */

    /* FREEEEEE */
    free(x->numero);
    /* Faz com que os ponteiros de x apontem para mult */
    x->numero = mult.numero;
    x->tamanho = mult.tamanho;

    free(num.numero);
    free(carry.numero);
}


/* Recebe dois ponteiros de numeroes (comuns)
 * no final da operacao, o numerao x guardara o resto
 * e o numerao y guardara o resultado
 * */
void division(numerao *x, numerao *y){
    int i,j,t,anda;
    int xTamOri = x->tamanho, xSinOri = x->sinal;
    numerao xCopy;
    numerao tabuada[10];
    numerao m;
    numerao div;

    /* se o numerador for menor que o denominador
     * divisao = 0
     * resto = numerador */
    if(maiorComum(*y,*x) > 0){
	inverteNumerao(*x);
	y->tamanho = 0;
	return;
    }

    /* Inicializa as variaveis */
    /* Guarda uma copia de x para poder "descer" os proximos algarismo durante a divisao */
    xCopy.sinal = x->sinal;
    xCopy.numero = malloc(1005*sizeof(char));
    for(i=0;i<x->tamanho;i++){
	xCopy.numero[i] = x->numero[i];
    }
    xCopy.tamanho = x->tamanho;

    /* Guarda a tabuada do denominador para evitar refazer contas */
    for(i=0;i<10;i++){
	tabuada[i].sinal = 1;
	tabuada[i].numero = malloc(maxSize*sizeof(char));
	tabuada[i].numero[0] = '\0';
	tabuada[i].tamanho = 0;
    }
    
    /* Variavel que sera utilizada para criar a tabuada */
    m.sinal = 1;
    m.numero = malloc(1005*sizeof(char));
    for(i=0;i<y->tamanho;i++){
	m.numero[i] = y->numero[i];
    }
    m.tamanho = y->tamanho;

    /* resultado da divisao */
    div.sinal = x->sinal * y->sinal;
    div.numero = malloc((x->tamanho)*sizeof(char));
    div.tamanho = 0;

    /* Deixa x e y positivos para nao interfirir nas contas de soma */
    y->sinal = 1;
    x->sinal = 1;
    /***************************/

    /* Encontra o tamanho da primeira parte a ser dividida */
    for(x->tamanho = 1, anda = 0; maiorComum(*y,*x) > 0; x->tamanho++, anda++);

    /* Percorre todos os numeros do numerador */
    for(; anda < xTamOri; anda++){
	/* Puxa o proximo numero de xCopy para continuar a conta */
	if(maiorComum(*y,*x) > 0){
	    x->numero[x->tamanho] = xCopy.numero[anda];
	    x->tamanho++;
	}


	/* [DEBUG] 
	printNumerao(*x);
	printf("x->tamanho = %d\n", x->tamanho); */

	/* Encontra o maior multiplo de y que ainda seja menor que o valor a ser subtraido */
	for(i=1;i<10;i++){
	    /* Se o valor da tabuada ainda nao tiver sido calculado,
	     * calcula e salva o proximo numero */
	    if(tabuada[i].numero[0] == '\0'){
		/* copia o valor de m para a tabuada*/
		for(j=0;j<m.tamanho;j++){
		    tabuada[i].numero[j] = m.numero[j];
		}
		tabuada[i].tamanho = m.tamanho;

		/* m = m+y */
		inverteNumerao(m);
		inverteNumerao(*y);
		sum(&m,y);
		inverteNumerao(m);
		inverteNumerao(*y);
	    }
	    /* Se tabuada[i].numero tiver passado (ser maior) do o que queremos dividir,
	     * voltamos 1 numero na tabuada
	     * Se for exatamente igual saimos do loop com o multiplicador salvo em i */
	    t = maiorComum(tabuada[i],*x);
	    if(t==0) break;
	    if(t==1){
		i--;
		break;
	    }
	}
	/* Se chegamos ao indice 10 isso quer dizer que queremos o ultimo numero da tabuada
	 * tabuada[9] */
	if(i==10) i--;

	/* [DEBUG] 
	printf("tabuada[%d] = ", i);
	printNumerao(tabuada[i]); */
	
	
	/* [DEBUG] 
	for(j=0;j<10;j++){
	    printf("y x %d = ", j);
	    printNumerao(tabuada[j]);
	} */

	/* Realiza a subtracao entre x e o valor encontrado na tabuada */
	tabuada[i].sinal = -1;
	inverteNumerao(tabuada[i]);
	inverteNumerao(*x);

	/* [DEBUG]
	printf("tabuada[%d] = ", i);
	printNumerao(tabuada[i]);
	printf("x = ");
	printNumerao(*x);
	*/

	sum(x,&tabuada[i]);
	/* [DEBUG]
	printf("x = ");
	printNumerao(*x); */
	inverteNumerao(*x);
	inverteNumerao(tabuada[i]);
	tabuada[i].sinal = 1;

	/* Adiciona o indice no resultado da divisao */
	div.numero[div.tamanho] = i+'0';
	div.tamanho++;

	/* [DEBUG]
	printf("div = ");
	printNumerao(div);
	printf("x->tamanho = %d\n", x->tamanho); */
	
	/* [DEBUG]
	inverteNumerao(*x);
	printf("novo x = ");
	printNumerao(*x); */
	/* [DEBUG] 
	pn pn */
    }

    inverteNumerao(div);
    inverteNumerao(*x);

    /* Ajusta os sinais finais */
    x->sinal = xSinOri;
    y->sinal = div.sinal;
    /* Copia o resultado da divisao para y */
    /* Poderia ser uma solucao por mudanca nos ponteiros como na multiplicacao */
    for(i=0;i<div.tamanho;i++){
	y->numero[i] = div.numero[i];
    }
    y->tamanho = div.tamanho;

    /* FREEEEEE */
    free(div.numero);

    for(i=0;i<10;i++){
	free(tabuada[i].numero);
    }
    
    free(m.numero);
}


/* To do list:
 * Implementar Karatsuba
 * 
 * Gambiarras de invesoes de numeros na divisao poderiam ser evitadas por adaptacoes em algumas
 * funcoes como a checkMaior, porem fiquei sem tempo para tal
 */
