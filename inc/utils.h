#ifndef _H_UTILS_
#define _H_UTILS_

#include <pthread.h>
#include <SDL2/SDL.h>



#include "character.h"



#define S_PIXEL 5
#define W_TOP	0
#define W_LEFT	0
#define S_BOX	20
#define W_WIDTH 1000
#define W_HEIGHT (15* S_BOX)
#define W_TITLE "Super Mario Bross - Beta"

typedef characater_t map_t;

typedef struct
{
	
	pthread_mutex_t * m_stdout,
					* m_coord,
					* m_updated_f;

	characater_t * c_main;
	map_t *	m_main;

	// Used by all
	int * w_updated_f,
		* quit_f;

	// Used by event listener
	int * moved_f,
		* jumped_f,
		*dy, *dx;
	
	// Used by game engine
	int * x, *y;

	SDL_Window * w;
	SDL_Renderer * r;
	SDL_Texture * t_char,
				* t_level,	
				* t_background;	
}targ_t;


targ_t init_arg_t ( SDL_Window * win, SDL_Renderer * rend, char * f_character, char * f_map);

void free_targ_t ( targ_t a);


#endif
