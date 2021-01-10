#include "include/X_cumagic.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <stdlib.h>

	Display *disp=NULL;
	Window finestra;
	Font f;
	GC gc;
	XEvent evt;
	int pnt;
	unsigned long negro,blanco;
	char lletra[2];

int X_init_w()
{
	disp=XOpenDisplay(NULL);
	f=XLoadFont(disp,"fixed");
	pnt=DefaultScreen(disp);
	blanco=WhitePixel(disp,pnt);
	negro=BlackPixel(disp,pnt);

	finestra=XCreateSimpleWindow(disp,DefaultRootWindow(disp),100,100,500,500,2,negro,blanco);
	XSelectInput(disp,finestra,ButtonPressMask | ButtonReleaseMask | KeyPressMask);
	XMapWindow(disp,finestra);

	gc=XCreateGC(disp,finestra,0,NULL);
	XSetFont(disp,gc,f);
}

void X_fi_w()
{
	//endwin();
}

int CapturaEvent(int *x, int *y){
	XNextEvent(disp,&evt);
	if (evt.type==ButtonPress){
	       *x=evt.xbutton.x;
	       *y=evt.xbutton.y;
	}
	return evt.type;
}

void X_printf(int y, int x, char* cadena){
	XDrawString(disp,finestra,gc,x,y,cadena,strlen(cadena));
}

void X_llegircar(char *car){
int llegircar=1;

	while(llegircar){
		XNextEvent(disp,&evt);
		switch(evt.type){
			case KeyPress:
				lletra[0]=evt.xkey.keycode;
				XDrawString(disp,finestra,gc,evt.xkey.x,evt.xkey.y,lletra,1);
				llegircar=0;
				break;
		}
	}
	*car=lletra[0];
}

void X_llegirenter(int *num){
int llegirenter=1;

	while(llegirenter){
		XNextEvent(disp,&evt);
		switch(evt.type){
			case KeyPress:
				lletra[0]=evt.xkey.keycode;
				XDrawString(disp,finestra,gc,evt.xkey.x,evt.xkey.y,lletra,1);
				llegirenter=0;
				break;
		}
	}
	*num=(int)lletra[0];

}

int X_init_color(){
/*
	if (has_colors())if (start_color()==ERR) return -1;
	//Inicialitza parells de colors
	init_pair(ENREIXAT,COLOR_YELLOW,COLOR_GREEN);
	init_pair(NOMBRES,COLOR_BLUE,COLOR_GREEN);
	init_pair(ENR_SEL,COLOR_YELLOW,COLOR_WHITE);
	init_pair(NOM_SEL,COLOR_RED,COLOR_WHITE);
	//Inicialitza fons
	bkgd(COLOR_BLACK);
*/
}


void X_dib_enreixat(int y, int x, int n){
int i;

	for(i=1;i<=n+1;i++){
		XDrawLine(disp,finestra,gc,x,y,x+n*AMP_C,y);
		y+=ALT_C;
	}
	for(i=1;i<=n+1;i++){
		XDrawLine(disp,finestra,gc,x,y,x,y+n*ALT_C);
		x+=AMP_C;
	}
	XFlush(disp);
}



int X_imp_cumagic(int n,t_enreixat *e)
{
int i,j,y,x;

//attron(COLOR_PAIR(NOMBRES));
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			y=e->cu[i][j].pos_num.y;x=e->cu[i][j].pos_num.x;
			if (e->cu[i][j].num) X_printf(y,x,"e->cu[i][j].num");
			if (!e->cu[i][j].num) X_printf(y,x,"   ");
		}
//attroff(COLOR_PAIR(NOMBRES));
	//Imprimir sumX i sumY
	for(i=0;i<n;i++){
		y=e->sumX[i].pos_num.y;x=e->sumX[i].pos_num.x;
		if (e->sumX[i].num) X_printf(y,x,"e->sumX[i].num");
		if (!e->sumX[i].num) X_printf(y,x,"    ");
		y=e->sumY[i].pos_num.y;x=e->sumY[i].pos_num.x;
		if (e->sumY[i].num) X_printf(y,x,"e->sumY[i].num");
		if (!e->sumY[i].num) X_printf(y,x,"    ");
	}
	//Imprimir diagonals
	y=e->DiaA.pos_num.y;x=e->DiaA.pos_num.x;
	if (e->DiaA.num) X_printf(y,x,"e->DiaA.num");
	if (!e->DiaA.num) X_printf(y,x,"    ");
	y=e->DiaB.pos_num.y;x=e->DiaB.pos_num.x;
	if (e->DiaB.num) X_printf(y,x,"e->DiaB.num");
	if (!e->DiaB.num) X_printf(y,x,"    ");
	XFlush(disp);
}

int X_sel_fc(int fila,int columna,t_enreixat *e,int *valor)
{
/*
	attron(COLOR_PAIR(NOM_SEL));
	*valor=e->cu[fila][columna].num;
	mvprintw(e->cu[fila][columna].pos_num.y,e->cu[fila][columna].pos_num.x,"%3d",e->cu[fila][columna].num);
	attroff(COLOR_PAIR(NOM_SEL));
*/
}

int X_desel_fc(int fila,int columna,t_enreixat *e)
{
/*
int valor;
	valor=e->cu[fila][columna].num;
	attron(COLOR_PAIR(NOMBRES));
	if (valor > 0) mvprintw(e->cu[fila][columna].pos_num.y,e->cu[fila][columna].pos_num.x,"%3d",valor);
	if (valor <=0) mvprintw(e->cu[fila][columna].pos_num.y,e->cu[fila][columna].pos_num.x,"    ");
	attroff(COLOR_PAIR(NOMBRES));
*/
}


int X_act_event_mouse()
{
/*
	raw();
	keypad(stdscr,TRUE);
	mousemask(ALL_MOUSE_EVENTS,0);
*/
}

int X_yx_fc(t_enreixat *e,int n,int y, int x, int *fila, int *columna)
{
int i,j,x_ini,x_fi,y_ini,y_fi,ok=1;
//mvprintw(25,25,"rat_yx_fc: y:%d x:%d %d %d %d %d",y,x,e->pos_erx.y,e->pos_erx.x,e->pos_erx.y + e->ly,e->pos_erx.x + e->lx);getch();
if ((y <= e->pos_erx.y) || (y >= (e->pos_erx.y + e->ly)) || (x <= e->pos_erx.x) || (x >= (e->pos_erx.x + e->lx))) return(0);
for (i=0;i<n;i++)
	for (j=0;j<n;j++)
	{
		x_ini=e->cu[i][j].pos_cas.x;
		x_fi=x_ini+e->cu[i][j].lx;
		y_ini=e->cu[i][j].pos_cas.y;
		y_fi=y_ini+e->cu[i][j].ly;
//mvprintw(20,20,"x0: %d x1: %d y0: %d y1: %d",x_ini,x_fi,y_ini,y_fi);getch();
		if ((x >= x_ini) && (x <= x_fi) && (y >= y_ini) && (y <= y_fi))
		{
			*fila=i;
			*columna=j;
			//mvprintw(20,20,"FILA: %d COLUMNA: %d",*fila,*columna);getch();
			return(1);
		}
	}
return(0);
}
