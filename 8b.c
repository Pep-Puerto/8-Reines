#include <stdio.h>
#include <stdlib.h>
#define MAX 8
#define TRUE 1
#define FALSE 0

int Taulell[MAX][MAX];
int Columna_de_reina[MAX];
int posicio_inicial(int Fila[MAX]);
int ubicar_reina(int reina);
int desubicar_reina(int reina);
int posicio_segura(int reina, int pos);
int no_reina_en_columna(int reina,int columna);
int no_reina_en_diagonal_A(int reina_ubicada,int fila_reina,int col_reina);
int imprimir_Taulell();
int inicialitzar_Taulell();

int main(){
int reina=0;
	inicialitzar_Taulell();
	while (reina<MAX){
		if (ubicar_reina(reina)) reina++;
		else reina--;
	}
	imprimir_Taulell();
	printf("\n%d\n",reina);
}

int ubicar_reina(int reina){
int pos_ini=0, ubicada=FALSE;

	pos_ini=posicio_inicial(Taulell[reina]);
//printf("reina %d pos_ini %d \n",reina, pos_ini);
	Taulell[reina][pos_ini]=0;
	Columna_de_reina[reina]=0;
	if (pos_ini==(MAX-1)) return FALSE;
	if (pos_ini>0) pos_ini++;
	while ((pos_ini<MAX) && !(ubicada)){
		if (posicio_segura(reina, pos_ini)){
			Taulell[reina][pos_ini]=1;
			Columna_de_reina[reina]=pos_ini;
			ubicada=TRUE;
		}
		else pos_ini++;
	}
	imprimir_Taulell();
	printf("\n%d\n",reina);
	getchar();
	return ubicada;
}
int desubicar_reina(int reina){
	Taulell[reina][Columna_de_reina[reina]]=0;
	Columna_de_reina[reina]=0;
}

int posicio_inicial(int Fila[MAX]){
int pos_ini=0;
	while ((pos_ini<MAX) && !(Fila[pos_ini])) pos_ini++;
	if (pos_ini==8) pos_ini=0;
	return (pos_ini);
}

int posicio_segura(int reina, int columna){
int reina_ubicada;
int i;
//Veure que no esta a la mateixa columna de cap reina anterior
	reina_ubicada=0;
	while ((reina_ubicada<reina) && (no_reina_en_columna(reina_ubicada,columna))) reina_ubicada++;
	if (reina_ubicada < reina) return FALSE;
	reina_ubicada=0;
	while ((reina_ubicada<reina) && (no_reina_en_diagonal_A(reina_ubicada,reina,columna))) reina_ubicada++;
	if (reina_ubicada < reina) return FALSE;

//for (i=0;i<MAX;i++) printf("%d",Columna_de_reina[i]);getchar();
//Veure que no esta en les diagonals de les reines ubicades

return TRUE;
}

int no_reina_en_columna(int reina,int columna){
	return (Columna_de_reina[reina]!=columna);
}

int no_reina_en_diagonal_A(int r_ubicada,int fila_r,int col_r){
int i,j;
	i=r_ubicada;
	j=Columna_de_reina[r_ubicada];
//printf("f_r_ubicada %d c_r_ubicada %d",i,j);getchar();
	while ((fila_r!=i) && (col_r!=j) && (i<MAX) && (j<MAX)){i++;j++;};
	if ((fila_r==i) && (col_r==j)) return FALSE;
	return TRUE;
}

int inicialitzar_Taulell(){
int i,j;
	for (i=0;i<MAX;i++)
		for (j=0;j<MAX;j++)
			Taulell[i][j]=0;
}

int imprimir_Taulell(){
int i,j;
	for (i=0;i<MAX;i++){
		for (j=0;j<MAX;j++)
			printf ("%4d",Taulell[i][j]);
		printf("\n");
	}
}