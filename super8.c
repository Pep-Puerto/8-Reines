#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX 12
#define TOPE MAX-1
#define DESUBICADA -1
#define SIMB_POC '-'
#define SIMB_PIC 'O'

int COL_D_REINA[MAX];
int reina_fin;
int reina_ini;

int NUM_SOL[MAX][MAX];
char PIC_SOL[MAX][MAX];

int ubicar_reina(int reina);
int posicio_segura(int reina, int pos);
int seg_reina(int reina);
int ant_reina(int reina);
int reina_en_col(int reina,int columna);
int reina_en_dia(int reina_ubi,int fila_reina,int col_reina,void
 (*seg)(int *,int *),void (*ant)(int *,int *));
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
int afegir_solucio();
int imprimir_num_solucions();
int ini_num_solucions();
int ini_pic();
int imp_pic();


int main(){
int i,j;
int reina,col,solucio;
	ini_num_solucions();
	for(reina=0;reina<MAX;reina++)
		for(col=0;col<MAX;col++){
//printf("Reina: %d Columna: %d",reina,col);getchar();
			inicialitzar_Taulell();
			reina_ini=reina;
			reina_fin=reina;
			solucio=0;
			COL_D_REINA[reina]=col-1;
			do{
				do{
					if (ubicar_reina(reina))reina=seg_reina(reina);
					else reina=ant_reina(reina);
				}while (reina!=reina_fin);
				if (es_solucio()){afegir_solucio();solucio++;};
			}while(mes_solucions(&reina));
imprimir_num_solucions();
		}
	imprimir_num_solucions();
	while(1){
	for(i=0;i<MAX;i++)
		for(j=0;j<MAX;j++){
			imp_pic(NUM_SOL[i][j]);
			getchar();
		}
	}
}

int es_solucio(){
int i;
	for(i=0;i<MAX;i++) if (COL_D_REINA[i]==DESUBICADA) return FALSE;
	return TRUE;
}
int mes_solucions(int *reina){
int pos;
	if (es_solucio()){
		(*reina)=ant_reina(*reina);
		COL_D_REINA[*reina]=DESUBICADA;
		(*reina)=ant_reina(*reina);
		return TRUE;
	}
	return FALSE;
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
	while ((reina_ubi!=reina) && !(reina_en_col(reina_ubi,col)))
 reina_ubi=seg_reina(reina_ubi);
	if (reina_ubi!=reina) return FALSE;
	//Veureque no esta a la diagonal_A de cap reina anterior
	reina_ubi=reina_ini;
	while ((reina_ubi!=reina) &&
 !(reina_en_dia(reina_ubi,reina,col,&seg_dA,&ant_dA)))
 reina_ubi=seg_reina(reina_ubi);
	if (reina_ubi!=reina) return FALSE;
	//Veure que no esta a la diagonal_B de cap reina anterior
	reina_ubi=reina_ini;
	while ((reina_ubi!=reina) &&
 !(reina_en_dia(reina_ubi,reina,col,&seg_dB,&ant_dB)))
 reina_ubi=seg_reina(reina_ubi);
	if (reina_ubi!=reina) return FALSE;
	return TRUE;
}

int reina_en_col(int reina,int columna){
	return (COL_D_REINA[reina]==columna);
}

int reina_en_dia(int r_ubicada,int fila_r,int col_r,void (*seg)(int
 *,int *),void (*ant)(int *,int *)){
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

int seg_reina(int reina){reina++;if (reina>TOPE) reina=0;return
 reina;}
int ant_reina(int reina){reina--;if (reina<0) reina=TOPE;return
 reina;}
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

int afegir_solucio(){
int reina;
//printf("Afegint solucio...");getchar();
NUM_SOL[reina_ini][COL_D_REINA[reina_ini]]=NUM_SOL[reina_ini][COL_D_REINA[reina_ini]]+1;}

int imprimir_num_solucions(){
int i,j;
	printf("\n");
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++)
			printf ("%6d",NUM_SOL[i][j]);
		printf("\n");
	}
}

int ini_num_solucions(){
int i,j;
	for(i=0;i<MAX;i++)
		for(j=0;j<MAX;j++)
			NUM_SOL[i][j]=0;
}

int ini_pic(){
int i,j;
	for(i=0;i<MAX;i++)
		for(j=0;j<MAX;j++)
			PIC_SOL[i][j]=SIMB_POC;
}

int imp_pic(valor){
int i,j;
	ini_pic();
	printf("\n");
	for(i=0;i<MAX;i++){
		for(j=0;j<MAX;j++){
			if (NUM_SOL[i][j]==valor) PIC_SOL[i][j]=SIMB_PIC;
			printf ("%2c",PIC_SOL[i][j]);
		}
		printf("\n");
	}
}
