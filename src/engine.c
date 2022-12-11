#include "utils.h"
#include <time.h>

double gettime () {
	struct timespec ts;
	clock_gettime ( CLOCK_MONOTONIC, &ts);
	return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}

void * engine_routine ( void * args)
{
	targ_t * a = (targ_t *) args;
	int quit_f = *(a->quit_f),
		moved_f = 0,
		jumped_f = 0;

	double	t1 = gettime(),
			t2 = 0.0f;
	a->t_level = (SDL_Texture *) a->m_main->c_texture;
	a->t_char = (SDL_Texture *) a->c_main->c_texture;
	
	do
	{
		pthread_mutex_lock( a->m_stdout);
		quit_f = *(a->quit_f);
		moved_f = *(a->moved_f);
		if (!jumped_f)	jumped_f = *(a->jumped_f);
		pthread_mutex_unlock( a->m_stdout);

		t2 = gettime();
		
		if ( moved_f)
		{
			pthread_mutex_lock ( a->m_stdout);
			a->c_main->x += *(a->dx);
			*(a->dx) = 0;
			*(a->w_updated_f) = 1;
			*(a->moved_f) = 0;
			pthread_mutex_unlock ( a->m_stdout);
		}
		if ( jumped_f)
		{
			if ( t2 - t1 > 7e-2)
			{
				pthread_mutex_lock ( a->m_stdout);
				if ( jumped_f > 3) a->c_main->y -= 1;
				else 			   a->c_main->y += 1;
				jumped_f--;
				if ( jumped_f == 0) *(a->jumped_f) = 0;
				*(a->w_updated_f) = 1;
				pthread_mutex_unlock ( a->m_stdout);		
				t1 = gettime();
				// Detecter l'impact
			
			}
		}
	} while (!quit_f);
	
	return NULL;
}
