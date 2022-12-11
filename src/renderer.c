#include "display.h"
#include "utils.h"


void * display_routine ( void * args)
{
	targ_t * a = (targ_t *) args;
	int quit_f = *(a->quit_f), 
		w_updated_f = 0;

	a->t_level = (SDL_Texture *) a->m_main->c_texture;
	a->t_char = (SDL_Texture *) a->c_main->c_texture;
	
	do
	{
		pthread_mutex_lock( a->m_stdout);
		w_updated_f = *(a->w_updated_f);
		quit_f = *(a->quit_f);
		pthread_mutex_unlock( a->m_stdout);
		
		if ( w_updated_f == 1)
		{

			displayGameScreen ( a->r, a->t_background, a->t_level, a->t_char, *(a->x), *(a->y), (a->c_main->w), (a->c_main->h));
			pthread_mutex_lock ( a->m_stdout);
			*(a->w_updated_f) = 0;
			pthread_mutex_unlock ( a->m_stdout);
		}		
	} while (!quit_f);
	
	return NULL;
}



