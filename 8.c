#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 8
#define TOPE MAX-1
#define DESUBICADA -1

int COL_D_REINA[MAX];
int reina_fin;
int reina_ini;

int ubicar_reina(int reina);
int posicio_segura(int reina, int pos);
int seg_reina(int reina);
int ant_reina(int reina);
int reina_en_col(int reina,int columna);
int reina_en_dia(int reina_ubi,int fila_reina,int col_reina,void (*seg)(int *,int *),void (*ant)(int *,int *));
void seg_dA(int *i,int *j);
void ant_dA(int *i,int *j);
void seg_dB(int *i,int *j);
void ant_dB(int *i,int *j);
int imprimir_Taulell(int solucio);
int inicialitzar_Taulell();
void posicio_de_partida(int *reina,int *col);
int continuar();
int es_solucio();
int mes_solucions();

int main(){
int reina,col,solucio;
	do{
		inicialitzar_Taulell();
		posicio_de_partida(&reina,&col);
		reina_ini=reina;
		reina_fin=reina;
		solucio=0;
		COL_D_REINA[reina]=col-1;
		do{
			do{
				if (ubicar_reina(reina))reina=seg_reina(reina);
				else reina=ant_reina(reina);
			}while (reina!=reina_fin);
			if (es_solucio()) imprimir_Taulell(++solucio);
		}while(mes_solucions(&reina));
		getchar();
	}while(continuar());
}
int es_solucio(){
int i;
	for(i=0;i<MAX;i++) if (COL_D_REINA[i]==DESUBICADA) return FALSE;
	return TRUE;
}
int mes_solucions(int *reina){
int pos;
	if (!es_solucio()){
		printf("\n----------------------------");
		printf("\nNo hi ha mes solucions!.\n ");
		printf("----------------------------\n");
		return FALSE;
	}
	(*reina)=ant_reina(*reina);
//printf(" \n *reina%d \n",*reina);
	COL_D_REINA[*reina]=DESUBICADA;
	(*reina)=ant_reina(*reina);
//printf(" \n *reina%d \n",*reina);
	if (mes_solucions){
		printf("\nAltra solucio?(s/n) ");
		return(getchar()=='s');
	}else return FALSE;
}

int continuar(){
	printf("\nDessitjes continuar?(s/n) ");
	return (getchar()=='s');
}
void posicio_de_partida(int *reina,int *col){
	printf("\nDona'm fila i columna de inici...\n");
	printf("Fila?: \n");
	scanf("%d",reina);
	printf("Columna?: \n");
	scanf("%d",col);
}

int ubicar_reina(int reina){
int pos,ubicada=FALSE;
	pos=COL_D_REINA[reina];
	if (pos==TOPE){
		COL_D_REINA[reina]=DESUBICADA;
		return FALSE;
	}
	pos++;
	while ((pos<MAX) && !(ubicada)){
		if (posicio_segura(reina, pos)){
			COL_D_REINA[reina]=pos;
			ubicada=TRUE;
		}
		else pos++;
	}
	if (!ubicada) COL_D_REINA[reina]=DESUBICADA;
	return ubicada;
}

int posicio_segura(int reina, int col){
int reina_ubi;
	//Veure que no esta a la mateixa columna de cap reina anterior
	reina_ubi=reina_ini;
	while ((reina_ubi!=reina) && !(reina_en_col(reina_ubi,col))) reina_ubi=seg_reina(reina_ubi);
	if (reina_ubi!=reina) return FALSE;
	//Veureque no esta a la diagonal_A de cap reina anterior
	reina_ubi=reina_ini;
	while ((reina_ubi!=reina) && !(reina_en_dia(reina_ubi,reina,col,&seg_dA,&ant_dA))) reina_ubi=seg_reina(reina_ubi);
	if (reina_ubi!=reina) return FALSE;
	//Veure que no esta a la diagonal_B de cap reina anterior
	reina_ubi=reina_ini;
	while ((reina_ubi!=reina) && !(reina_en_dia(reina_ubi,reina,col,&seg_dB,&ant_dB))) reina_ubi=seg_reina(reina_ubi);
	if (reina_ubi!=reina) return FALSE;
	return TRUE;
}

int reina_en_col(int reina,int columna){
	return (COL_D_REINA[reina]==columna);
}

int reina_en_dia(int r_ubicada,int fila_r,int col_r,void (*seg)(int *,int *),void (*ant)(int *,int *)){
int i,j;
	i=r_ubicada;
	j=COL_D_REINA[r_ubicada];
	while ((fila_r!=i) && (col_r!=j) && (i<MAX) && (j<MAX)) seg(&i,&j);
	if ((fila_r==i) && (col_r==j)) return TRUE;
	i=r_ubicada;
	j=COL_D_REINA[r_ubicada];
	while ((fila_r!=i) && (col_r!=j) && (i>=0) && (j>=0)) ant(&i,&j);
	if ((fila_r==i) && (col_r==j)) return TRUE;
	return FALSE;
}

int seg_reina(int reina){reina++;if (reina>TOPE) reina=0;return reina;}
int ant_reina(int reina){reina--;if (reina<0) reina=TOPE;return reina;}
void seg_dA(int *i,int *j){(*i)++;(*j)++;}
void ant_dA(int *i,int *j){(*i)--;(*j)--;}
void seg_dB(int *i,int *j){(*i)++;(*j)--;}
void ant_dB(int *i,int *j){(*i)--;(*j)++;}

int inicialitzar_Taulell(){
int reina;
	for (reina=0;reina<MAX;reina++) COL_D_REINA[reina]=DESUBICADA;
}

int imprimir_Taulell(int solucio){
int reina,columna;
	printf("\n\n");
	for (reina=0;reina<MAX;reina++){
		for (columna=0;columna<MAX;columna++)
			if ((columna<COL_D_REINA[reina]) || (columna>COL_D_REINA[reina]))
				printf ("%2d",0);
			else printf ("%2d",1);
		printf("\n");
	}
	printf("-----------------------------");
	printf("\n SOLUCIO: %d \n", solucio);
	getchar();
	return TRUE;
}
