//Using libs SDL, glibc
#include <SDL2/SDL.h>	//SDL version 2.0

#include <stdlib.h>
#include <stdio.h>



// Numbers bitmap, some routines and and SDL initialization taken from
// https://github.com/flightcrank/pong


// Please follow the coding guidelines described in:
// https://users.ece.cmu.edu/~eno/coding/CCodingStandard.html



/* Do not use magic numbers in the code, define the meaning of the number
   in this section and the use the define across the code. This increases
   readability accross the code
*/


// The constants used to define the size of the window
#define SCREEN_WIDTH 960	//window height
#define SCREEN_HEIGHT 780	//window width

// The constants used for the movement of the block
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3


// For the return of the functions
#define SUCCESS 0
#define FAILURE 1


// Defines for states
#define FALSE 0
#define TRUE 1

// The colors used in the game
#define BLACK 0x000000ff
#define WHITE 0xffffffff





//function prototypes
//initialise SDL
int init_SDL(int w, int h, int argc, char *args[]);

// Estructuras
typedef struct muro {//Estructura para los muros

	int x,y;// posicion
	int w,h;// tamano
} muro_t;

typedef struct worrior {//Estructura para los tiradores

	int x,y;// tirador width and height
	int w,h;// position on the screen
	int vida;//Vida de los tiradores
	int direccion;//Dirección para los tiradores
	int muerte;//Cantidad de muertes de los tiradores
} worrior_t;

// Avoid the use of global variables, modify the code to avoid its use.
int g_width, g_height;		//used if fullscreen

SDL_Window* window = NULL;	//The window we'll be rendering to
SDL_Renderer *renderer;		//The renderer SDL will use to draw to the screen

//surfaces
static SDL_Surface *screen;
static SDL_Surface *title;
static SDL_Surface *game_menu;

static SDL_Surface *puntos;
static SDL_Surface *interfaz_in_user;
static SDL_Surface *insert_coin;
static SDL_Surface *numblab;
static SDL_Surface *end;
static SDL_Surface *laberinto2;
static SDL_Surface *laberinto3;
static SDL_Surface *sprites;
static SDL_Surface *one_coin;
static SDL_Surface *two_coin;
static SDL_Surface *radar;

//textures
SDL_Texture *screen_texture;


//variables

int level;
int lifes=0;


int llamada=0;
int cant_num_sprite_tir = 0;
int t = 0;
int tiempo = 0;
int tiempo_vida = 0;
int tiempo_vel=0;
int vel = 1;
int v;
int vel_tiempo = 10;
int portal=0;
int enemigo_d = 0;
int level;
int gen=0;

int disparo=0;
int contador=0;

static muro_t muro[152];
static worrior_t worrior[20];



static void crear_paredes () { //Función encargada de dibujar los muros del mapa

	SDL_Rect src;
	int i;

	for (i = 0; i < 150; i++){

		if(i!=73 && i!=74){

			src.x = muro[i].x;
			src.y = muro[i].y;
			src.w = muro[i].w;
			src.h = muro[i].h;

			if (i!=71 && i!=72 && i!=149){

				int r = SDL_FillRect(screen, &src, 0xffff5916);

				if (r !=0){

				printf("fill rectangle faliled in func draw_muro()");
				}
			}
				if (i==149 && (worrior[0].muerte==0||worrior[0].vida==0))
				{
					int r = SDL_FillRect(screen, &src, 0xffff5916);

					if (r !=0){

					printf("fill rectangle faliled in func draw_muro()");
					}
				}
		}
		/*else{
				if(portal==1) //Dibuja un muro rojo en el portal si alguien lo ha cruzado
				{
					src.x = muro[i].x;
					src.y = muro[i].y;
					src.w = muro[i].w;
					src.h = muro[i].h;

					int r = SDL_FillRect(screen, &src, 0xff0810d2);

					if (r !=0){

					printf("fill rectangle faliled in func draw_muro()");
					}
				}
		}*/
	}
}

static void mapa1(){ //Función encargada de dibujar los muros del nivel 1


	portal = 0;
	tiempo=0;
	tiempo_vel=0;
	worrior[0].muerte=1;

	//lineas verticales
	for (int i = 6; i <16 ; ++i)
	{
		muro[i].y = 242;
    }
 	muro[6].x = 260;
	muro[7].x = 308;
	muro[8].x = 356;
	muro[9].x = 404;
    muro[10].x = 500;
	muro[11].x = 548;
	muro[12].x = 596;
	muro[13].x = 644;
    muro[14].x = 692;

	for (int i = 16; i < 20; ++i)
	{
		muro[i].y = 290;
	}

	muro[16].x = 356;
	muro[17].x = 452;
	muro[18].x = 500;
	muro[19].x = 596;


	muro[20].x = 308;
	muro[20].y = 338;
	muro[21].x = 644;
	muro[21].y = 338;

	for (int i = 22; i < 28; ++i)
	{
		muro[i].y = 386;
	}

	muro[22].x = 260;
	muro[23].x = 356;
	muro[24].x = 452;
	muro[25].x = 500;
	muro[26].x = 596;
	muro[27].x = 692;

	muro[28].x = 308;
	muro[28].y = 434;
	muro[29].y = 434;
	muro[29].x = 644;

	//lineas horizontal

	muro[85].x = 360;
	muro[86].x = 552;
	muro[85].y = 334;
	muro[86].y = 334;

	muro[87].x = 312;
	muro[88].x = 600;
	muro[87].y = 382;
	muro[88].y = 382;

	muro[89].x = 408;
	muro[90].x = 504;
	muro[89].y = 430;
	muro[90].y = 430;

	//t=0;
}

static void mapa2(){ //Función encargada de dibujar los muros del nivel 2


	worrior[0].muerte = 1;
	lifes++;
	worrior[0].vida = lifes;

	//paredes verticales
	muro[6].x = 404;
	muro[6].y = 194;
	muro[7].y = 194;
	muro[7].x = 548;

	for (int i = 8; i < 12; i++)
	{
		muro[i].y = 242;
	}
	muro[8].x = 260;
	muro[9].x = 452;
	muro[10].x = 500;
	muro[11].x = 692;

	muro[12].y = 290;
	muro[13].y = 290;
	muro[12].x = 308;
	muro[13].x = 644;

	for (int i = 14; i <18; ++i)
	{
		muro[i].y = 338;
	}
	muro[14].x = 308;
	muro[15].x = 356;
	muro[16].x = 596;
	muro[17].x = 644;

	muro[18].y = 386;
	muro[19].y = 386;
	muro[18].x = 260;
	muro[19].x = 692;

	muro[20].y = 434;
	muro[21].y = 434;
	muro[20].x = 356;
	muro[21].x = 596;

	//horizontal

    int	j = 0;

	for (int i = 85; i < 89; ++i)
	{
		muro[i].y = 238;
	}

	muro[85].x = 264;
	muro[86].x = 312;
	muro[87].x = 600;
	muro[88].x = 648;

	for (int i = 89; i < 93; ++i)
	{
		muro[i].y = 286;
	}

	muro[89].x = 312;
	muro[90].x = 360;
	muro[91].x = 552;
	muro[92].x = 600;

	for (int i = 93; i < 96; ++i)
	{
		muro[i].x = 408;
		muro[i].y = ((23+j*6)*8)+150;
		j++;
	}

	muro[96].y = 382;
	muro[96].x = 456;

	j=0;

	for (int i = 97; i < 100; ++i)
	{
		muro[i].x = 504;
		muro[i].y = ((23+j*6)*8)+150;
		j++;
	}

	//t=0;
}

static void dibuja_cuadro() {

	// muro vertical
	for (int i = 6; i < 75; i++)
	{
		muro[i].x=screen->w + 2;
		muro[i].y=screen->h;
		muro[i].w = 8;
		muro[i].h = 48;
	}
	//muro horizontal

	for (int i = 79; i < 150; i++)
	{
		muro[i].x=screen->w + 2;
		muro[i].y=screen->h;
		muro[i].w = 48;
		muro[i].h = 8;
	}
// barras verticales del cuadro
	for (int i = 0; i < 6; i++)
	{
		muro[i].w = 4;
	}

	muro[0].x = 216;
	muro[0].y = 198;
	muro[0].h = 92;

	muro[1].x = 216;
	muro[1].y = 337;
	muro[1].h = 193;

	muro[2].x = 260;
	muro[2].y = 482;
	muro[2].h = 48;

	muro[3].x = 696;
	muro[3].y = 482;
	muro[3].h = 48;

	muro[4].x = 740;
	muro[4].y = 337;
	muro[4].h = 193;

	muro[5].x = 740;
	muro[5].y = 198;
	muro[5].h = 92;

//barras horizontales del cuadro
	for (int i = 75; i < 79; i++)
	{
		muro[i].h = 4;
	}

	muro[75].x = 216;
	muro[75].y = 194;
	muro[75].w = 528;

	muro[76].x = 260;
	muro[76].y = 478;
	muro[76].w = 440;

	muro[77].x = 220;
	muro[77].y = 526;
	muro[77].w = 40;

	muro[78].x = 700;
	muro[78].y = 526 ;
	muro[78].w = 40;

	muro[79].x = 220;
	muro[79].y = 334;
	//muro[79].w = 44;
	//muro[79].h = 8;

	muro[80].x = 696;
	muro[80].y = 334;
	//muro[80].w = 44;
	//muro[80].h = 8;

	muro[81].x = 168;
	muro[81].y = 286;

	muro[82].x = 744;
	muro[82].y = 286;

	muro[83].x = 168;
	muro[83].y = 334;

	muro[84].x = 744;
	muro[84].y = 334;

	muro[148].x = 216;
	muro[148].y = 478;

	muro[149].x = 696;
	muro[149].y = 478;

}

static void muro_temp(int a){ //Es el muro que desaparece cuando el tirador sale de la sala de espera xD
	switch (a) {
		case 0 :
		muro[73].x = 740;
		muro[73].y = 290;
		muro[73].w = 5;
		muro[73].h = 47;
		muro[74].x = 215;
		muro[74].y = 290;
		muro[74].w = 5;
		muro[74].h = 47;
		break;
	}
}

//Inicializacion de la posicion y tamaño de los elementos
static void game_inicialization() {

    dibuja_cuadro();

	worrior[0].x = 5000;
	worrior[0].y = 5000;
	worrior[0].w = 36;
	worrior[0].h = 36;
	worrior[0].vida = lifes;
	worrior[0].muerte=0;
	worrior[0].direccion = 3;
	worrior[1].x = 702;
	worrior[1].y = 488;
	worrior[1].w = 36;
	worrior[1].h = 36;
	//bullet[0].x = 5500;
	//bullet[0].y = 5500;

	for (int i = 2; i <= worrior[0].vida; i++)
	{
		if(i > 5)
		{
			worrior[i].x = 750;
			worrior[i].y = 536 - i*48;
			worrior[i].w = 36;
			worrior[i].h = 36;
		}
		else {
			worrior[i].x = 750;
			worrior[i].y = 584 - i*48;
			worrior[i].w = 36;
			worrior[i].h = 36;
		}
	}


/*
	for (int i = 0; i < 6; ++i)
	{
		enemigo[i].color = 0;
		enemigo[i].velocidad = 0;
	}
	enemigo[6].color = 1;
	enemigo[6].velocidad = 2;
	enemigo[7].color = 2;
	enemigo[7].velocidad = 2;
	enemigo[8].color = 1;
	enemigo[8].velocidad = 2;
	enemigo[9].color = 2;
	enemigo[9].velocidad = 2;
	enemigo[10].color = 1;
	enemigo[10].velocidad = 2;
	enemigo[11].color = 2;
	enemigo[11].velocidad = 2;
	enemigo[12].color = 3;
	enemigo[12].velocidad = 5;
	enemigo[13].color = 4;
	enemigo[13].velocidad = 5;

	for (int j = 0; j < enemigos_tot; j++)
	{
		enemigo[j].x=6000;
		enemigo[j].y=6000;
		enemigo_radar[j].x = 6000;
		enemigo_radar[j].y = 6000;
	}*/
}


static void menu(int fase) { //Función encargada de dibujar el menu


	SDL_Rect src;
	SDL_Rect dest;


	switch (fase)
	{
		case 0:
            src.x = 0;
            src.y = 0;
            src.w = title->w;
            src.h = title->h;

            dest.x = (screen->w / 2) - (src.w / 2);
            dest.y = (screen->h / 2) - (src.h / 2);
            dest.w = title->w;
            dest.h = title->h;

            SDL_BlitSurface(title, &src, screen, &dest);

			break;

		case 1:
            src.x = 0;
            src.y = 0;
            src.w = game_menu->w;
            src.h = game_menu->h;

            dest.x = 0;
            dest.y = 0;
            dest.w = game_menu->w;
            dest.h = game_menu->h;

            SDL_BlitSurface(game_menu, &src, screen, &dest);
			break;

        case 2:
			src.x = 0;
			src.y = 0;
			src.w = puntos->w;
			src.h = puntos->h;

			dest.x = (screen->w / 2) - (src.w / 2);
			dest.y = (screen->h / 2) - (src.h / 2);
			dest.w = puntos->w;
			dest.h = puntos->h;

			SDL_BlitSurface(puntos, &src, screen, &dest);


			break;

		case 3:
			src.x = 160;
			src.y = 150;
			src.w = 640;
			src.h = 480;

			dest.x=0;
			dest.y=0;
			dest.w=640;
			dest.h=480;

			SDL_BlitSurface(one_coin, &dest, screen, &src);
			break;
		case 4:
			src.x = 160;
			src.y = 150;
			src.w = 640;
			src.h = 480;

			dest.x=0;
			dest.y=0;
			dest.w=640;
			dest.h=480;
			SDL_BlitSurface(two_coin, &dest, screen, &src);
			break;

	}
}

static void cuadro_de_juego(){ //Función encargada de dibujar la interfaz de ususario mediante sprites con la librería SDL

	SDL_Rect src;
	SDL_Rect dest;

			src.x = 0;
			src.y = 0;
			src.w = interfaz_in_user->w;
			src.h = interfaz_in_user->h;

			dest.x = (screen->w / 2) - (src.w / 2);
			dest.y = (screen->h / 2) - (src.h / 2);
			dest.w = interfaz_in_user->w;
			dest.h = interfaz_in_user->h;

	SDL_BlitSurface(interfaz_in_user, &src, screen, &dest);
}

static void crea_worrior() { //muestra en pantalla al worrior y las vidas

	SDL_Rect src;
	SDL_Rect dest;
	int i;


	for (i = 1; i <= worrior[0].vida; i++) {
		src.x = worrior[i].x;
		src.y = worrior[i].y;
		src.w = worrior[i].w;
		src.h = worrior[i].h;
		dest.x=0;
		dest.y=108;
		dest.w=36;
		dest.h=36;
		SDL_BlitSurface(sprites, &dest, screen, &src);
	}
}

static void tirador_sprites () {//dibuja al tirador caminando o disparando

	SDL_Rect dest;
	SDL_Rect src;

	src.x = worrior[0].x;
	src.y = worrior[0].y;
	src.w = worrior[0].w;
	src.h = worrior[0].h;
	if (worrior[0].vida >= 0){

		if (disparo==1)
		{
			if (worrior[0].muerte==0)
			{
				dest.x= 108 + worrior[0].direccion*36;
				dest.y=216;
				dest.w=36;
				dest.h=36;
				SDL_BlitSurface(sprites, &dest, screen, &src);
				if((contador/7)<10)////////////////////////////////////////////////////////
				{
					contador++;
				}
				if ((contador/7)==1)
				{
					disparo=0;
					contador=0;
				}
			}
		}

		if (disparo==0)
		{
			if (worrior[0].muerte==0)
			{
				if (cant_num_sprite_tir >= 0)
				{
					dest.x=cant_num_sprite_tir*36;
					dest.y=108;
					dest.w=36;
					dest.h=36;
					SDL_BlitSurface(sprites, &dest, screen, &src);
				}
			}

		}
	}
}


static void tirador_movimiento(int direction) { //Función encargada del movimiento del tirador

	int x,y;
	int velocidad = 8;
	x = worrior[0].x;
	y = worrior[0].y;

	if (worrior[0].vida>0 && worrior[0].muerte==0){}
	if(t%3==2){

// flecha arriba
	if (direction == 0) {

        if(worrior[0].y <= 0) {

            worrior[0].y = 0;

        }
        else {
            if ((worrior[0].x - 80) % 48 == 30 || (worrior[0].x - 80) % 48 == -18){
                worrior[0].y -= velocidad;
                worrior[0].direccion = 0;

                if (cant_num_sprite_tir > 5 && cant_num_sprite_tir < 8)
                {
                    cant_num_sprite_tir++;
                }
                else
                {
                    cant_num_sprite_tir = 6;
                }
            }
            else
            {
            if (worrior[0].direccion == 1)
            {
                worrior[0].x += velocidad;
                worrior[0].direccion = 1;
            if (cant_num_sprite_tir > 2 && cant_num_sprite_tir < 5)
            {
                cant_num_sprite_tir++;
            }
            else
            {
                cant_num_sprite_tir = 3;
            }
            }

            if (worrior[0].direccion == 3)
            {
                worrior[0].x -= velocidad;
                worrior[0].direccion = 3;
            if (cant_num_sprite_tir < 2)
            {
                cant_num_sprite_tir++;
            }
            else{
                cant_num_sprite_tir = 0;
            }
            }

            }
        }
	}

	// flecha abajo
	if (direction == 2) {

        if(worrior[0].y >= screen->h - worrior[0].h) {

        worrior[0].y = screen->h - worrior[0].h;

        }
        else {

        if ((worrior[0].x - 80) % 48 == 30 || (worrior[0].x - 80) % 48 == -18){
            worrior[0].y += velocidad;
            worrior[0].direccion = 2;
        if (cant_num_sprite_tir > 8 && cant_num_sprite_tir < 11)
        {
            cant_num_sprite_tir++;
        }
        else{
            cant_num_sprite_tir = 9;
        }
        }
        else
        {
        if (worrior[0].direccion == 1)
        {
            worrior[0].x += velocidad;
            worrior[0].direccion = 1;
        if (cant_num_sprite_tir > 2 && cant_num_sprite_tir < 5)
        {
            cant_num_sprite_tir++;
        }
        else{
            cant_num_sprite_tir = 3;
        }
        }
        if (worrior[0].direccion == 3)
        {
            worrior[0].x -= velocidad;
            worrior[0].direccion = 3;
        if (cant_num_sprite_tir < 2)
        {
            cant_num_sprite_tir++;
        }
        else{
            cant_num_sprite_tir = 0;
        }
        }
        }
        }
	}

// derecha
	if (direction == 1) {

        if(worrior[0].x >= screen->w - worrior[0].w) {

            worrior[0].x = screen->w - worrior[0].w;

        }
        else
        {
        if ((worrior[0].y - 68) % 48 == 30 || (worrior[0].y - 68) % 48 == -18){
                worrior[0].x += velocidad;
                worrior[0].direccion = 1;
            if (cant_num_sprite_tir > 2 && cant_num_sprite_tir < 5)
            {
                cant_num_sprite_tir++;
            }
            else{
                cant_num_sprite_tir = 3;
            }
        }
        else
        {
            if (worrior[0].direccion == 0)
            {
                    worrior[0].y -= velocidad;
                    worrior[0].direccion = 0;
                if (cant_num_sprite_tir > 5 && cant_num_sprite_tir < 8)
                {
                    cant_num_sprite_tir++;
                }
                else{
                    cant_num_sprite_tir = 6;
                }
            }
            if (worrior[0].direccion == 2)
            {
                    worrior[0].y += velocidad;
                    worrior[0].direccion = 2;
                if (cant_num_sprite_tir > 8 && cant_num_sprite_tir < 11)
                {
                    cant_num_sprite_tir++;
                }
                else{
                    cant_num_sprite_tir = 9;
                }
            }
        }
        }
	}
	// izquierda
	if (direction == 3) {

        if(worrior[0].x <= 0) {

            worrior[0].x = 0;

        }
        else
        {

            if ((worrior[0].y - 68) % 48 == 30 || (worrior[0].y - 68) % 48 == -18){
                worrior[0].x -= velocidad;
                worrior[0].direccion = 3;
            if (cant_num_sprite_tir < 2)
        {
            cant_num_sprite_tir++;
        }
        else{
                cant_num_sprite_tir = 0;
            }
            }
            else
            {
                if (worrior[0].direccion == 0)
            {
                worrior[0].y -= velocidad;
                worrior[0].direccion = 0;
            if (cant_num_sprite_tir > 5 && cant_num_sprite_tir < 8)
            {
                cant_num_sprite_tir++;
            }
            else{
                cant_num_sprite_tir = 6;
            }
            }
            if (worrior[0].direccion == 2)
            {
                worrior[0].y += velocidad;
                worrior[0].direccion = 2;

            if (cant_num_sprite_tir > 8 && cant_num_sprite_tir < 11)
            {
                cant_num_sprite_tir++;
            }

            else
            {
                cant_num_sprite_tir = 9;
            }
            }
            }
        }
	}

	for (int i = 0; i < 150; ++i)
	{
        if (verif_colision_tirador(worrior[0],muro[i])==1)
        {
            if (i == 71 || i == 72){

            if (i==71){
                worrior[0].x = 702;
                worrior[0].y = 296;
                portal=1;
            }
            else{
                worrior[0].x = 222;
                worrior[0].y = 296;
                portal=1;

            }
            }

            else
            {
                worrior[0].y = y;
                worrior[0].x = x;
            }
        }
	}
	/*for (int i = 0; i < enemigos_tot; ++i)
	{
	if (verif_colision_tiradorenemigo(enemigo[i] , worrior[0]) == 1)
	{
	if (enemigo[i].alive == 1)
	{
		worrior[0].muerte = 1;
		cant_num_sprite_tir = 0;
	}
	}
	}*/
	}
 }


 static void tirador_mov(int mov){ // movimiento de salida del tirador de la sala de espera

	SDL_Rect src;
	SDL_Rect dest;

	src.x = 666;
	src.y = 497;
	src.w = 12;
	src.h = 20;


	int velocidad = 8;
	muro_temp(2);
	if (worrior[0].muerte==1)
	{
		muro_temp(2);

		if (worrior[0].vida>0)
		{
			tiempo_vida++;
			dest.x = 484;
			dest.y = 216 - ((tiempo_vida / 30)%11)*24;//////////////////////////
			dest.w = 12;
			dest.h = 20;
			SDL_BlitSurface(sprites, &dest, screen, &src);


			if (mov==0)
			{
				if ((tiempo_vida / 30)%11==10)
				{
					if (worrior[1].y != 440)
					{
						worrior[1].y -= velocidad;
					}
					if (worrior[1].y == 440)
					{
						worrior[0].x = 702;
						worrior[0].y = 440;
						worrior[0].muerte=0;
						--worrior[0].vida;
						--lifes;
						worrior[1].y = 488;
						muro_temp(2);
						tiempo_vida=0;
					}
				}
			}
			if (mov==1)
			{
				if (worrior[1].y != 440)
				{
					worrior[1].y -= velocidad;
				}
				if (worrior[1].y == 440)
				{
					worrior[0].x = 702;
					worrior[0].y = 440;
					worrior[0].muerte=0;
					--worrior[0].vida;
					--lifes;
					worrior[1].y = 488;
					muro_temp(2);
					tiempo_vida=0;
				}
			}
		}
	}
}

//Retorna 1 si ocurre la colision y 0 si no ocurre
int verif_colision_tirador(worrior_t a, muro_t b) {

	int left_a, left_b;
	int right_a, right_b;
	int top_a, top_b;
	int bottom_a, bottom_b;

	left_a = a.x;
	right_a = a.x + a.w;
	top_a = a.y;
	bottom_a = a.y + a.h;

	left_b = b.x;
	right_b = b.x + b.w;
	top_b = b.y;
	bottom_b = b.y + b.h;


	if (left_a > right_b) {
		return 0;
	}

	if (right_a < left_b) {
		return 0;
	}

	if (top_a > bottom_b) {
		return 0;
	}

	if (bottom_a < top_b) {
		return 0;
	}

	return 1;}


// Main function

int main (int argc, char *args[]) {

	// Define the player and the maps
	//game_element_t player;

	// For the project the elements of the map should be created
	// dinamically (using malloc) and using linked lists.
	//game_element_t map_element;

	//SDL Window setup
	if (init_SDL(SCREEN_WIDTH, SCREEN_HEIGHT, argc, args) == FAILURE) {

		return FAILURE;
	}


	SDL_GetWindowSize(window, &g_width, &g_height);

    Uint32 next_game_tick = SDL_GetTicks();
    int sleep = 0;
	int quit = FALSE;
	int accion = 0;
	int select =0;




	//render loop
	while(quit == FALSE) {
        t++;
        tiempo_vel++;
        //check for new events every frame
		SDL_PumpEvents();

		const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_ESCAPE]) {

            quit = TRUE;
        }

        if (keystate[SDL_SCANCODE_SPACE]) {

        }



        //Acciones de movimientos
        if (keystate[SDL_SCANCODE_S]) {//Detecta cuando se presiona la tecla S

			tirador_movimiento(2);
		}

		if (keystate[SDL_SCANCODE_W]) {//Detecta cuando se presiona la tecla W

			tirador_movimiento(0);
			tirador_mov(1);
		}
		if (keystate[SDL_SCANCODE_D]){//Detecta cuando se presiona la tecla D
			tirador_movimiento(1);
		}
		if (keystate[SDL_SCANCODE_A]){//Detecta cuando se presiona la tecla A
			tirador_movimiento(3);
		}


		//Dibuja el fondo
		SDL_RenderClear(renderer);

		SDL_FillRect(screen, NULL, 0x000000ff);


        if (accion == 0){
            if (select<4){

                if (keystate[SDL_SCANCODE_SPACE]){
                    ++select;
                    SDL_Delay(400);
                }
            }
            if(select>2){

                if (select==3)
				{
					if (keystate[SDL_SCANCODE_RETURN]) {

						lifes = 3;
                        accion = 1;
						level=0;
						game_inicialization();
						mapa1();
						//enemigo_azul();
						SDL_Delay(300);

					}

				}
				if (select==4)
				{
					if (keystate[SDL_SCANCODE_RETURN]) {

						lifes = 7;
						accion = 1;
						level=0;
						game_inicialization();
						mapa1();

						//enemigo_azul();
						SDL_Delay(300);
					}
					else if (keystate[SDL_SCANCODE_P]) {

                        --select;
					}
				}

            }
            menu(select);


		}

		else if(accion==1){
            cuadro_de_juego();

            tirador_mov(0);
            muro_temp(1);
            crear_paredes();
            tirador_sprites();
            crea_worrior();

		}


		SDL_UpdateTexture(screen_texture, NULL, screen->pixels,
						  screen->w * sizeof (Uint32));
		SDL_RenderCopy(renderer, screen_texture, NULL, NULL);

		//draw to the display
		SDL_RenderPresent(renderer);

		//time it takes to render  frame in milliseconds
		next_game_tick += 1000 / 30;
		sleep = next_game_tick - SDL_GetTicks();

		if( sleep >= 0 ) {

			SDL_Delay(sleep);
		}
	}

	//free loaded images
	SDL_FreeSurface(screen);
	SDL_FreeSurface(title);
	SDL_FreeSurface(game_menu);
	SDL_FreeSurface(end);

	//free renderer and all textures used with it
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return SUCCESS;

}

/* Function: init_SDL
 * ----------------------------
 * This function initialises the required environment for SDL
 * to work.
 *
 * Arguments:
 *	width: The width of the screen.
 * 	height: The height of the screen.
 *	argc: The same parameter from the main function.
 *	args: The same parameter from the main function.
 *
 * Return:
 *	SUCCESS if no problem reported.
 *	FAILURE if any initialization failed
 */
int init_SDL(int width, int height, int argc, char *args[]) {

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

		return FAILURE;
	}

	int i;

	for (i = 0; i < argc; i++) {

		//Create window
		if(strcmp(args[i], "-f")) {

			SDL_CreateWindowAndRenderer(SCREEN_WIDTH,
										SCREEN_HEIGHT,
										SDL_WINDOW_SHOWN,
										&window,
										&renderer);

		} else {

			SDL_CreateWindowAndRenderer(SCREEN_WIDTH,
										SCREEN_HEIGHT,
										SDL_WINDOW_FULLSCREEN_DESKTOP,
										&window,
										&renderer);
		}
	}

	if (window == NULL) {

		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

		return FAILURE;
	}

	// Create the screen surface where all the elements will be drawn
	screen = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32,
											SDL_PIXELFORMAT_RGBA32);

	if (screen == NULL) {

		printf("Could not create the screen surfce! SDL_Error: %s\n",
			   SDL_GetError());

		return FAILURE;
	}

	// Create the screen texture to render the screen surface to the actual
	// display
	screen_texture = SDL_CreateTextureFromSurface(renderer, screen);

	if (screen_texture == NULL) {

		printf("Could not create the screen_texture! SDL_Error: %s\n",
				SDL_GetError());

		return FAILURE;
	}

	//Load the title image
	title = SDL_LoadBMP("title.bmp");

	if (title == NULL) {

		printf("Could not Load title image! SDL_Error: %s\n", SDL_GetError());

		return FAILURE;
	}

	//Load the game_menu image
	game_menu = SDL_LoadBMP("wiz.bmp");

	if (game_menu == NULL) {

		printf("Could not Load game_menu image! SDL_Error: %s\n",
				SDL_GetError());

		return FAILURE;
	}

		//Carga la imagen del puntos
	puntos = SDL_LoadBMP("puntos.bmp");

	if (puntos == NULL) {

		printf("Could not Load puntos image! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Carga la imagen laberinto3
	laberinto3 = SDL_LoadBMP("laberinto3.bmp");

	if (laberinto3 == NULL) {

		printf("La imagen laberinto3 no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}
	//Carga la imagen laberinto2
	laberinto2 = SDL_LoadBMP("laberinto2.bmp");

	if (laberinto2 == NULL) {

		printf("La imagen laberinto2 no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Carga la imagen radar
	radar = SDL_LoadBMP("radar.bmp");

	if (radar == NULL) {

		printf("La imagen radar no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//Carga la imagen insert_coin
	insert_coin = SDL_LoadBMP("insert_coin.bmp");

	if (insert_coin == NULL) {

		printf("La imagen intert_coin no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	one_coin = SDL_LoadBMP("one_coin.bmp");

	if (one_coin == NULL) {

		printf("La imagen one_coin no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	two_coin = SDL_LoadBMP("two_coin.bmp");

	if (two_coin == NULL) {

		printf("La imagen two_coin no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}
	//carga los sprites
	sprites = SDL_LoadBMP("sprites.bmp");

	if (sprites == NULL) {

		printf("La imagen sprites no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//carga la imagen numblab
	numblab = SDL_LoadBMP("numblab.bmp");

	if (numblab == NULL) {

		printf("La imagen numblab no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	interfaz_in_user = SDL_LoadBMP("interfaz_in_user.bmp");

	if (interfaz_in_user == NULL) {

		printf("La imagen nterfaz_in_user no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}

	//carga la imagen gameover
	end = SDL_LoadBMP("gameover.bmp");

	if (end == NULL) {

		printf("La imagen end no puede ser cargada! SDL_Error: %s\n", SDL_GetError());

		return 1;
	}


	// Set the title colourkey.
	Uint32 colorkey = SDL_MapRGB(title->format, 255, 0, 0);
	SDL_SetColorKey(title, SDL_TRUE, colorkey);
	SDL_SetColorKey(game_menu, SDL_TRUE, colorkey);

	return SUCCESS;
}
