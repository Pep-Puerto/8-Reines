#include "glb_cumagic.h"

#define ENREIXAT	1
#define NOMBRES		2
#define ENR_SEL		3
#define NOM_SEL		4



int X_init_w();
void X_fi_w();
void X_printf(int y, int x, char* cadena);
void X_llegircar(char *op);
void X_llegirenter(int *num);
int X_imp_cumagic(int n,t_enreixat *e);
void X_dib_enreixat(int y, int x, int costat);

void X_cuadre(int y,int x,int alt,int amp);
int X_sel_fc(int fila,int columna,t_enreixat *e,int *valor);
int X_desel_fc(int fila,int columna,t_enreixat *e);
int X_init_color();



int X_act_event_mouse();
int X_yx_fc(t_enreixat *e,int n,int y, int x, int *fila, int *columna);
int CapturaEvent(int *x, int *y);