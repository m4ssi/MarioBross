#include "utils.h"


void * engine_routine ( void * args)
{
	targ_t * a = (targ_t *) args;
	int quit_f = *(a->quit_f);
	int moved_f = 0;

	a->t_level = (SDL_Texture *) a->m_main->c_texture;
	a->t_char = (SDL_Texture *) a->c_main->c_texture;
	
	do
	{
		pthread_mutex_lock( a->m_stdout);
		quit_f = *(a->quit_f);
		moved_f = *(a->moved_f);
		pthread_mutex_unlock( a->m_stdout);
		
		if ( moved_f)
		{
			pthread_mutex_lock ( a->m_stdout);
			a->c_main->x += *(a->dx);
			*(a->dx) = 0;
			*(a->w_updated_f) = 1;
			*(a->moved_f) = 0;
			pthread_mutex_unlock ( a->m_stdout);
		}		
	} while (!quit_f);
	
	return NULL;
}
